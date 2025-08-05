#include "game_engine.h"

void update_ball_physics(float delta_time) {
    Ball* ball = &g_game_state.ball;
    
    // Apply air resistance
    if (ball->position.z > 0.0f) {
        vec3_scale(&ball->velocity, &ball->velocity, 0.98f);
    }
    
    // Bounce off walls
    if (ball->position.x <= -g_game_state.field_width/2 + ball->radius) {
        ball->velocity.x = fabsf(ball->velocity.x);
        ball->position.x = -g_game_state.field_width/2 + ball->radius;
    }
    if (ball->position.x >= g_game_state.field_width/2 - ball->radius) {
        ball->velocity.x = -fabsf(ball->velocity.x);
        ball->position.x = g_game_state.field_width/2 - ball->radius;
    }
    
    if (ball->position.y <= -g_game_state.field_height/2 + ball->radius) {
        ball->velocity.y = fabsf(ball->velocity.y);
        ball->position.y = -g_game_state.field_height/2 + ball->radius;
    }
    if (ball->position.y >= g_game_state.field_height/2 - ball->radius) {
        ball->velocity.y = -fabsf(ball->velocity.y);
        ball->position.y = g_game_state.field_height/2 - ball->radius;
    }
}

void reset_ball_position(void) {
    g_game_state.ball.position = (Vec3){0.0f, 0.0f, 0.0f};
    g_game_state.ball.velocity = (Vec3){0.0f, 0.0f, 0.0f};
}