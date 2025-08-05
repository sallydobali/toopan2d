#include "game_engine.h"
#include "renderer.h"
#include "physics.h"
#include "input.h"

GameState g_game_state;

void game_init(void) {
    LOGI("Initializing game engine");
    
    // Initialize renderer
    if (!renderer_init()) {
        LOGE("Failed to initialize renderer");
        return;
    }
    
    // Initialize input
    input_init();
    
    // Initialize game state
    g_game_state.field_width = 20.0f;
    g_game_state.field_height = 12.0f;
    g_game_state.score[0] = 0;
    g_game_state.score[1] = 0;
    
    // Initialize ball
    g_game_state.ball.position = (Vec3){0.0f, 0.0f, 0.0f};
    g_game_state.ball.velocity = (Vec3){0.0f, 0.0f, 0.0f};
    g_game_state.ball.radius = 0.3f;
    
    // Initialize players - Team A (left side)
    for (int i = 0; i < 3; i++) {
        g_game_state.players[i].team = 0;
        g_game_state.players[i].radius = 0.5f;
        g_game_state.players[i].position = (Vec3){-8.0f + i * 2.0f, -4.0f + i * 4.0f, 0.0f};
        g_game_state.players[i].velocity = (Vec3){0.0f, 0.0f, 0.0f};
    }
    
    // Initialize players - Team B (right side)
    for (int i = 0; i < 3; i++) {
        g_game_state.players[i + 3].team = 1;
        g_game_state.players[i + 3].radius = 0.5f;
        g_game_state.players[i + 3].position = (Vec3){8.0f - i * 2.0f, -4.0f + i * 4.0f, 0.0f};
        g_game_state.players[i + 3].velocity = (Vec3){0.0f, 0.0f, 0.0f};
    }
    
    LOGI("Game engine initialized successfully");
}

void game_resize(int width, int height) {
    g_game_state.screen_width = width;
    g_game_state.screen_height = height;
    glViewport(0, 0, width, height);
}

void game_update(float delta_time) {
    // Update input
    input_update();
    
    // Update physics
    physics_update(delta_time);
    
    // Update AI players
    update_ai_players(delta_time);
    
    // Update ball physics
    update_ball_physics(delta_time);
    
    // Check field boundaries and goals  
    check_ball_out_of_bounds();
    check_goals();
}

void game_render(void) {
    renderer_begin_frame();
    
    draw_field();
    draw_players();
    draw_ball();
    draw_ui();
    
    renderer_end_frame();
}

void game_touch(float x, float y, int action) {
    // Convert screen coordinates to world coordinates
    float world_x = (x / g_game_state.screen_width - 0.5f) * g_game_state.field_width;
    float world_y = (0.5f - y / g_game_state.screen_height) * g_game_state.field_height;
    
    input_handle_touch(world_x, world_y, action);
}

// Math utility implementations
void vec3_add(Vec3* result, const Vec3* a, const Vec3* b) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}

void vec3_scale(Vec3* result, const Vec3* v, float scale) {
    result->x = v->x * scale;
    result->y = v->y * scale;
    result->z = v->z * scale;
}

float vec3_length(const Vec3* v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vec3_normalize(Vec3* v) {
    float len = vec3_length(v);
    if (len > 0.0f) {
        v->x /= len;
        v->y /= len;
        v->z /= len;
    }
}

void mat4_identity(Mat4* m) {
    memset(m->m, 0, sizeof(m->m));
    m->m[0] = m->m[5] = m->m[10] = m->m[15] = 1.0f;
}

void mat4_perspective(Mat4* m, float fov, float aspect, float near, float far) {
    float f = 1.0f / tanf(fov * 0.5f);
    memset(m->m, 0, sizeof(m->m));
    
    m->m[0] = f / aspect;
    m->m[5] = f;
    m->m[10] = (far + near) / (near - far);
    m->m[11] = -1.0f;
    m->m[14] = (2.0f * far * near) / (near - far);
}

void mat4_lookat(Mat4* m, const Vec3* eye, const Vec3* center, const Vec3* up) {
    Vec3 f = {center->x - eye->x, center->y - eye->y, center->z - eye->z};
    vec3_normalize(&f);
    
    Vec3 s = {f.y * up->z - f.z * up->y, f.z * up->x - f.x * up->z, f.x * up->y - f.y * up->x};
    vec3_normalize(&s);
    
    Vec3 u = {s.y * f.z - s.z * f.y, s.z * f.x - s.x * f.z, s.x * f.y - s.y * f.x};
    
    mat4_identity(m);
    m->m[0] = s.x;
    m->m[4] = s.y;
    m->m[8] = s.z;
    m->m[1] = u.x;
    m->m[5] = u.y;
    m->m[9] = u.z;
    m->m[2] = -f.x;
    m->m[6] = -f.y;
    m->m[10] = -f.z;
    m->m[12] = -(s.x * eye->x + s.y * eye->y + s.z * eye->z);
    m->m[13] = -(u.x * eye->x + u.y * eye->y + u.z * eye->z);
    m->m[14] = f.x * eye->x + f.y * eye->y + f.z * eye->z;
}

void mat4_multiply(Mat4* result, const Mat4* a, const Mat4* b) {
    Mat4 temp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp.m[i * 4 + j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                temp.m[i * 4 + j] += a->m[i * 4 + k] * b->m[k * 4 + j];
            }
        }
    }
    *result = temp;
}