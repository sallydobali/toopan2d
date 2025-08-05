# Toopan2D - 2.5D Soccer Game for Android

A 2.5D soccer game built with C and OpenGL ES for Android using the Android NDK.

## Features

- 2.5D perspective soccer gameplay
- Touch controls for player movement
- Physics-based ball movement with gravity and bouncing
- AI-controlled opponent team
- Real-time collision detection
- Score tracking

## Game Controls

- **Touch and drag**: Select and move your team's players (red/white team)
- **Player collision with ball**: Kick the ball by running into it
- **Goal**: Score by getting the ball into the opponent's goal

## Technical Details

- **Engine**: Custom C game engine with OpenGL ES 2.0
- **Physics**: Basic 2D physics with 3D ball trajectories
- **Rendering**: 2.5D perspective with camera positioned above the field
- **Platform**: Android (API level 21+)

## Project Structure

```
toopan2d/
├── src/main/
│   ├── cpp/
│   │   ├── include/          # Header files
│   │   ├── main.c           # JNI interface
│   │   ├── game_engine.c    # Core game engine
│   │   ├── renderer.c       # OpenGL rendering
│   │   ├── physics.c        # Physics simulation
│   │   ├── input.c          # Touch input handling
│   │   ├── soccer_field.c   # Field logic
│   │   ├── player.c         # Player AI
│   │   └── ball.c           # Ball physics
│   ├── java/                # Android Java code
│   └── res/                 # Android resources
├── CMakeLists.txt           # CMake build configuration
└── build.gradle             # Android build configuration
```

## Building

### Prerequisites

- Android Studio with NDK
- CMake 3.18.1 or higher
- Android SDK (API level 21+)

### Build Steps

1. Open the project in Android Studio
2. Sync the project to download dependencies
3. Build and run on an Android device or emulator

### Manual Build (Command Line)

```bash
# Build the native library
cd /path/to/toopan2d
./gradlew assembleDebug

# Install on connected device
./gradlew installDebug
```

## Game Architecture

### Core Components

1. **Game Engine** (`game_engine.c`): Main game loop, state management
2. **Renderer** (`renderer.c`): OpenGL ES rendering, shaders, meshes
3. **Physics** (`physics.c`): Collision detection, movement simulation
4. **Input** (`input.c`): Touch input processing, player selection
5. **AI** (`player.c`): Computer player behavior

### Rendering Pipeline

1. Set up 2.5D camera view (perspective projection + elevated camera)
2. Render soccer field background
3. Render players as circles with team colors
4. Render ball with physics-based position
5. Handle UI elements (score display)

### Physics System

- **Ball Physics**: Gravity, bouncing, friction, wall collisions
- **Player Movement**: Touch-controlled movement with velocity
- **Collisions**: Circle-based collision detection between players and ball
- **Field Boundaries**: Keep all objects within field limits

## Customization

### Modifying Game Parameters

Edit constants in `src/main/cpp/include/physics.h`:

```c
#define GRAVITY -9.81f        // Ball gravity
#define FRICTION 0.95f        // Movement friction
#define BALL_BOUNCE 0.8f      // Ball bounce factor
#define PLAYER_SPEED 5.0f     // Player movement speed
```

### Adding Features

- **Enhanced Graphics**: Add textures, better field rendering
- **Sound Effects**: Integrate OpenSL ES for audio
- **Game Modes**: Tournament, multiplayer, different field sizes
- **Better AI**: More sophisticated computer player behavior
- **UI Improvements**: Better score display, menus, settings

## License

This project is open source. Feel free to modify and distribute.

## Performance Notes

- Optimized for 60 FPS on mid-range Android devices
- Uses efficient circle-based collision detection
- Minimal memory allocations during gameplay
- OpenGL ES 2.0 compatible for broad device support