cmake_minimum_required(VERSION 3.15...3.28)

option(BUILD_TESTING "Build unit tests" ON)

# Generate project name based on the root folder name
get_filename_component(ProjectId ${CMAKE_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(cpp_entry VERSION 1.0.0 LANGUAGES CXX)

# Tells CMake to create a JSON file containing all compiler commands for the whole project
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define path to bin directory inside the current build folder to isolate builds
set(OUTPUT_BIN_DIR ${CMAKE_BINARY_DIR}/bin)

# Force no subfolders for /Debug or /Release for MSVC
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${OUTPUT_BIN_DIR}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${OUTPUT_BIN_DIR}" )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${OUTPUT_BIN_DIR}" )
endforeach()

# Put in bin all file types (.exe)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

# Put in bin all dynamic libraries (.dll / .so)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

# Put in bin all static libraries and archives (.lib / .a)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable scanning for C++20 Modules dependencies.
# This prevents CMake from injecting '-fdeps-format=p1689r5' flags 
# into compile_commands.json, which Clang-Tidy currently does not support.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# --- Code Coverage Flags (GCC / Clang on MSYS2 / Linux) ---
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT MSVC)
    message(STATUS "Enabling Code Coverage flags for GCC/Clang")

    # Compilation flags: disable optimization (-O0), enable debug (-g) and coverage
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")

    # Linker flags: must also contain --coverage to create proper executables
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
endif()

# --- Sanitizers (Address & Undefined Behavior) ---
option(USE_SANITIZERS "Enable ASan and UBSan for memory error detection" OFF)

# Only enable sanitizers for Linux/GCC builds, exclude Windows cross-compilation
if(USE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Enabling Address and Undefined Behavior Sanitizers")

    # Add sanitizer flags and ensure frame pointers are kept for readable stack traces
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address,undefined")
endif()

# --- FetchContent: Magic Enum ---
# Store fetched dependencies in the _deps/ folder
#set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps")
include(FetchContent)
FetchContent_Declare(
    magic_enum
    URL https://github.com/Neargye/magic_enum/archive/refs/tags/v0.9.5.zip
    EXCLUDE_FROM_ALL # <--- Add this to keep compile_commands.json clean
)
FetchContent_MakeAvailable(magic_enum)

# Collection of source and header files
# Use GLOB_RECURSE to find files in all subdirectories (like src/dummy)
# Using CONFIGURE_DEPENDS forces CMake to check directory contents at build time
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE libs_SRC CONFIGURE_DEPENDS "inc/*.h" "inc/*.hpp")

# Create library (to separate logic from main.cpp)
add_library(${PROJECT_NAME}_lib STATIC ${SRC_LIST} ${libs_SRC})
target_include_directories(${PROJECT_NAME}_lib PUBLIC inc)

# Link magic_enum PUBLICLY to the library so anything linking to this library inherits the include paths
target_link_libraries(${PROJECT_NAME}_lib PUBLIC magic_enum::magic_enum)

# Create executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the library to the executable (automatically includes magic_enum via transitive dependency)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Remove default /W3 from CMAKE_CXX_FLAGS to prevent D9025 warning
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()

    # Apply strict warning level at the target level
    target_compile_options(${PROJECT_NAME}_lib PRIVATE /W4)
endif()

# Unit Tests
if(BUILD_TESTING)
    enable_testing()
    
    # Google Test setup
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        EXCLUDE_FROM_ALL # <--- REQUIRED: Drops target from default build & JSON DB
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # --- CRITICAL FIX: Forcefully drop GTest from compile_commands.json ---
    set_target_properties(gtest gtest_main gmock gmock_main 
        PROPERTIES EXPORT_COMPILE_COMMANDS OFF
    )

    # Recursively find all C++ source files in the tests directory and its subdirectories
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")

    # Check if any test files were found to avoid CMake configuration errors
    if(NOT TEST_SOURCES)
        message(WARNING "No test files found in the tests/ directory!")
    endif()

    # Create the test executable using all dynamically found source files
    add_executable(unit_tests ${TEST_SOURCES})
    # Add common folder to include paths for unit_tests target
    target_include_directories(unit_tests PRIVATE tests)

    # Link tests to the main library (which includes magic_enum) and GTest
    target_link_libraries(unit_tests PRIVATE ${PROJECT_NAME}_lib GTest::gtest_main GTest::gmock_main)
    
    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

# --- Static Analysis: Cppcheck ---
find_program(CPPCHECK_PROGRAM cppcheck)

if(CPPCHECK_PROGRAM)
    add_custom_target(
        run_cppcheck
        COMMAND ${CPPCHECK_PROGRAM}
            --enable=all
            --inconclusive
            --inline-suppr
            --suppress=missingIncludeSystem
            -I ${CMAKE_SOURCE_DIR}/inc
            -I ${CMAKE_BINARY_DIR}/_deps/magic_enum-src/include  # Provide magic_enum to cppcheck
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/main.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running Cppcheck analysis..."
    )
endif()

# --- Static Analysis: Clang-Tidy ---
# Search for clang-tidy with explicit common installation paths
find_program(CLANG_TIDY_EXE
    NAMES clang-tidy
    PATHS "C:/Program Files/LLVM/bin" "C:/Program Files (x86)/LLVM/bin"
)

# Modern Clang-Tidy Target (Uses compile_commands.json from Ninja)
if(CLANG_TIDY_EXE)
    add_custom_target(
        run_tidy
        COMMAND ${CLANG_TIDY_EXE}
            -p=${CMAKE_BINARY_DIR}        # Point to the build directory containing JSON DB
            ${SRC_LIST}                   # includes all .cpp from subdirectories
            main.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running Clang-Tidy analysis using compile_commands.json..."
    )
endif()