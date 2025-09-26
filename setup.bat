@echo off
cls
echo.
echo ========================================
echo  Stellar Data Recovery Pro Free Setup
echo ========================================
echo.

REM Create necessary directories
echo Creating project directories...
if not exist "src" mkdir src
if not exist "bin" mkdir bin
if not exist "docs" mkdir docs
if not exist "scripts" mkdir scripts
if not exist "releases" mkdir releases
if not exist "temp" mkdir temp

echo Directories created successfully!
echo.

REM Check for existing installation
echo Checking for existing installation...
if exist "bin\stellar-recovery.exe" (
    echo Found existing installation in bin directory.
) else (
    echo No existing installation found.
    echo Please place your Stellar Data Recovery executable in the 'bin' directory.
)
echo.

REM Create shortcuts if needed
echo Creating desktop shortcuts...
if exist "bin\stellar-recovery.exe" (
    powershell -Command "& {$WshShell = New-Object -comObject WScript.Shell; $Shortcut = $WshShell.CreateShortcut('%USERPROFILE%\Desktop\Stellar Data Recovery.lnk'); $Shortcut.TargetPath = '%CD%\bin\stellar-recovery.exe'; $Shortcut.WorkingDirectory = '%CD%\bin'; $Shortcut.Save()}"
    echo Desktop shortcut created!
) else (
    echo Skipping shortcut creation - executable not found.
)
echo.

REM Display system information
echo System Information:
echo OS: %OS%
echo User: %USERNAME%
echo Computer: %COMPUTERNAME%
echo Current Directory: %CD%
echo.

echo ========================================
echo  Setup Complete!
echo ========================================
echo.
echo Next steps:
echo 1. Place your Stellar Data Recovery executable in the 'bin' folder
echo 2. Run 'run.bat' to launch the application
echo 3. Check 'docs' folder for documentation
echo.
pause