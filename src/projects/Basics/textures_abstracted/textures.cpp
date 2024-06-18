#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader_s.h>
#include <stb_image/stb_image.h>
#include "assert_utils.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "vertexArray.h"
#include "renderer.h"
#include "texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(void)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT , "Learning Textures ", NULL, NULL);
    if (window == NULL){
        std::cout << "Debug: Failed to create GLFW window"<< std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Debug: Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Shader custom_shader("shaders/texture.vs", "shaders/texture.fs");
    float vertices[] = {
        // positions        // colors         // texture coords
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

 
    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertices, 4 * 8 * sizeof(float));
  
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); //color
    layout.push<float>(2); // texture
    vertexArray.AddBuffer(vertexBuffer, layout);

    ElementBuffer elementBuffer(indices, 6);

    Texture containerTexture("/Users/emma/dev/Opengl-Booom/resources/textures/container.jpg", GL_RGB);
    Texture smileyFaceTexture("/Users/emma/dev/Opengl-Booom/resources/textures/awesomeface.png", GL_RGBA);

    custom_shader.Bind();
    custom_shader.setInt("smiley_face_texture", 1);

    Renderer renderer;

    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // render
        // ------
        GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        renderer.Clear();

        // bind Texture
       
        containerTexture.Bind(0);
        smileyFaceTexture.Bind(1);

        //finally draw to screen
        renderer.Draw(vertexArray, elementBuffer, custom_shader);

        glfwSwapBuffers(window);
        glfwPollEvents(); // checks for events and update the window state and calls right functions
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

