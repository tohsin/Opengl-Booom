#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <stb_image/stb_image.h>
#include "assert_utils.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "vertexArray.h"
#include "renderer.h"
#include "texture.h"
#include "gWindow.h"
#include "shader.h"
#include "camera.h"
#include "particle.h"
#include "simulator.h"

int screen_width = 1500; 
int screen_height = 1000;
int main(void)
{
    Camera camera((float)screen_width,(float)screen_height, glm::vec3(0.0f, 0.0f, 10.0f), CameraType::ORTHO,  glm::vec3(0.0f, 1.0f, 0.0f));
    GLFWWindow::camera = &camera;
    const glm::vec3 bgColor(0.2f, 0.3f, 0.3f);
    
    GLFWWindow window(screen_width, screen_height, "Learning Translation", false);

    Shader shader("shaders/vertex.vs", "shaders/fragment.fs");

    float vertices[] = {
        // positions          
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
    };
    
    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertices, sizeof(vertices));

    vertexArray.Bind();
    vertexBuffer.Bind();
    
  
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    vertexArray.AddBuffer(vertexBuffer, layout);


    Renderer renderer;
    Simulator simulator(renderer, camera, shader, vertexArray, 6, vec2(screen_width/2, screen_height - 500));
    simulator.enableEmmiter();
    simulator.emitParticle();
    float lastFrameTime = glfwGetTime();
    float elaspsed_time = 0.0f;

    while(!window.shouldClose()){
        
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // input
        window.processInput();

        // render
        renderer.Clear(bgColor); 
        shader.Bind();
        shader.setUniformVec3f("bg_color", bgColor);
        
        // render simulator
        simulator.Step();
        //finally draw to screen
        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}
