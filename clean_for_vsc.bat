@echo off
setlocal enabledelayedexpansion

:: Detect if script is in scripts_builds/ or root, and set working directory to project root
cd /d "%~dp0"
if exist "..\CMakeLists.txt" cd /d "%~dp0\.."

echo [INFO] =================================================
echo [INFO] Preparing for VS Code: Deep cleaning CMake cache...
echo [INFO] =================================================
echo.

:: Clean the main build directory
call :DeepClean build

:: Clean the Windows cross-compilation directory
call :DeepClean build_win

echo.
echo [INFO] =================================================
echo [SUCCESS] VS Code environment deep cleaned successfully!
echo [INFO] =================================================
pause
exit /b 0


:: --- Helper Function for Deep Cleaning ---
:DeepClean
set "TARGET_DIR=%~1"
if not exist "%TARGET_DIR%" exit /b 0

echo [INFO] Cleaning main cache in %TARGET_DIR%...
if exist "%TARGET_DIR%\CMakeFiles" rmdir /s /q "%TARGET_DIR%\CMakeFiles"
if exist "%TARGET_DIR%\CMakeCache.txt" del /f /q "%TARGET_DIR%\CMakeCache.txt"
if exist "%TARGET_DIR%\.cmake" rmdir /s /q "%TARGET_DIR%\.cmake"

:: --- Clean FetchContent subbuilds ---
if exist "%TARGET_DIR%\_deps" (
    echo [INFO] Cleaning FetchContent cache in %TARGET_DIR%\_deps...
    
    :: Remove the subbuild folders (contains the conflicting Ninja cache)
    for /d %%D in ("%TARGET_DIR%\_deps\*-subbuild") do (
        rmdir /s /q "%%D"
    )
    
    :: Remove the dependency build folders (forces reconfiguration for VS2022)
    for /d %%D in ("%TARGET_DIR%\_deps\*-build") do (
        rmdir /s /q "%%D"
    )
    
    echo [INFO] %TARGET_DIR%\_deps cleaned. Downloaded source code is safe!
)
exit /b 0