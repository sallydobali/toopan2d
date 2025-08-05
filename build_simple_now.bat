@echo off
echo ================================
echo Simple Toopan2D APK Builder
echo (Java-only version)
echo ================================
echo.

echo Checking Java...
java -version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ Java not found!
    echo Please install Java first.
    pause
    exit /b 1
) else (
    echo ✅ Java found
)

echo.
echo Preparing simple build...

REM Backup original files
if exist build.gradle (
    copy build.gradle build.gradle.backup >nul
    echo ✅ Original build.gradle backed up
)

REM Use simple build configuration (no NDK)
copy build_simple.gradle build.gradle >nul
echo ✅ Using simplified build configuration

REM Remove NDK references temporarily
if exist CMakeLists.txt (
    ren CMakeLists.txt CMakeLists.txt.backup >nul
    echo ✅ NDK configuration disabled
)

echo.
echo Building APK...
echo This may take a few minutes...
echo.

REM Set JAVA_HOME if not set
if not defined JAVA_HOME (
    set "JAVA_HOME=C:\Program Files\Eclipse Adoptium\jdk-17.0.16.8-hotspot"
    echo ✅ JAVA_HOME set temporarily
)

REM Build using Gradle Wrapper
if exist gradlew.bat (
    echo Using Gradle Wrapper...
    call gradlew.bat clean assembleDebug --stacktrace
    set BUILD_RESULT=%errorlevel%
) else (
    echo ❌ Gradle wrapper not found!
    echo Creating minimal Gradle wrapper...
    
    REM Create basic gradle wrapper
    mkdir gradle\wrapper 2>nul
    echo distributionBase=GRADLE_USER_HOME > gradle\wrapper\gradle-wrapper.properties
    echo distributionPath=wrapper/dists >> gradle\wrapper\gradle-wrapper.properties
    echo distributionUrl=https://services.gradle.org/distributions/gradle-8.0-bin.zip >> gradle\wrapper\gradle-wrapper.properties
    echo zipStoreBase=GRADLE_USER_HOME >> gradle\wrapper\gradle-wrapper.properties
    echo zipStorePath=wrapper/dists >> gradle\wrapper\gradle-wrapper.properties
    
    echo Gradle wrapper created. Please run this script again.
    set BUILD_RESULT=1
)

echo.
REM Restore original files
if exist build.gradle.backup (
    copy build.gradle.backup build.gradle >nul
    del build.gradle.backup >nul
    echo ✅ Original build.gradle restored
)

if exist CMakeLists.txt.backup (
    ren CMakeLists.txt.backup CMakeLists.txt >nul
    echo ✅ NDK configuration restored
)

if %BUILD_RESULT% equ 0 (
    echo.
    echo ✅ BUILD SUCCESSFUL!
    echo.
    echo APK Location:
    if exist "build\outputs\apk\debug\" (
        for %%f in ("build\outputs\apk\debug\*.apk") do (
            echo 📱 APK: %%~nxf
            echo 📁 Path: %%~ff
        )
    ) else (
        echo ❌ APK directory not found
    )
) else (
    echo.
    echo ❌ Build failed!
    echo.
    echo Possible solutions:
    echo 1. Make sure Java 17 is properly installed
    echo 2. Check internet connection for Gradle download
    echo 3. Try running as Administrator
    echo 4. Use GitHub Actions for online building
)

echo.
echo Done!
pause