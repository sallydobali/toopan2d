#include "renderer.h"

Shader g_basic_shader;
Mesh g_quad_mesh;
Mesh g_circle_mesh;

static const char* vertex_shader_src = 
    "attribute vec3 a_position;\n"
    "attribute vec4 a_color;\n"
    "uniform mat4 u_mvp;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "    gl_Position = u_mvp * vec4(a_position, 1.0);\n"
    "    v_color = a_color;\n"
    "}\n";

static const char* fragment_shader_src = 
    "precision mediump float;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "    gl_FragColor = v_color;\n"
    "}\n";

static GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint info_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1) {
            char* info_log = malloc(info_len);
            glGetShaderInfoLog(shader, info_len, NULL, info_log);
            LOGE("Shader compile error: %s", info_log);
            free(info_log);
        }
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

int renderer_init(void) {
    LOGI("Initializing renderer");
    
    // Enable depth testing and blending
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Create basic shader
    if (!shader_create(&g_basic_shader, vertex_shader_src, fragment_shader_src)) {
        LOGE("Failed to create basic shader");
        return 0;
    }
    
    // Create meshes
    mesh_create_quad(&g_quad_mesh, 1.0f, 1.0f);
    mesh_create_circle(&g_circle_mesh, 1.0f, 16);
    
    LOGI("Renderer initialized successfully");
    return 1;
}

void renderer_shutdown(void) {
    shader_destroy(&g_basic_shader);
    mesh_destroy(&g_quad_mesh);
    mesh_destroy(&g_circle_mesh);
}

void renderer_begin_frame(void) {
    glClearColor(0.2f, 0.6f, 0.2f, 1.0f); // Green field color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_end_frame(void) {
    // Frame is automatically presented by the GLSurfaceView
}

int shader_create(Shader* shader, const char* vertex_src, const char* fragment_src) {
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_src);
    if (!vertex_shader) return 0;
    
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_src);
    if (!fragment_shader) {
        glDeleteShader(vertex_shader);
        return 0;
    }
    
    shader->program = glCreateProgram();
    glAttachShader(shader->program, vertex_shader);
    glAttachShader(shader->program, fragment_shader);
    glLinkProgram(shader->program);
    
    GLint linked;
    glGetProgramiv(shader->program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint info_len = 0;
        glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1) {
            char* info_log = malloc(info_len);
            glGetProgramInfoLog(shader->program, info_len, NULL, info_log);
            LOGE("Program link error: %s", info_log);
            free(info_log);
        }
        glDeleteProgram(shader->program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return 0;
    }
    
    // Get attribute and uniform locations
    shader->position_attr = glGetAttribLocation(shader->program, "a_position");
    shader->color_attr = glGetAttribLocation(shader->program, "a_color");
    shader->mvp_uniform = glGetUniformLocation(shader->program, "u_mvp");
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return 1;
}

void shader_destroy(Shader* shader) {
    if (shader->program) {
        glDeleteProgram(shader->program);
        shader->program = 0;
    }
}

void shader_use(const Shader* shader) {
    glUseProgram(shader->program);
}

void mesh_create_quad(Mesh* mesh, float width, float height) {
    float half_w = width * 0.5f;
    float half_h = height * 0.5f;
    
    float vertices[] = {
        -half_w, -half_h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-left
         half_w, -half_h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
         half_w,  half_h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
        -half_w,  half_h, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f  // Top-left
    };
    
    unsigned short indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &mesh->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    mesh->vertex_count = 4;
    mesh->index_count = 6;
}

void mesh_create_circle(Mesh* mesh, float radius, int segments) {
    int vertex_count = segments + 1; // +1 for center vertex
    int vertex_size = 7; // 3 position + 4 color
    float* vertices = malloc(vertex_count * vertex_size * sizeof(float));
    
    // Center vertex
    vertices[0] = 0.0f; vertices[1] = 0.0f; vertices[2] = 0.0f;
    vertices[3] = 1.0f; vertices[4] = 1.0f; vertices[5] = 1.0f; vertices[6] = 1.0f;
    
    // Circle vertices
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        int idx = (i + 1) * vertex_size;
        vertices[idx + 0] = cosf(angle) * radius;
        vertices[idx + 1] = sinf(angle) * radius;
        vertices[idx + 2] = 0.0f;
        vertices[idx + 3] = 1.0f; vertices[idx + 4] = 1.0f; 
        vertices[idx + 5] = 1.0f; vertices[idx + 6] = 1.0f;
    }
    
    // Create indices for triangle fan
    int index_count = segments * 3;
    unsigned short* indices = malloc(index_count * sizeof(unsigned short));
    for (int i = 0; i < segments; i++) {
        indices[i * 3 + 0] = 0; // Center
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = (i + 1) % segments + 1;
    }
    
    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &mesh->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned short), indices, GL_STATIC_DRAW);
    
    mesh->vertex_count = vertex_count;
    mesh->index_count = index_count;
    
    free(vertices);
    free(indices);
}

