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
#include "model.h"

int screen_width = 800;
int screen_height = 600;
const glm::vec3 bgColor(0.2f, 0.3f, 0.3f);


int main(void)
{
    Camera camera(  (float)screen_width, (float)screen_height, 
                    glm::vec3(0.0f, 0.0f, 10.0f), CameraType::PROJ, 
                    glm::vec3(0.0f, 1.0f, 0.0f));
    GLFWWindow::camera = &camera; 
    GLFWWindow window(screen_width, screen_height, "Model Loading", true);

    Model bagModel("/Users/emma/dev/Opengl-Booom/resources/objects/backpack/backpack.obj");
    GLCALL(glEnable(GL_DEPTH_TEST);)
    Shader shader("shaders/vertex.vs", "shaders/fragment.fs");
    Renderer renderer;

    while(!window.shouldClose()){

        // input
        window.processInput();

        //clear
        renderer.Clear(bgColor);

        //setup shader
        shader.Bind();
        shader.setUniformMat4("projection", camera.getProjectionMatrix());
        shader.setUniformMat4("view", camera.getViewMatrix());
        glm::mat4 model = glm::mat4(1.0f);
        // translate it down so it's at the center of the scene
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        // it's a bit too big for our scene, so scale it down
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setUniformMat4("model", model);

        
        bagModel.Draw(shader, renderer);

        //finally draw to screen
        window.swapBuffers();
        window.pollEvents();
    }

    glfwTerminate();
    return 0;
}
