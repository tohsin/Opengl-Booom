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

        // model matrix transforms it to be in world space
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate to appear to be on the floor

        // view/camera model we want to move back abit which is the same as moving the scene forward
        // so we move nagative z axis
        // using right handded system
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

        // finally clip coordinates and porjection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
            100.0f);

        custom_shader.setUniformMat4("model", model);
        custom_shader.setUniformMat4("view", view);
        custom_shader.setUniformMat4("projection", projection);


        //finally draw to screen
        renderer.Draw(vertexArray, elementBuffer, custom_shader);

        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}
