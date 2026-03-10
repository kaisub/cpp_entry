@echo off
setlocal enabledelayedexpansion

:: Navigate to the project root directory
cd /d "%~dp0.."

:: Call the shared setup script and pass arguments (e.g., --clean)
call "scripts_builds\setup_msvc.bat" %1

echo [INFO] Starting full build (Application + Tests)...

:: Configure using Ninja generator to prevent cache collisions
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=cl -DCMAKE_C_COMPILER=cl -DBUILD_TESTING=ON
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

:: Build all targets
cmake --build build --config Debug

if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Build completed successfully!
    echo [INFO] Binaries are located in the /build/bin folder
) else (
    echo [ERROR] Build failed.
    exit /b %ERRORLEVEL%
)

if not "%NOPAUSE%"=="1" pause