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
int screen_width = 800;
int screen_height = 600;
const glm::vec3 bgColor(0.2f, 0.3f, 0.3f);

struct Lightpropeties{
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
};

int main(void)
{
    Camera camera((float)screen_width,(float)screen_height, glm::vec3(0.0f, 0.0f, 10.0f), CameraType::PROJ,  glm::vec3(0.0f, 1.0f, 0.0f));
    GLFWWindow::camera = &camera; 
    GLFWWindow window(screen_width, screen_height, "Learning Translation", true);

    GLCALL(glEnable(GL_DEPTH_TEST);)
    Shader cubeShader("shaders/vertex.vs", "shaders/fragment.fs");
    Shader lightingCubeShader("shaders/lighting_vetrex.vs", "shaders/lighting_fragment.fs");

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    VertexArray cubeVertexArray;
    VertexBuffer vertexBuffer(vertices, sizeof(vertices));

    cubeVertexArray.Bind();
    vertexBuffer.Bind();
    
  
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); // normal
    layout.push<float>(2); // texcoord
    cubeVertexArray.AddBuffer(vertexBuffer, layout);


    VertexArray lightCubeVertexArray;

    lightCubeVertexArray.Bind();
    vertexBuffer.Bind();

    VertexBufferLayout layout2;
    layout2.push<float>(3); // position
    lightCubeVertexArray.AddBuffer(vertexBuffer, layout2, 8 * sizeof(float));

    Texture lightMapTexture("/Users/emma/dev/Opengl-Booom/resources/textures/container2.png", TextureType::None);
    Texture specularMapTexture("/Users/emma/dev/Opengl-Booom/resources/textures/container2_specular.png", TextureType::None);


    cubeShader.Bind();
    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);

    Renderer renderer;
    // light source
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


    Lightpropeties light_properties;
    while(!window.shouldClose()){

        // input
        window.processInput();

        // render
        renderer.Clear(bgColor);

        // // render cube bind shaders
        cubeShader.Bind();
        cubeShader.setUniformVec3f("light.position", camera.getPosition());
        cubeShader.setUniformVec3f("light.direction", camera.getFront());
        cubeShader.setFloat("light.cutoff", glm::cos(glm::radians(12.5f))); 
        cubeShader.setUniformVec3f("viewPos", camera.getPosition());
        // set light colors
        cubeShader.setUniformVec3f("light.ambient",  light_properties.ambient);
        cubeShader.setUniformVec3f("light.diffuse", light_properties.diffuse);
        cubeShader.setUniformVec3f("light.specular", light_properties.specular);

        cubeShader.setFloat("light.constant", light_properties.constant);
        cubeShader.setFloat("light.linear", light_properties.linear);
        cubeShader.setFloat("light.quadratic", light_properties.quadratic);

        // material setup
        cubeShader.setFloat("material.shininess", 32.0f);
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);

        lightMapTexture.Bind(0);
        specularMapTexture.Bind(1);
        for(unsigned int i = 0; i < 10; i++)
        {
            model  = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3(1.0f, 0.3f, 0.5f));
            renderer.Draw(cubeVertexArray, cubeShader, 36, camera, model);
        }
        // camera is light source

        //finally draw to screen
        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}
