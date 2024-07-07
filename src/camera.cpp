#include "camera.h"

Camera::Camera(
    float width,
    float height,
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
    CameraType cameraType = ORTHO,
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
    
    :m_Pos(position), 
    m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
    m_Up(up),
    m_WorldUp(up),
    m_Yaw(YAW),
    m_Pitch(PITCH),
    m_Sensitivity(SENSITIVITY),
    m_MovementSpeed(SPEED){
        if (cameraType == ORTHO ){  
            m_Projection = glm::ortho(0.0f, width, 0.0f , height , -1.0f, 1.0f);
        }else{
            m_Projection = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 100.0f);
        }
    }
void Camera::setCameraConfig(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float pitch, float  yaw ){
   setPosition(pos);
   setCameraFront(front);
   setCameraUp(up);
   setPitch(pitch);
   setYaw(yaw);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

glm::vec3 Camera::computeDeltaPosZ(float m_DeltaTime) const {
    float velocity = m_MovementSpeed * m_DeltaTime;
    return velocity * m_Front;
}

glm::vec3 Camera::computeDeltaPosX(float m_DeltaTime) const {
    float velocity = m_MovementSpeed * m_DeltaTime;
    return  glm::normalize(glm::cross(m_Front, m_WorldUp)) * velocity;
}

void Camera::moveForward(float m_DeltaTime){
    m_Pos += computeDeltaPosZ( m_DeltaTime);
}

void Camera::moveBackward(float m_DeltaTime){
    m_Pos -= computeDeltaPosZ( m_DeltaTime) ;
}


void Camera::moveLeft(float m_DeltaTime){
    m_Pos -= computeDeltaPosX( m_DeltaTime);
}


void Camera::moveRight(float m_DeltaTime){
    m_Pos += computeDeltaPosX( m_DeltaTime);
}

void Camera::updateCameraOrientation(){
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);

    m_Up = glm::normalize(glm::cross(glm::normalize(glm::cross(m_Front, m_WorldUp)), m_Front));
}

void Camera::processMouseMotion(float xoffset , float yoffset ){
    xoffset *= m_Sensitivity;
    yoffset *= m_Sensitivity;

    offsetYaw(xoffset);
    offsetPitch(yoffset);

    if (m_Pitch > 89.0f)
        setPitch(89.0f);
    if (m_Pitch < -89.0f)
        setPitch(-89.0f);

    updateCameraOrientation();
}