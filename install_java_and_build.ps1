# PowerShell script to install Java and build APK
Write-Host "================================" -ForegroundColor Green
Write-Host "Auto Java Install & APK Builder" -ForegroundColor Green  
Write-Host "================================" -ForegroundColor Green
Write-Host ""

# Check if Java is already installed
try {
    $javaVersion = java -version 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ Java is already installed" -ForegroundColor Green
        Write-Host $javaVersion[0]
    }
} catch {
    Write-Host "❌ Java not found, installing..." -ForegroundColor Yellow
    
    # Download Java 17
    $javaUrl = "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.9%2B9/OpenJDK17U-jdk_x64_windows_hotspot_17.0.9_9.msi"
    $javaInstaller = "$env:TEMP\openjdk17.msi"
    
    Write-Host "Downloading Java 17..." -ForegroundColor Yellow
    try {
        Invoke-WebRequest -Uri $javaUrl -OutFile $javaInstaller -UseBasicParsing
        Write-Host "✅ Java downloaded" -ForegroundColor Green
        
        Write-Host "Installing Java..." -ForegroundColor Yellow
        Start-Process msiexec.exe -ArgumentList "/i", $javaInstaller, "/quiet", "/norestart" -Wait
        Write-Host "✅ Java installed" -ForegroundColor Green
        
        # Update PATH
        $javaHome = "C:\Program Files\Eclipse Adoptium\jdk-17.0.9.9-hotspot"
        [Environment]::SetEnvironmentVariable("JAVA_HOME", $javaHome, "Machine")
        $env:JAVA_HOME = $javaHome
        $env:PATH = "$javaHome\bin;$env:PATH"
        
        Write-Host "✅ Java PATH updated" -ForegroundColor Green
    } catch {
        Write-Host "❌ Failed to install Java automatically" -ForegroundColor Red
        Write-Host "Please install Java manually from: https://adoptium.net/temurin/releases/?version=17" -ForegroundColor Yellow
        exit 1
    }
}

Write-Host ""
Write-Host "Building simple APK..." -ForegroundColor Yellow

# Use simple build configuration
if (Test-Path "build.gradle") {
    Copy-Item "build.gradle" "build.gradle.backup"
}
Copy-Item "build_simple.gradle" "build.gradle"

# Disable NDK temporarily
if (Test-Path "CMakeLists.txt") {
    Rename-Item "CMakeLists.txt" "CMakeLists.txt.backup"
}

Write-Host "✅ Using simplified build configuration" -ForegroundColor Green

# Build APK
try {
    if (Test-Path "gradlew.bat") {
        Write-Host "Using Gradle Wrapper..." -ForegroundColor Yellow
        & .\gradlew.bat clean assembleDebug
    } else {
        Write-Host "Using system Gradle..." -ForegroundColor Yellow  
        & gradle clean assembleDebug
    }
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "✅ BUILD SUCCESSFUL!" -ForegroundColor Green
        Write-Host ""
        
        $apkPath = "build\outputs\apk\debug"
        if (Test-Path $apkPath) {
            $apkFiles = Get-ChildItem "$apkPath\*.apk"
            foreach ($apk in $apkFiles) {
                Write-Host "📱 APK created: $($apk.FullName)" -ForegroundColor Cyan
            }
        }
    } else {
        Write-Host "❌ Build failed!" -ForegroundColor Red
    }
} catch {
    Write-Host "❌ Build error: $($_.Exception.Message)" -ForegroundColor Red
}

# Restore original files
if (Test-Path "build.gradle.backup") {
    Move-Item "build.gradle.backup" "build.gradle" -Force
}
if (Test-Path "CMakeLists.txt.backup") {
    Rename-Item "CMakeLists.txt.backup" "CMakeLists.txt"
}

Write-Host ""
Write-Host "Done! Check the build\outputs\apk\debug\ folder for your APK" -ForegroundColor Green