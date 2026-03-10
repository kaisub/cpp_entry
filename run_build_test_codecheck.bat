@echo off
setlocal

:: Navigate to the directory containing this script (project root)
cd /d "%~dp0"

echo [INFO] =================================================
echo [INFO] Starting Local CI Pipeline (Windows)...
echo [INFO] =================================================
echo.

:: --- Step 1: Build and Tests ---
echo [INFO] Step 1: Building and running unit tests (--clean)
:: Trick with '< nul' automatically presses 'Enter' for each pause inside the scripts, allowing it to run uninterrupted.
call "scripts_builds\build_run_uts.bat" --clean < nul

:: Exit code verification (Fail-Fast)
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Build or Unit Tests failed! Stopping pipeline.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [INFO] =================================================
:: --- Step 2: Static Analysis ---
echo [INFO] Step 2: Running Static Analysis (Cppcheck ^& Clang-Tidy)
call "scripts_builds\code_check.bat" < nul

:: Exit code verification
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Static analysis found issues! Pipeline failed.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [INFO] =================================================
echo [SUCCESS] All pipeline steps completed successfully!
echo [INFO] =================================================

pause