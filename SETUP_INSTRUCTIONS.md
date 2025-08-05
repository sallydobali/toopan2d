# Android Studio Setup and Build Instructions

Since Android SDK/NDK tools are not currently available in this environment, here are the complete instructions to set up and build the Toopan2D project:

## Prerequisites Installation

### 1. Install Android Studio
1. Download Android Studio from: https://developer.android.com/studio
2. Install with default settings
3. Launch Android Studio and complete the setup wizard

### 2. Install NDK and CMake
1. Open Android Studio
2. Go to `File > Settings` (or `Android Studio > Preferences` on Mac)
3. Navigate to `Appearance & Behavior > System Settings > Android SDK`
4. Click on `SDK Tools` tab
5. Check these items:
   - ✅ NDK (Side by side)
   - ✅ CMake
   - ✅ LLDB
6. Click `Apply` and `OK` to install

### 3. Configure Environment Variables (Optional but recommended)
Add these to your system PATH:
```
ANDROID_HOME=C:\Users\%USERNAME%\AppData\Local\Android\Sdk
ANDROID_NDK_HOME=%ANDROID_HOME%\ndk\[version]
```

## Building the Project

### Method 1: Android Studio (Recommended)
1. **Open Project**:
   - Launch Android Studio
   - Click "Open an existing Android Studio project"
   - Navigate to the `toopan2d` folder and select it

2. **Sync Project**:
   - Android Studio will automatically detect the project
   - Click "Sync Now" when prompted
   - Wait for Gradle sync to complete (may take a few minutes first time)

3. **Build Project**:
   - Click `Build > Make Project` or press `Ctrl+F9`
   - Wait for build to complete

4. **Run on Device/Emulator**:
   - Connect an Android device via USB (with Developer Options enabled)
   - OR create an Android Virtual Device (AVD) in Android Studio
   - Click the green "Run" button or press `Shift+F10`
   - Select your target device
   - The app will install and launch automatically

### Method 2: Command Line (Advanced)
```bash
# Navigate to project directory
cd /path/to/toopan2d

# Build debug APK
./gradlew assembleDebug

# Install on connected device
./gradlew installDebug

# Or build and install in one step
./gradlew installDebug
```

## Troubleshooting

### Common Issues:

1. **"NDK not found"**:
   - Install NDK through SDK Manager in Android Studio
   - Verify NDK path in `local.properties`

2. **"CMake not found"**:
   - Install CMake through SDK Manager
   - Check CMake version in `CMakeLists.txt` matches installed version

3. **Build fails with "OpenGL not found"**:
   - This is normal - OpenGL ES headers come with the Android NDK
   - Make sure you're building for Android target, not desktop

4. **"Gradle sync failed"**:
   - Check internet connection
   - Try `File > Invalidate Caches and Restart`

### Project Structure Verification:
```
toopan2d/
├── build.gradle              ✅ Android build config
├── CMakeLists.txt            ✅ NDK build config
├── gradle.properties         ✅ Gradle settings
├── src/main/
│   ├── AndroidManifest.xml   ✅ App manifest
│   ├── java/                 ✅ Java source
│   ├── cpp/                  ✅ C source files
│   └── res/                  ✅ Android resources
└── README.md                 ✅ Documentation
```

## Expected Build Output

When successful, you should see:
- APK file generated in `build/outputs/apk/debug/`
- Native libraries in `build/intermediates/cmake/`
- App installs and runs on device showing green soccer field

## Game Controls (Once Running)
- Touch and drag to move your team's players (red/white circles)
- Players automatically kick the ball when they collide with it
- Score goals by getting the ball into the opponent's goal area
- AI controls the opposing team (black/red circles)

## Performance Notes
- Target: 60 FPS on mid-range Android devices (API 21+)
- Minimum requirements: OpenGL ES 2.0 support
- Recommended: 2GB RAM, ARM64 processor