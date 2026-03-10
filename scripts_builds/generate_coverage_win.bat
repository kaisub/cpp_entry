@echo off
setlocal

:: Navigate to the project root
cd /d "%~dp0.."

echo [INFO] Configuring Project for Coverage Analysis...
echo [INFO] Requires build_run_uts.bat to be run first to build the executable.
echo.

:: Create coverage output directory if it doesn't exist
if not exist coverage mkdir coverage

echo [INFO] Running Coverage Analysis...
set COVERAGE_EXE="C:\Program Files\OpenCppCoverage\OpenCppCoverage.exe"

:: Check if EXE exists at the default path
if not exist %COVERAGE_EXE% (
    set COVERAGE_EXE=OpenCppCoverage
)

:: Note: OpenCppCoverage must execute the binary to gather data
%COVERAGE_EXE% ^
    --sources "%cd%\src" ^
    --sources "%cd%\inc" ^
    --export_type=html:coverage ^
    -- ".\build\bin\unit_tests.exe"

if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Coverage report generated in: coverage\index.html
    start "" "coverage\index.html"
) else (
    echo [ERROR] Coverage analysis failed. Did you build the tests first?
)

if not "%NOPAUSE%"=="1" pause