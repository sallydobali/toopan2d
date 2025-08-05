#ifndef RENDERER_H
#define RENDERER_H

#include "game_engine.h"

typedef struct {
    GLuint program;
    GLint position_attr;
    GLint color_attr;
    GLint mvp_uniform;
} Shader;

typedef struct {
    GLuint vbo;
    GLuint ibo;
    int vertex_count;
    int index_count;
} Mesh;

// Renderer functions
int renderer_init(void);
void renderer_shutdown(void);
void renderer_begin_frame(void);
void renderer_end_frame(void);

// Shader functions
int shader_create(Shader* shader, const char* vertex_src, const char* fragment_src);
void shader_destroy(Shader* shader);
void shader_use(const Shader* shader);

// Mesh functions
void mesh_create_quad(Mesh* mesh, float width, float height);
void mesh_create_circle(Mesh* mesh, float radius, int segments);
void mesh_destroy(Mesh* mesh);
void mesh_render(const Mesh* mesh, const Mat4* mvp);

// Drawing functions
void draw_field(void);
void draw_players(void);
void draw_ball(void);
void draw_ui(void);

extern Shader g_basic_shader;
extern Mesh g_quad_mesh;
extern Mesh g_circle_mesh;

#endif