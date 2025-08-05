@echo off
echo ================================
echo Toopan2D Project Validation
echo ================================
echo.

echo Checking project structure...
echo.

if exist "CMakeLists.txt" (
    echo ✅ CMakeLists.txt found
) else (
    echo ❌ CMakeLists.txt missing
)

if exist "build.gradle" (
    echo ✅ build.gradle found  
) else (
    echo ❌ build.gradle missing
)

if exist "src\main\AndroidManifest.xml" (
    echo ✅ AndroidManifest.xml found
) else (
    echo ❌ AndroidManifest.xml missing
)

if exist "src\main\java\com\toopan2d\game\MainActivity.java" (
    echo ✅ MainActivity.java found
) else (
    echo ❌ MainActivity.java missing
)

if exist "src\main\cpp\main.c" (
    echo ✅ main.c found
) else (
    echo ❌ main.c missing
)

if exist "src\main\cpp\game_engine.c" (
    echo ✅ game_engine.c found
) else (
    echo ❌ game_engine.c missing
)

if exist "src\main\cpp\renderer.c" (
    echo ✅ renderer.c found
) else (
    echo ❌ renderer.c missing
)

if exist "src\main\cpp\include\game_engine.h" (
    echo ✅ game_engine.h found
) else (
    echo ❌ game_engine.h missing
)

echo.
echo ================================
echo Project validation complete!
echo ================================
echo.
echo To build this project:
echo 1. Install Android Studio
echo 2. Open this folder in Android Studio
echo 3. Sync project (installs NDK/CMake)
echo 4. Build and run on device/emulator
echo.
echo See SETUP_INSTRUCTIONS.md for detailed steps.
pause