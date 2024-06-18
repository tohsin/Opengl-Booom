#include "gWindow.h"


GLFWWindow::GLFWWindow(int width, int height, const char* title)
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
        camera->setSpeed(2.5f * m_DeltaTime);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            camera->moveForward();
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            camera->moveBackward();
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            camera->moveLeft();
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            camera->moveRight();
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

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    if(camera){
        camera->offsetYaw(xoffset);
        camera->offsetPitch(yoffset);

        if (camera->getPitch() > 89.0f)
            camera->setPitch(89.0f);
        if (camera->getPitch() < -89.0f)
            camera->setPitch(-89.0f);

        glm::vec3 front;
        front.x = cos(glm::radians(camera->getYaw())) * cos(glm::radians(camera->getPitch()));
        front.y = sin(glm::radians(camera->getPitch()));
        front.z = sin(glm::radians(camera->getYaw())) * cos(glm::radians(camera->getPitch()));
        camera->setCameraFront(glm::normalize(front));
    }

}