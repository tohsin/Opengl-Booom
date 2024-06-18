#include "camera.h"


void Camera::setCameraConfig(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float pitch, float  yaw ){
   setCameraPosition(pos);
   setCameraFront(front);
   setCameraUp(up);
   setPitch(pitch);
   setYaw(yaw);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

glm::vec3 Camera::computeDeltaPosZ() const {
    return m_Speed * m_CameraFront;
}

glm::vec3 Camera::computeDeltaPosX() const {
    return  glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_Speed;
}

void Camera::moveForward(){
    m_CameraPos += computeDeltaPosZ() ;
}

void Camera::moveBackward(){
    m_CameraPos -= computeDeltaPosZ() ;
}


void Camera::moveLeft(){
    m_CameraPos -= computeDeltaPosX();
}


void Camera::moveRight(){
    m_CameraPos += computeDeltaPosX();
}