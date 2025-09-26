@echo off
cls
echo.
echo ========================================
echo  Stellar Data Recovery Pro Free
echo ========================================
echo.

REM Set working directory to script location
cd /d "%~dp0"

REM Check if executable exists
if exist "bin\stellar-recovery.exe" (
    echo Launching Stellar Data Recovery Pro...
    echo Working Directory: %CD%
    echo.
    start "" "bin\stellar-recovery.exe"
    echo Application launched successfully!
) else if exist "bin\stellar.exe" (
    echo Launching Stellar Data Recovery...
    echo Working Directory: %CD%
    echo.
    start "" "bin\stellar.exe"
    echo Application launched successfully!
) else (
    echo ERROR: Stellar Data Recovery executable not found!
    echo.
    echo Please ensure one of the following files exists:
    echo - bin\stellar-recovery.exe
    echo - bin\stellar.exe
    echo.
    echo Run 'setup.bat' first to configure the project structure.
    echo.
    pause
    goto :end
)

echo.
echo ========================================
echo  Application Running
echo ========================================
echo.
echo The application is now running in a separate window.
echo You can close this command prompt safely.
echo.

:end
timeout /t 3 /nobreak >nul