#include "gWindow.h"


GLFWWindow::GLFWWindow(int width, int height, const char* title, bool use_Mouse )
    :m_DeltaTime(0.0f), m_LastFrame(0.0f)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    if(use_Mouse)
        glfwSetCursorPosCallback(window, mouse_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }
    mouse = Mouse(width/2.0f, height/2.0f);
}
Camera* GLFWWindow::camera = nullptr;
Mouse GLFWWindow::mouse(0.0f, 0.0f);

GLFWWindow::~GLFWWindow() {
    glfwTerminate();
}
bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void GLFWWindow::swapBuffers() const {
    glfwSwapBuffers(window);
}

void GLFWWindow::pollEvents() const {
    glfwPollEvents();
}

// void GLFWWindow::processInput() const {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//         glfwSetWindowShouldClose(window, true);
//     }
// }

void GLFWWindow::updateTime(){
    float currentFrame = glfwGetTime();
    m_DeltaTime = currentFrame - m_LastFrame;
    m_LastFrame = currentFrame;
}

void GLFWWindow::processInput(){
    //time and speed updates
    updateTime();
    if(camera){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            camera->moveForward(m_DeltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            camera->moveBackward(m_DeltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            camera->moveLeft(m_DeltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            camera->moveRight(m_DeltaTime);
        }
    }
    

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }


}

// call backs
void GLFWWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GLFWWindow::mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (mouse.first)
    {
        mouse.X = xpos;
        mouse.Y = ypos;
        mouse.first = false;
    }

    float xoffset = xpos - mouse.X;
    float yoffset = mouse.Y - ypos; // reversed since y-coordinates go from bottom to top
    mouse.X = xpos;
    mouse.Y = ypos;

    if(camera){
        camera->processMouseMotion(xoffset, yoffset);
    }

}