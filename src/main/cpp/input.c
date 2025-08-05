#include "input.h"
#include <float.h>

InputState g_input_state;

void input_init(void) {
    g_input_state.touch_pos.x = 0.0f;
    g_input_state.touch_pos.y = 0.0f;
    g_input_state.is_touching = 0;
    g_input_state.selected_player = -1;
}

void input_handle_touch(float x, float y, int action) {
    g_input_state.touch_pos.x = x;
    g_input_state.touch_pos.y = y;
    
    if (action == 0) { // ACTION_DOWN
        g_input_state.is_touching = 1;
        
        // Find nearest player to touch point
        Player* nearest = input_get_nearest_player(x, y);
        if (nearest) {
            g_input_state.selected_player = nearest - g_game_state.players;
        }
    } else if (action == 1) { // ACTION_UP
        g_input_state.is_touching = 0;
        g_input_state.selected_player = -1;
    } else if (action == 2) { // ACTION_MOVE
        // Continue tracking touch movement
    }
}

void input_update(void) {
    if (g_input_state.is_touching && g_input_state.selected_player >= 0) {
        Player* selected = &g_game_state.players[g_input_state.selected_player];
        
        // Calculate direction from player to touch point
        Vec3 direction = {
            g_input_state.touch_pos.x - selected->position.x,
            g_input_state.touch_pos.y - selected->position.y,
            0.0f
        };
        
        float distance = vec3_length(&direction);
        if (distance > 0.1f) { // Dead zone
            vec3_normalize(&direction);
            
            // Apply movement velocity
            vec3_scale(&direction, &direction, PLAYER_SPEED);
            selected->velocity = direction;
        }
    }
}

Player* input_get_nearest_player(float x, float y) {
    Player* nearest = NULL;
    float min_distance = FLT_MAX;
    
    // Only allow control of team A players (first 3)
    for (int i = 0; i < 3; i++) {
        Player* player = &g_game_state.players[i];
        
        float dx = x - player->position.x;
        float dy = y - player->position.y;
        float distance = sqrtf(dx * dx + dy * dy);
        
        if (distance < min_distance && distance < 2.0f) { // Within selection range
            min_distance = distance;
            nearest = player;
        }
    }
    
    return nearest;
}