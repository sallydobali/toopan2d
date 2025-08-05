@echo off
echo ================================
echo Toopan2D APK Builder
echo ================================
echo.

echo Checking requirements...

REM Check Java
java -version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ Java not found
    echo.
    echo Installing Java...
    echo Please download and install Java 17 from:
    echo https://adoptium.net/temurin/releases/
    echo.
    pause
    exit /b 1
) else (
    echo ✅ Java found
)

REM Check Android SDK
if not exist "%ANDROID_HOME%" (
    echo ❌ Android SDK not found
    echo.
    echo Please set ANDROID_HOME environment variable
    echo Download Android SDK from: https://developer.android.com/studio/releases/platform-tools
    echo.
    pause
    exit /b 1
) else (
    echo ✅ Android SDK found at %ANDROID_HOME%
)

echo.
echo Building APK...
echo.

REM Build with Gradle
if exist gradlew.bat (
    echo Using Gradle Wrapper...
    gradlew.bat assembleDebug
) else (
    echo Using system Gradle...
    gradle assembleDebug
)

if %errorlevel% equ 0 (
    echo.
    echo ✅ Build successful!
    echo APK location: build\outputs\apk\debug\
    echo.
    dir build\outputs\apk\debug\*.apk
) else (
    echo.
    echo ❌ Build failed!
    echo Check the error messages above.
)

pause