void mesh_destroy(Mesh* mesh) {
    if (mesh->vbo) glDeleteBuffers(1, &mesh->vbo);
    if (mesh->ibo) glDeleteBuffers(1, &mesh->ibo);
    mesh->vbo = mesh->ibo = 0;
}

void mesh_render(const Mesh* mesh, const Mat4* mvp) {
    shader_use(&g_basic_shader);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    
    // Set up vertex attributes
    glEnableVertexAttribArray(g_basic_shader.position_attr);
    glVertexAttribPointer(g_basic_shader.position_attr, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(g_basic_shader.color_attr);
    glVertexAttribPointer(g_basic_shader.color_attr, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // Set MVP matrix
    glUniformMatrix4fv(g_basic_shader.mvp_uniform, 1, GL_FALSE, mvp->m);
    
    // Draw
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_SHORT, 0);
    
    glDisableVertexAttribArray(g_basic_shader.position_attr);
    glDisableVertexAttribArray(g_basic_shader.color_attr);
}

void draw_field(void) {
    // Set up 2.5D camera view
    Mat4 projection, view, model, mvp;
    
    float aspect = (float)g_game_state.screen_width / g_game_state.screen_height;
    mat4_perspective(&projection, 45.0f * M_PI / 180.0f, aspect, 0.1f, 100.0f);
    
    Vec3 eye = {0.0f, -15.0f, 10.0f}; // Camera position for 2.5D view
    Vec3 center = {0.0f, 0.0f, 0.0f};
    Vec3 up = {0.0f, 0.0f, 1.0f};
    mat4_lookat(&view, &eye, &center, &up);
    
    // Draw field background
    mat4_identity(&model);
    model.m[0] = g_game_state.field_width;
    model.m[5] = g_game_state.field_height;
    
    mat4_multiply(&mvp, &projection, &view);
    mat4_multiply(&mvp, &mvp, &model);
    
    mesh_render(&g_quad_mesh, &mvp);
}

void draw_players(void) {
    Mat4 projection, view, model, mvp;
    
    float aspect = (float)g_game_state.screen_width / g_game_state.screen_height;
    mat4_perspective(&projection, 45.0f * M_PI / 180.0f, aspect, 0.1f, 100.0f);
    
    Vec3 eye = {0.0f, -15.0f, 10.0f};
    Vec3 center = {0.0f, 0.0f, 0.0f};
    Vec3 up = {0.0f, 0.0f, 1.0f};
    mat4_lookat(&view, &eye, &center, &up);
    
    for (int i = 0; i < 6; i++) {
        Player* player = &g_game_state.players[i];
        
        mat4_identity(&model);
        model.m[0] = player->radius * 2.0f;
        model.m[5] = player->radius * 2.0f;
        model.m[12] = player->position.x;
        model.m[13] = player->position.y;
        model.m[14] = player->position.z + 0.1f; // Slightly above ground
        
        mat4_multiply(&mvp, &projection, &view);
        mat4_multiply(&mvp, &mvp, &model);
        
        mesh_render(&g_circle_mesh, &mvp);
    }
}

void draw_ball(void) {
    Mat4 projection, view, model, mvp;
    
    float aspect = (float)g_game_state.screen_width / g_game_state.screen_height;
    mat4_perspective(&projection, 45.0f * M_PI / 180.0f, aspect, 0.1f, 100.0f);
    
    Vec3 eye = {0.0f, -15.0f, 10.0f};
    Vec3 center = {0.0f, 0.0f, 0.0f};
    Vec3 up = {0.0f, 0.0f, 1.0f};
    mat4_lookat(&view, &eye, &center, &up);
    
    mat4_identity(&model);
    model.m[0] = g_game_state.ball.radius * 2.0f;
    model.m[5] = g_game_state.ball.radius * 2.0f;
    model.m[12] = g_game_state.ball.position.x;
    model.m[13] = g_game_state.ball.position.y;
    model.m[14] = g_game_state.ball.position.z + 0.05f;
    
    mat4_multiply(&mvp, &projection, &view);
    mat4_multiply(&mvp, &mvp, &model);
    
    mesh_render(&g_circle_mesh, &mvp);
}

void draw_ui(void) {
    // UI rendering would go here (score, etc.)
    // For now, just basic rendering
}