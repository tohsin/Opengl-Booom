#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader_s.h>
#include "assert_utils.h"
#include "vertexBuffer.h"

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


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT , "Learning Open GL ", NULL, NULL);
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

    Shader custom_shader("shaders/shader.vs", "shaders/shader.fs");


    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
    };


    //glgenbuffer allows us to generate one
    unsigned int VAO;
    GLCALL(glGenVertexArrays(1, &VAO));
    GLCALL(glBindVertexArray(VAO));

    VertexBuffer vertexBuffer(vertices, 3 * 6 * sizeof(float));


    // position attribute
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*) 0));
    GLCALL(glEnableVertexAttribArray(0));
    // color attribute
    GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float))));
    GLCALL(glEnableVertexAttribArray(1));
    

    // glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // glBindVertexArray(0); 


    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // render
        // ------
        GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        custom_shader.use();
        
        GLCALL(glBindVertexArray(VAO));

        GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));


        GLCALL(glfwSwapBuffers(window));
        GLCALL(glfwPollEvents()); // checks for events and update the window state and calls right functions
    }
  
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}


void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}