#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
enum CameraType{
    ORTHO,
    PROJ
};
const float SPEED       =  2.5f;
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SENSITIVITY =  0.1f;
class Camera{
private:
    glm::vec3 m_Pos, m_Front, m_Up, m_WorldUp, m_Right;
    float m_Yaw, m_Pitch, m_Sensitivity, m_MovementSpeed;
    glm::mat4 m_Projection;
public:
    Camera( float width,
            float height, 
            glm::vec3 position, 
            CameraType cameraType, 
            glm::vec3 up);
    
    void setCameraConfig(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float pitch, float yaw );

    inline void setPosition(glm::vec3 pos) {m_Pos = pos;};
    inline void setCameraFront(glm::vec3 front) {m_Front = front;};
    inline void setCameraUp(glm::vec3 up) {m_Up = up;};
    inline void setMovementSpeed(float speed) {m_MovementSpeed = speed;};
    inline void setPitch(float pitch) {m_Pitch = pitch;};
    inline void setYaw(float yaw) {m_Yaw = yaw;};

   inline glm::vec3 getPosition()const {return m_Pos ;};
   inline glm::vec3 getFront() const {return m_Front;};
   inline glm::vec3 getCameraUp() const  {return m_Up;};

   inline float getMovementSpeed() const {return m_MovementSpeed;}; 
   inline float getPitch() const {return m_Pitch;}; 
   inline float getYaw() const {return m_Yaw;}; 

   inline glm::mat4 getProjectionMatrix() const{return m_Projection;};
   glm::mat4 getViewMatrix() const;

   inline void offsetYaw(float xoffset){ m_Yaw += xoffset;};
   inline void offsetPitch(float yoffset){ m_Pitch += yoffset;};
   inline void setOffset(float xoffset, float yoffset){offsetYaw(xoffset); offsetPitch(yoffset);}

   glm::vec3 computeDeltaPosZ(float m_DeltaTime) const;
   glm::vec3 computeDeltaPosX(float m_DeltaTime) const;

   void moveForward(float m_DeltaTime);
   void moveBackward(float m_DeltaTime);
   void moveLeft(float m_DeltaTime);
   void moveRight(float m_DeltaTime);

   void updateCameraOrientation();
   void processMouseMotion(float xoffset , float yoffset);

   

};
#endif
