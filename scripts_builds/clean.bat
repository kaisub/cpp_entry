@echo off
setlocal

:: Navigate to the project root directory
cd /d "%~dp0.."

echo [INFO] Cleaning project...

:: Remove the generated directories if they exist
if exist build rd /s /q build
if exist build_win rd /s /q build_win
if exist bin rd /s /q bin
if exist coverage rd /s /q coverage
if exist deps rd /s /q deps

echo [SUCCESS] Workspace cleaned.
echo.

:: Pause unless NOPAUSE is set
if not "%NOPAUSE%"=="1" pause