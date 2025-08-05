@echo off
echo ================================
echo GitHub Preparation Tool
echo ================================
echo.

echo Preparing project for GitHub upload...
echo.

REM Create a summary of files
echo Creating file list...
echo # Toopan2D Project Files > FILES_LIST.txt
echo. >> FILES_LIST.txt
echo ## Main Files: >> FILES_LIST.txt
if exist build.gradle echo ✅ build.gradle >> FILES_LIST.txt
if exist build_simple.gradle echo ✅ build_simple.gradle >> FILES_LIST.txt
if exist CMakeLists.txt echo ✅ CMakeLists.txt >> FILES_LIST.txt
if exist gradlew.bat echo ✅ gradlew.bat >> FILES_LIST.txt
if exist AndroidManifest.xml echo ✅ AndroidManifest.xml >> FILES_LIST.txt

echo. >> FILES_LIST.txt
echo ## Source Code: >> FILES_LIST.txt
if exist "src\main\java" echo ✅ Java source files >> FILES_LIST.txt
if exist "src\main\cpp" echo ✅ C source files >> FILES_LIST.txt
if exist "src\main\res" echo ✅ Android resources >> FILES_LIST.txt

echo. >> FILES_LIST.txt
echo ## Build System: >> FILES_LIST.txt
if exist "gradle\wrapper" echo ✅ Gradle wrapper >> FILES_LIST.txt
if exist ".github\workflows" echo ✅ GitHub Actions >> FILES_LIST.txt

echo. >> FILES_LIST.txt
echo ## Documentation: >> FILES_LIST.txt
if exist README.md echo ✅ README.md >> FILES_LIST.txt
if exist GITHUB_GUIDE.md echo ✅ GITHUB_GUIDE.md >> FILES_LIST.txt

echo ✅ File list created: FILES_LIST.txt

echo.
echo Creating ZIP file for easy upload...
powershell -Command "Compress-Archive -Path * -DestinationPath toopan2d-project.zip -Force"

if exist toopan2d-project.zip (
    echo ✅ ZIP file created: toopan2d-project.zip
) else (
    echo ❌ Failed to create ZIP file
)

echo.
echo ================================
echo GitHub Upload Instructions:
echo ================================
echo.
echo 1. Go to github.com and create new repository
echo 2. Name it: toopan2d
echo 3. Make it Public (free)
echo 4. Upload toopan2d-project.zip OR drag individual files
echo 5. Commit with message: "Initial commit - Toopan2D Soccer Game"
echo 6. Go to Actions tab and watch the build
echo 7. Download APK from Artifacts section
echo.
echo For detailed guide, see: GITHUB_GUIDE.md
echo.
pause