@echo off
echo ================================
echo Quick Android Development Setup
echo ================================
echo.

echo This script will help you install the required tools quickly.
echo.

echo Step 1: Install Java 17
echo ------------------------
echo Please download and install Java 17 from:
echo https://adoptium.net/temurin/releases/?version=17
echo.
echo After installation, press any key to continue...
pause
echo.

echo Step 2: Install Android Command Line Tools
echo ------------------------------------------
echo Downloading Android SDK Command Line Tools...

if not exist "android-sdk" mkdir android-sdk
cd android-sdk

if not exist "cmdline-tools" (
    echo Downloading Android SDK...
    powershell -Command "Invoke-WebRequest -Uri 'https://dl.google.com/android/repository/commandlinetools-win-9477386_latest.zip' -OutFile 'cmdline-tools.zip'"
    
    echo Extracting...
    powershell -Command "Expand-Archive -Path 'cmdline-tools.zip' -DestinationPath '.'"
    
    if exist "cmdline-tools" (
        mkdir cmdline-tools-temp
        move cmdline-tools cmdline-tools-temp\latest
        move cmdline-tools-temp cmdline-tools
    )
    
    del cmdline-tools.zip
    echo ✅ Android SDK Command Line Tools installed
) else (
    echo ✅ Android SDK Command Line Tools already installed
)

cd ..

echo.
echo Step 3: Set Environment Variables
echo --------------------------------
set ANDROID_HOME=%CD%\android-sdk
set PATH=%PATH%;%ANDROID_HOME%\cmdline-tools\latest\bin;%ANDROID_HOME%\platform-tools

echo ANDROID_HOME set to: %ANDROID_HOME%
echo.

echo Step 4: Install Required SDK Components
echo ---------------------------------------
echo Installing Android SDK components...

%ANDROID_HOME%\cmdline-tools\latest\bin\sdkmanager.bat --licenses
%ANDROID_HOME%\cmdline-tools\latest\bin\sdkmanager.bat "platform-tools" "platforms;android-33" "build-tools;33.0.0" "ndk;25.1.8937393" "cmake;3.18.1"

echo.
echo ✅ Setup complete!
echo.
echo Now you can build the APK by running:
echo build_apk.bat
echo.
pause