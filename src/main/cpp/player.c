#include "game_engine.h"

// Simple AI for computer-controlled players (Team B)
void update_ai_players(float delta_time) {
    Ball* ball = &g_game_state.ball;
    
    // Update AI for Team B players (indices 3, 4, 5)
    for (int i = 3; i < 6; i++) {
        Player* player = &g_game_state.players[i];
        
        // Simple AI: move towards ball
        Vec3 to_ball = {
            ball->position.x - player->position.x,
            ball->position.y - player->position.y,
            0.0f
        };
        
        float distance_to_ball = vec3_length(&to_ball);
        
        if (distance_to_ball > 1.0f) { // Don't crowd the ball
            vec3_normalize(&to_ball);
            vec3_scale(&to_ball, &to_ball, PLAYER_SPEED * 0.7f); // AI is slightly slower
            player->velocity = to_ball;
        } else {
            // Stop when close to ball
            player->velocity.x = 0.0f;
            player->velocity.y = 0.0f;
            player->velocity.z = 0.0f;
        }
    }
}

void reset_player_positions(void) {
    // Reset Team A (left side)
    for (int i = 0; i < 3; i++) {
        g_game_state.players[i].position = (Vec3){-8.0f + i * 2.0f, -4.0f + i * 4.0f, 0.0f};
        g_game_state.players[i].velocity = (Vec3){0.0f, 0.0f, 0.0f};
    }
    
    // Reset Team B (right side)
    for (int i = 0; i < 3; i++) {
        g_game_state.players[i + 3].position = (Vec3){8.0f - i * 2.0f, -4.0f + i * 4.0f, 0.0f};
        g_game_state.players[i + 3].velocity = (Vec3){0.0f, 0.0f, 0.0f};
    }
}