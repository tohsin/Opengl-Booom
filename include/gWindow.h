#ifndef WINDOW_H
#define WINDOW_H
// #pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "camera.h"

struct Mouse{
    bool first = true;
    float X;
    float Y;

    Mouse(float x, float y)
        :X(x), Y(y){}
};
class GLFWWindow {
private:
    GLFWwindow* window;
    int m_Width, m_Height;
    float m_DeltaTime;
    float m_LastFrame;
    
public:
    static Camera* camera;
    static Mouse mouse;
    GLFWWindow(int width, int height, const char* title, bool use_Mouse);
    ~GLFWWindow();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    // void processInput() const;
    void updateTime();
    void processInput();

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

};
#endif