#include "game_engine.h"
#include "renderer.h"

// Soccer field rendering and logic
void draw_field_lines(void) {
    // This function would draw the field lines, goals, etc.
    // For now, the basic field rendering is handled in renderer.c
    
    // TODO: Add field markings like:
    // - Center circle
    // - Goal areas
    // - Corner arcs
    // - Sidelines
}

void check_ball_out_of_bounds(void) {
    Ball* ball = &g_game_state.ball;
    
    // Check if ball is out of bounds
    if (ball->position.y < -g_game_state.field_height/2 || 
        ball->position.y > g_game_state.field_height/2) {
        // Ball is out - reset to center
        ball->position.x = 0.0f;
        ball->position.y = 0.0f;
        ball->position.z = 0.0f;
        ball->velocity.x = 0.0f;
        ball->velocity.y = 0.0f;
        ball->velocity.z = 0.0f;
    }
}

void check_goals(void) {
    Ball* ball = &g_game_state.ball;
    float goal_width = 3.0f; // Goal width
    
    // Check left goal (Team B scores)
    if (ball->position.x < -g_game_state.field_width/2 && 
        ball->position.y > -goal_width/2 && 
        ball->position.y < goal_width/2) {
        g_game_state.score[1]++;
        
        // Reset ball
        ball->position.x = 0.0f;
        ball->position.y = 0.0f;
        ball->position.z = 0.0f;
        ball->velocity.x = 0.0f;
        ball->velocity.y = 0.0f;
        ball->velocity.z = 0.0f;
        
        LOGI("Goal! Team B scores. Score: %d - %d", 
             g_game_state.score[0], g_game_state.score[1]);
    }
    
    // Check right goal (Team A scores)
    if (ball->position.x > g_game_state.field_width/2 && 
        ball->position.y > -goal_width/2 && 
        ball->position.y < goal_width/2) {
        g_game_state.score[0]++;
        
        // Reset ball
        ball->position.x = 0.0f;
        ball->position.y = 0.0f;
        ball->position.z = 0.0f;
        ball->velocity.x = 0.0f;
        ball->velocity.y = 0.0f;
        ball->velocity.z = 0.0f;
        
        LOGI("Goal! Team A scores. Score: %d - %d", 
             g_game_state.score[0], g_game_state.score[1]);
    }
}