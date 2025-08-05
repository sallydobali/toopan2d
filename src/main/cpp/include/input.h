#ifndef INPUT_H
#define INPUT_H

#include "game_engine.h"

typedef struct {
    Vec2 touch_pos;
    int is_touching;
    int selected_player;
} InputState;

// Input functions
void input_init(void);
void input_handle_touch(float x, float y, int action);
void input_update(void);
Player* input_get_nearest_player(float x, float y);

extern InputState g_input_state;

#endif