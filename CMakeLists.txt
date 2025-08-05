cmake_minimum_required(VERSION 3.18.1)

project("toopan2d")

# Find required packages
find_library(log-lib log)
find_library(android-lib android)
find_library(EGL-lib EGL)
find_library(GLESv2-lib GLESv2)

# Add source files
add_library(toopan2d SHARED
    src/main/cpp/main.c
    src/main/cpp/game_engine.c
    src/main/cpp/renderer.c
    src/main/cpp/soccer_field.c
    src/main/cpp/player.c
    src/main/cpp/ball.c
    src/main/cpp/physics.c
    src/main/cpp/input.c
)

# Include directories
target_include_directories(toopan2d PRIVATE
    src/main/cpp/include
)

# Link libraries
target_link_libraries(toopan2d
    ${log-lib}
    ${android-lib}
    ${EGL-lib}
    ${GLESv2-lib}
)