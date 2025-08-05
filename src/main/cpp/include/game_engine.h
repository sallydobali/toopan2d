#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <GLES2/gl2.h>
#include <android/log.h>
#include <jni.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LOG_TAG "Toopan2D"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    float m[16];
} Mat4;

typedef struct {
    Vec3 position;
    Vec3 velocity;
    float radius;
    int team; // 0 = team A, 1 = team B
} Player;

typedef struct {
    Vec3 position;
    Vec3 velocity;
    float radius;
} Ball;

typedef struct {
    Player players[6]; // 3 players per team
    Ball ball;
    int score[2];
    float field_width;
    float field_height;
    int screen_width;
    int screen_height;
} GameState;

// Game engine functions
void game_init(void);
void game_resize(int width, int height);
void game_update(float delta_time);
void game_render(void);
void game_touch(float x, float y, int action);

// Math utilities
void vec3_add(Vec3* result, const Vec3* a, const Vec3* b);
void vec3_scale(Vec3* result, const Vec3* v, float scale);
float vec3_length(const Vec3* v);
void vec3_normalize(Vec3* v);

void mat4_identity(Mat4* m);
void mat4_perspective(Mat4* m, float fov, float aspect, float near, float far);
void mat4_lookat(Mat4* m, const Vec3* eye, const Vec3* center, const Vec3* up);
void mat4_multiply(Mat4* result, const Mat4* a, const Mat4* b);

extern GameState g_game_state;

// Function declarations for other modules
void update_ai_players(float delta_time);
void update_ball_physics(float delta_time);
void check_ball_out_of_bounds(void);
void check_goals(void);
void reset_ball_position(void);
void reset_player_positions(void);

#endif