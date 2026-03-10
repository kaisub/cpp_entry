@echo off
setlocal

:: Navigate to the directory containing this script (project root)
cd /d "%~dp0"

:: Disable individual pauses in child scripts
set NOPAUSE=1

echo [INFO] =================================================
echo [INFO] Starting Local CI Pipeline...
echo [INFO] =================================================
echo.

:: --- Step 1: Build and Tests ---
echo [INFO] Step 1: Building and running unit tests (--clean)
:: Use 'call' to return to this script after completion
call "scripts_builds\build_run_uts.bat" --clean

:: Exit code verification (Fail-Fast)
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Build or Unit Tests failed! Stopping pipeline.
    exit /b %ERRORLEVEL%
)

echo.
echo [INFO] =================================================
:: --- Step 2: Static Analysis ---
echo [INFO] Step 2: Running Static Analysis (Cppcheck ^& Clang-Tidy)
call "scripts_builds\code_check.bat"

:: Exit code verification
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Static analysis found issues! Pipeline failed.
    exit /b %ERRORLEVEL%
)

echo.
echo [INFO] =================================================
echo [SUCCESS] All pipeline steps completed successfully!
echo [INFO] =================================================

:: Pipeline is done, restore normal pause behavior and pause the final result
set NOPAUSE=0
pause