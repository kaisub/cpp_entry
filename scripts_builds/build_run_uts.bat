@echo off
setlocal enabledelayedexpansion

:: Call the shared setup script and pass arguments (e.g., --clean)
call "scripts_builds\setup_msvc.bat" %1

echo.
echo [INFO] Configuring Project (App + Tests)...
:: Using Ninja to prevent generator conflicts with code_check.bat [cite: 23, 24]
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=cl -DCMAKE_C_COMPILER=cl -DBUILD_TESTING=ON
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
echo.

echo [INFO] Building All Targets...
cmake --build build --config Debug
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
echo.

echo [INFO] Running Unit Tests...
:: Run tests from the bin directory 
.\build\bin\unit_tests.exe
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Unit tests failed!
    exit /b %ERRORLEVEL%
)
echo.

if not "%NOPAUSE%"=="1" pause