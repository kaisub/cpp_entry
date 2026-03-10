@echo off
:: CRITICAL: Do NOT use setlocal here! 
:: We need the MSVC environment variables to be exported back to the calling script.

:: Navigate to the project root directory
cd /d "%~dp0.."

:: 1. Handle Clean Flag
if "%1"=="--clean" (
    echo.
    echo [INFO] Flag --clean detected. Running clean script...
    set NOPAUSE=1
    call "scripts_builds\clean.bat"
    set NOPAUSE=0
)

:: 2. Check if environment is already loaded
if defined DevEnvDir goto :vs_setup_done

echo [INFO] Searching for Visual Studio installation...
set "VS_PATH="
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -property installationPath`) do (
    set "VS_PATH=%%i"
)

:: Check if vswhere found anything
if not defined VS_PATH (
    echo [ERROR] vswhere.exe could not find a Visual Studio installation.
    exit /b 1
)

:: Check if the specific compiler script exists
if not exist "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" (
    echo [ERROR] Could not find vcvarsall.bat in "%VS_PATH%".
    exit /b 1
)

echo [INFO] Loading VS environment from: %VS_PATH%
call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x64

:vs_setup_done