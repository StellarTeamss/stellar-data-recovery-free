@echo off
cls
echo.
echo ========================================
echo  Stellar Data Recovery Pro - Build
echo ========================================
echo.

REM Set working directory to script location
cd /d "%~dp0"

echo Checking build environment...

REM Check for source files
if not exist "src" (
    echo ERROR: Source directory 'src' not found!
    echo This appears to be a binary distribution.
    goto :no_build
)

if not exist "src\*.cpp" (
    echo No C++ source files found in src directory.
    echo This appears to be a binary distribution.
    goto :no_build
)

echo C++ source files detected. Attempting build...

REM Check for build tools
echo.
echo Detecting build tools...

REM Check for Visual Studio
where cl >nul 2>&1
if %ERRORLEVEL% equ 0 (
    echo Found Visual Studio compiler (cl.exe)
    goto :build_vs
)

REM Check for MinGW-w64
where g++ >nul 2>&1
if %ERRORLEVEL% equ 0 (
    echo Found MinGW-w64 compiler (g++.exe)
    goto :build_mingw
)

REM Check for CMake
where cmake >nul 2>&1
if %ERRORLEVEL% equ 0 (
    echo Found CMake build system
    goto :build_cmake
)

echo No suitable build tools found!
echo.
echo Please install one of the following:
echo 1. Visual Studio Build Tools or Visual Studio Community
echo 2. MinGW-w64 compiler suite
echo 3. CMake with a compatible compiler
echo.
goto :no_build

:build_vs
echo.
echo Building with Visual Studio compiler...
cd src
if not exist "obj" mkdir obj
cl /std:c++17 /EHsc /O2 /DWIN32_LEAN_AND_MEAN /DNDEBUG /I. main.cpp utils.cpp /link setupapi.lib cfgmgr32.lib kernel32.lib user32.lib advapi32.lib /OUT:"..\bin\stellar-recovery.exe"
if %ERRORLEVEL% equ 0 (
    echo Build successful!
    cd ..
    goto :build_success
) else (
    echo Build failed!
    cd ..
    goto :build_failed
)

:build_mingw
echo.
echo Building with MinGW-w64 compiler...
cd src
if not exist "obj" mkdir obj
g++ -std=c++17 -Wall -Wextra -O2 -DWIN32_LEAN_AND_MEAN -DNDEBUG -static-libgcc -static-libstdc++ main.cpp utils.cpp -o "..\bin\stellar-recovery.exe" -lsetupapi -lcfgmgr32 -lkernel32 -luser32 -ladvapi32
if %ERRORLEVEL% equ 0 (
    echo Build successful!
    cd ..
    goto :build_success
) else (
    echo Build failed!
    cd ..
    goto :build_failed
)

:build_cmake
echo.
echo Building with CMake...
if not exist "build" mkdir build
cd build
cmake ..\src -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    cd ..
    goto :build_failed
)
cmake --build . --config Release
if %ERRORLEVEL% equ 0 (
    echo Build successful!
    cd ..
    goto :build_success
) else (
    echo Build failed!
    cd ..
    goto :build_failed
)

:build_success
echo.
echo ========================================
echo  Build Completed Successfully!
echo ========================================
echo.
echo Output: bin\stellar-recovery.exe
if exist "bin\stellar-recovery.exe" (
    echo File size: 
    dir "bin\stellar-recovery.exe" | find ".exe"
)
echo.
echo You can now run the application using:
echo - run.bat
echo - bin\stellar-recovery.exe
echo.
goto :end

:build_failed
echo.
echo ========================================
echo  Build Failed!
echo ========================================
echo.
echo Please check the following:
echo 1. All required dependencies are installed
echo 2. Compiler is properly configured
echo 3. Windows SDK is available
echo 4. Source files are not corrupted
echo.
goto :end

:no_build
echo.
echo ========================================
echo  Binary Distribution Detected
echo ========================================
echo.
echo This appears to be a binary distribution of Stellar Data Recovery Pro.
echo No build is required - simply place the executable in the 'bin' directory.
echo.
echo Instructions:
echo 1. Download the Stellar Data Recovery Pro executable
echo 2. Place it in the 'bin' directory as 'stellar-recovery.exe'
echo 3. Run 'run.bat' to launch the application
echo.

:end
echo.
pause