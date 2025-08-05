#include "game_engine.h"
#include <jni.h>

JNIEXPORT void JNICALL
Java_com_toopan2d_game_MainActivity_nativeInit(JNIEnv *env, jobject thiz) {
    LOGI("Initializing native game");
    game_init();
}

JNIEXPORT void JNICALL
Java_com_toopan2d_game_MainActivity_nativeResize(JNIEnv *env, jobject thiz, 
                                                  jint width, jint height) {
    LOGI("Screen resize: %dx%d", width, height);
    game_resize(width, height);
}

JNIEXPORT void JNICALL
Java_com_toopan2d_game_MainActivity_nativeRender(JNIEnv *env, jobject thiz) {
    static float last_time = 0.0f;
    static int frame_count = 0;
    
    // Simple frame timing (in real app, use proper timing)
    float current_time = (float)frame_count * 0.016f; // ~60 FPS
    float delta_time = current_time - last_time;
    last_time = current_time;
    frame_count++;
    
    game_update(delta_time);
    game_render();
}

JNIEXPORT void JNICALL
Java_com_toopan2d_game_MainActivity_nativeTouch(JNIEnv *env, jobject thiz, 
                                                 jfloat x, jfloat y, jint action) {
    game_touch(x, y, action);
}