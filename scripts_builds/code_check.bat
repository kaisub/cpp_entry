@echo off
setlocal enabledelayedexpansion

:: Navigate to the project root directory
cd /d "%~dp0.."

:: Handle manual clean flag
if "%1"=="--clean" (
    echo.
    echo [INFO] Flag --clean detected. Running clean script...
    set NOPAUSE=1
    call "scripts_builds\clean.bat"
    set NOPAUSE=0
    echo.
)

:: Load Visual Studio environment dynamically to use cl.exe in regular CMD
if not defined DevEnvDir (
    echo [INFO] Searching for Visual Studio installation...
    :: Removed strict -requires flag to ensure it finds Build Tools correctly
    for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -property installationPath`) do (
        set "VS_PATH=%%i"
    )
    
    if defined VS_PATH (
        if exist "!VS_PATH!\VC\Auxiliary\Build\vcvarsall.bat" (
            echo [INFO] Loading VS environment from: !VS_PATH!
            call "!VS_PATH!\VC\Auxiliary\Build\vcvarsall.bat" x64
        ) else (
            echo [ERROR] Could not find vcvarsall.bat in "!VS_PATH!".
            exit /b 1
        )
    ) else (
        echo [ERROR] vswhere.exe could not find a Visual Studio installation.
        exit /b 1
    )
)

echo.
echo [INFO] Configuring Project for Static Analysis...
:: CRITICAL: Force Ninja and MSVC to successfully generate compile_commands.json
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=cl -DCMAKE_C_COMPILER=cl -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Configuration failed.
    exit /b %ERRORLEVEL%
)
echo.

echo [INFO] Running Cppcheck...
if not exist "build\compile_commands.json" (
    echo [ERROR] compile_commands.json missing! 
    exit /b 1
)

:: Run Cppcheck, ignore deps/tests, use .jenkins suppressions, and fail on error (--error-exitcode=1)
cppcheck --project=build/compile_commands.json -i deps -i tests --enable=all --inconclusive --suppressions-list=.jenkins/cppcheck_suppressions.txt --error-exitcode=1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Cppcheck found issues! Build failed.
    exit /b %ERRORLEVEL%
)
echo.

echo [INFO] Running Clang-Tidy...
:: Run Clang-Tidy via CMake target
cmake --build build --target run_tidy
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Clang-Tidy found issues! Build failed.
    exit /b %ERRORLEVEL%
)
echo.

echo [SUCCESS] Static Analysis completed without issues!
if not "%NOPAUSE%"=="1" pause