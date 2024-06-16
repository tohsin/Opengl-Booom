#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader_s.h>
#include <stb_image/stb_image.h>
#include "assert_utils.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "vertexArray.h"

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

    // glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // glBindVertexArray(0); 

    // load and create a texture 
    // -------------------------
    unsigned int texture;
    GLCALL(glGenTextures(1, &texture));
    GLCALL(glBindTexture(GL_TEXTURE_2D, texture)); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // set texture filtering parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/emma/dev/Opengl-Booom/resources/textures/container.jpg", &width, &height, &nrChannels, 0);

    if(data){
        // generate texture and minmaps from data
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    }else{
        std::cout << "DEBUG: Failed to load texture" << std::endl;
    }
    // free the image memory
    stbi_image_free(data);



    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // render
        // ------
        GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCALL( glClear(GL_COLOR_BUFFER_BIT));

        // bind Texture
        GLCALL(glBindTexture(GL_TEXTURE_2D, texture));
      
        custom_shader.use();
        vertexArray.Bind();
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        glfwSwapBuffers(window);
        glfwPollEvents(); // checks for events and update the window state and calls right functions
    }

    // glDeleteBuffers(1, &EBO);
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

