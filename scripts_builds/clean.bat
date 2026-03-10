@echo off
setlocal

:: Przejdź do głównego folderu projektu
cd /d "%~dp0\.."

echo [INFO] =================================================
echo [INFO] Running Clean (Windows) keeping _deps...
echo [INFO] =================================================
echo.

:: Wyczyść domyślny build oraz build dla cross-kompilacji
call :SmartClean build
call :SmartClean build_win

:: Remove the generated directories if they exist
if exist coverage rd /s /q coverage

echo.
echo [SUCCESS] Clean completed!
exit /b 0

:: --- Funkcja czyszcząca ---
:SmartClean
set "TARGET_DIR=%~1"
if exist "%TARGET_DIR%" (
    echo [INFO] Cleaning '%TARGET_DIR%' directory...
    
    :: 1. Usuń wszystkie podfoldery Z WYJĄTKIEM folderu _deps
    for /d %%D in ("%TARGET_DIR%\*") do (
        if /i not "%%~nxD"=="_deps" (
            rmdir /s /q "%%D"
        )
    )
    
    :: 2. Usuń wszystkie pliki luzem w folderze (m.in. CMakeCache.txt)
    for %%F in ("%TARGET_DIR%\*") do (
        del /f /q "%%F"
    )
    
    echo [INFO] '%TARGET_DIR%' cleaned. '_deps' are safe.
) else (
    echo [INFO] Directory '%TARGET_DIR%' does not exist. Skipping.
)
exit /b 0