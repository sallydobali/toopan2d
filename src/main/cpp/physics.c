#include "physics.h"

void physics_update(float delta_time) {
    // Update ball physics
    Ball* ball = &g_game_state.ball;
    
    // Apply gravity if ball is in the air
    if (ball->position.z > 0.0f) {
        ball->velocity.z += GRAVITY * delta_time;
    }
    
    // Update ball position
    vec3_scale(&ball->velocity, &ball->velocity, 1.0f);
    Vec3 delta_pos;
    vec3_scale(&delta_pos, &ball->velocity, delta_time);
    vec3_add(&ball->position, &ball->position, &delta_pos);
    
    // Ball ground collision
    if (ball->position.z <= 0.0f) {
        ball->position.z = 0.0f;
        if (ball->velocity.z < 0.0f) {
            ball->velocity.z = -ball->velocity.z * BALL_BOUNCE;
        }
    }
    
    // Apply friction to ball
    physics_apply_friction(&ball->velocity, FRICTION);
    
    // Keep ball in field bounds
    physics_keep_in_bounds(&ball->position, ball->radius,
                          -g_game_state.field_width/2, g_game_state.field_width/2,
                          -g_game_state.field_height/2, g_game_state.field_height/2);
    
    // Update player physics
    for (int i = 0; i < 6; i++) {
        Player* player = &g_game_state.players[i];
        
        // Update player position
        Vec3 delta_pos;
        vec3_scale(&delta_pos, &player->velocity, delta_time);
        vec3_add(&player->position, &player->position, &delta_pos);
        
        // Apply friction to player
        physics_apply_friction(&player->velocity, FRICTION);
        
        // Keep player in bounds
        physics_keep_in_bounds(&player->position, player->radius,
                              -g_game_state.field_width/2, g_game_state.field_width/2,
                              -g_game_state.field_height/2, g_game_state.field_height/2);
        
        // Check collision with ball
        if (physics_check_collision_circle(&player->position, player->radius,
                                          &ball->position, ball->radius)) {
            // Simple collision response - push ball away from player
            Vec3 direction = {ball->position.x - player->position.x,
                             ball->position.y - player->position.y,
                             0.0f};
            vec3_normalize(&direction);
            
            // Add some upward velocity for 2.5D effect
            direction.z = 0.3f;
            
            // Apply impulse to ball
            vec3_scale(&direction, &direction, 8.0f);
            vec3_add(&ball->velocity, &ball->velocity, &direction);
            
            // Separate ball from player
            Vec3 separation;
            vec3_scale(&separation, &direction, 0.1f);
            vec3_add(&ball->position, &ball->position, &separation);
        }
    }
    
    // Check player-player collisions
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            Player* p1 = &g_game_state.players[i];
            Player* p2 = &g_game_state.players[j];
            
            if (physics_check_collision_circle(&p1->position, p1->radius,
                                              &p2->position, p2->radius)) {
                // Simple separation
                Vec3 direction = {p2->position.x - p1->position.x,
                                 p2->position.y - p1->position.y,
                                 0.0f};
                vec3_normalize(&direction);
                
                Vec3 separation;
                vec3_scale(&separation, &direction, 0.05f);
                vec3_add(&p2->position, &p2->position, &separation);
                
                vec3_scale(&separation, &separation, -1.0f);
                vec3_add(&p1->position, &p1->position, &separation);
            }
        }
    }
}

void physics_apply_friction(Vec3* velocity, float friction) {
    vec3_scale(velocity, velocity, friction);
    
    // Stop very small velocities
    if (vec3_length(velocity) < 0.01f) {
        velocity->x = velocity->y = velocity->z = 0.0f;
    }
}

int physics_check_collision_circle(const Vec3* pos1, float radius1,
                                  const Vec3* pos2, float radius2) {
    Vec3 diff = {pos2->x - pos1->x, pos2->y - pos1->y, pos2->z - pos1->z};
    float distance = vec3_length(&diff);
    return distance < (radius1 + radius2);
}

void physics_resolve_collision(Vec3* pos1, Vec3* vel1, float mass1,
                              Vec3* pos2, Vec3* vel2, float mass2) {
    // Simple elastic collision resolution
    Vec3 direction = {pos2->x - pos1->x, pos2->y - pos1->y, pos2->z - pos1->z};
    vec3_normalize(&direction);
    
    // Relative velocity
    Vec3 rel_vel = {vel1->x - vel2->x, vel1->y - vel2->y, vel1->z - vel2->z};
    float speed = rel_vel.x * direction.x + rel_vel.y * direction.y + rel_vel.z * direction.z;
    
    if (speed < 0) return; // Objects separating
    
    // Collision impulse
    float impulse = 2 * speed / (mass1 + mass2);
    
    Vec3 impulse_vec;
    vec3_scale(&impulse_vec, &direction, impulse * mass2);
    vec3_add(vel1, vel1, &impulse_vec);
    
    vec3_scale(&impulse_vec, &direction, -impulse * mass1);
    vec3_add(vel2, vel2, &impulse_vec);
}

void physics_keep_in_bounds(Vec3* position, float radius,
                           float min_x, float max_x, float min_y, float max_y) {
    if (position->x - radius < min_x) {
        position->x = min_x + radius;
    }
    if (position->x + radius > max_x) {
        position->x = max_x - radius;
    }
    if (position->y - radius < min_y) {
        position->y = min_y + radius;
    }
    if (position->y + radius > max_y) {
        position->y = max_y - radius;
    }
}