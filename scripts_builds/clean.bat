@echo off
setlocal

:: Navigate to project root
cd /d "%~dp0\.."

echo [INFO] =================================================
echo [INFO] Running DEEP Clean (Preserving downloaded source)...
echo [INFO] =================================================
echo.

call :DeepClean build
call :DeepClean build_win

echo.
echo [SUCCESS] Deep Clean completed!
exit /b 0

:: --- Helper Function ---
:DeepClean
set "TGT=%~1"
if exist "%TGT%" (
    echo [INFO] Cleaning %TGT%...
    
    :: 1. Delete all subdirectories EXCEPT _deps
    for /d %%D in ("%TGT%\*") do (
        if /i not "%%~nxD"=="_deps" rmdir /s /q "%%D"
    )
    
    :: 2. CRITICAL FIX: Force delete all files (including hidden/system) without a loop
    del /f /q /a "%TGT%\*" >nul 2>&1
    
    :: 3. Go INSIDE _deps and delete subbuilds/builds (the generator conflict source)
    if exist "%TGT%\_deps" (
        for /d %%S in ("%TGT%\_deps\*-subbuild") do rmdir /s /q "%%S"
        for /d %%B in ("%TGT%\_deps\*-build") do rmdir /s /q "%%B"
    )
    
    echo [INFO] %TGT% cleaned. Downloaded source in _deps is safe.
)
exit /b 0