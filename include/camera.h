#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera{
private:
    glm::vec3 m_CameraPos, m_CameraFront, m_CameraUp;
    float m_Yaw, m_Pitch, m_Speed;
public:
    Camera(float speed)
        :   m_CameraPos(glm::vec3(0.0f, 0.0f, 0.0f)), 
            m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), 
            m_CameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
            m_Yaw(0),
            m_Pitch(0),
            m_Speed(speed){}

    glm::mat4 getViewMatrix() const;

    void setCameraConfig(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float pitch, float yaw );

    inline void setCameraPosition(glm::vec3 pos) {m_CameraPos = pos;};
    inline void setCameraFront(glm::vec3 front) {m_CameraFront = front;};
    inline void setCameraUp(glm::vec3 up) {m_CameraUp = up;};
    inline void setSpeed(float speed) {m_Speed = speed;};
    inline void setPitch(float pitch) {m_Pitch = pitch;};
    inline void setYaw(float yaw) {m_Yaw = yaw;};

   inline glm::vec3 getCameraPosition()const {return m_CameraPos ;};
   inline glm::vec3 getCameraFront() const {return m_CameraFront;};
   inline glm::vec3 getCameraUp() const  {return m_CameraUp;};
   inline float getSpeed() const {return m_Speed;}; 
   inline float getPitch() const {return m_Pitch;}; 
   inline float getYaw() const {return m_Yaw;}; 

   inline void offsetYaw(float offset){ m_Yaw += offset;};
   inline void offsetPitch(float offset){ m_Pitch += offset;};

   glm::vec3 computeDeltaPosZ() const;
   glm::vec3 computeDeltaPosX() const;

   void moveForward();
   void moveBackward();
   void moveLeft();
   void moveRight();

};
#endif
