#ifndef PHYSICS_H
#define PHYSICS_H

#include "game_engine.h"

// Physics constants
#define GRAVITY -9.81f
#define FRICTION 0.95f
#define BALL_BOUNCE 0.8f
#define PLAYER_SPEED 5.0f

// Physics functions
void physics_update(float delta_time);
void physics_apply_friction(Vec3* velocity, float friction);
int physics_check_collision_circle(const Vec3* pos1, float radius1, 
                                  const Vec3* pos2, float radius2);
void physics_resolve_collision(Vec3* pos1, Vec3* vel1, float mass1,
                              Vec3* pos2, Vec3* vel2, float mass2);
void physics_keep_in_bounds(Vec3* position, float radius, 
                           float min_x, float max_x, float min_y, float max_y);

#endif