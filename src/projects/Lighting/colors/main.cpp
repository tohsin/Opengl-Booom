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

int main(void)
{
    Camera camera(0.05f);
    GLFWWindow::camera = &camera; 
    GLFWWindow window(800, 600, "Learning Translation");

    GLCALL(glEnable(GL_DEPTH_TEST);)
    Shader cubeShader("shaders/vertex.vs", "shaders/fragment.fs");
    Shader lightingCubeShader("shaders/lighting_vetrex.vs", "shaders/lighting_fragment.fs");
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };
    VertexArray cubeVertexArray;
    VertexBuffer vertexBuffer(vertices, sizeof(vertices));

    cubeVertexArray.Bind();
    vertexBuffer.Bind();
    
  
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    cubeVertexArray.AddBuffer(vertexBuffer, layout);


    VertexArray lightCubeVertexArray;

    lightCubeVertexArray.Bind();
    vertexBuffer.Bind();

    VertexBufferLayout layout2;
    layout2.push<float>(3); // position
    lightCubeVertexArray.AddBuffer(vertexBuffer, layout2);


    Renderer renderer;
    
    camera.setCameraConfig(glm::vec3(0.0f, 0.0f, 3.0f),
                           glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f),
                           0.0f,
                           -90.0f);
    // light source
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);



    while(!window.shouldClose()){

        // input
        window.processInput();

        // render
        renderer.Clear();

        // // render cube bind shaders
        cubeShader.Bind();
        cubeShader.setUniformVec3f("lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader.setUniformVec3f("objectColor", 1.0f, 0.5f, 0.31f);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
            100.0f);
        glm::mat4 view = camera.getViewMatrix();
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        
        renderer.Draw(cubeVertexArray, cubeShader, 36, projection, view, model);

        // render light cube
        lightingCubeShader.Bind();
        // lightCubeVertexArray.Bind();

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube

        renderer.Draw(lightCubeVertexArray, lightingCubeShader, 36, projection, view, model);

        //finally draw to screen
        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}
