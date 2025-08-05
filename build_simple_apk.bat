@echo off
echo ================================
echo Simple Toopan2D APK Builder
echo (Java-only version, no NDK needed)
echo ================================
echo.

echo Creating simple APK without C code...
echo.

REM Backup original build.gradle
if exist build.gradle (
    copy build.gradle build.gradle.backup
    echo ✅ Original build.gradle backed up
)

REM Use simple build.gradle
copy build_simple.gradle build.gradle
echo ✅ Using simplified build configuration

REM Remove NDK references from CMakeLists.txt temporarily
if exist CMakeLists.txt (
    ren CMakeLists.txt CMakeLists.txt.backup
    echo ✅ CMakeLists.txt temporarily disabled
)

echo.
echo Attempting to build APK...
echo.

REM Try different build methods
if exist gradlew.bat (
    echo Using Gradle Wrapper...
    gradlew.bat clean
    gradlew.bat assembleDebug
    set BUILD_RESULT=%errorlevel%
) else (
    echo Gradle wrapper not found, trying system gradle...
    gradle clean assembleDebug
    set BUILD_RESULT=%errorlevel%
)

REM Restore original files
if exist build.gradle.backup (
    copy build.gradle.backup build.gradle
    del build.gradle.backup
    echo ✅ Original build.gradle restored
)

if exist CMakeLists.txt.backup (
    ren CMakeLists.txt.backup CMakeLists.txt
    echo ✅ CMakeLists.txt restored
)

echo.
if %BUILD_RESULT% equ 0 (
    echo ✅ BUILD SUCCESSFUL!
    echo.
    echo APK Location:
    if exist "build\outputs\apk\debug\" (
        dir "build\outputs\apk\debug\*.apk" /b
        echo.
        echo Full path: %CD%\build\outputs\apk\debug\
    ) else (
        echo APK directory not found, but build was successful
    )
) else (
    echo ❌ Build failed!
    echo.
    echo Possible solutions:
    echo 1. Install Java 17: https://adoptium.net/temurin/releases/?version=17
    echo 2. Run quick_setup.bat to install Android SDK
    echo 3. Use GitHub Actions (upload to GitHub and build online)
)

echo.
pause