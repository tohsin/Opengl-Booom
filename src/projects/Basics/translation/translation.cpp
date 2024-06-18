#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <shader.h>
#include <stb_image/stb_image.h>
#include "assert_utils.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "vertexArray.h"
#include "renderer.h"
#include "texture.h"
#include "gWindow.h"

int main(void)
{
    GLFWWindow window(800, 600, "Learning Translation");

    Shader custom_shader("shaders/texture.vs", "shaders/texture.fs");

    float vertices[] = {
        // positions        // texture
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left
    };
    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertices, 4 * 5 * sizeof(float));
  
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texture
    
    vertexArray.AddBuffer(vertexBuffer, layout);

    ElementBuffer elementBuffer(indices, 6);

    Texture containerTexture("/Users/emma/dev/Opengl-Booom/resources/textures/container.jpg", GL_RGB);
    Texture smileyFaceTexture("/Users/emma/dev/Opengl-Booom/resources/textures/awesomeface.png", GL_RGBA);

    custom_shader.Bind();
    custom_shader.setInt("smiley_face_texture", 1);

    Renderer renderer;

    while(!window.shouldClose()){
        // input
        window.processInput();

        // render
        renderer.Clear();

        // bind Texture
        containerTexture.Bind(0);
        smileyFaceTexture.Bind(1);


        glm::mat4 trans = glm::mat4(1.0f); // to store my translation
        // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); // 90 degrees at z axis
        // trans = glm::scale(trans, glm::vec3(0.5, 0.5,0.5));

        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(),
                            glm::vec3(0.0f, 0.0f, 1.0f));

        
        custom_shader.setUniformMat4("transform", trans);

        //finally draw to screen
        renderer.Draw(vertexArray, elementBuffer, custom_shader);

        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}
