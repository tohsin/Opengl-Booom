#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using vec2 = glm::vec2;
using vec3 = glm::vec3;

using mat = glm::mat4;

class Particle{
private:
    vec2 m_Position;
    vec2 m_Prev_position;
    vec2 m_Acceleration;
    const float m_Size = 50.0;
public:
    mat model;
    float gravity = 50.0f;
    
    Particle(vec2 position);
    //~Particle();

    glm::mat4 getModelMatrix();
    void applyGravity();
    void Update(float dt); // calls verlet integration
    void accelerateParticle(vec2 acc);
    void updatePosition(float dt);

    inline vec2 getGravityVector() const { return vec2(0.0, -gravity * 1000); }
    inline void resetGravity(){ m_Acceleration = vec2(0.0f, 0.0f); };

    inline vec2 getPosition() const {return m_Position;};
    inline void setPosition(vec2 pos) { m_Position = pos;}
    inline float getSize() const {return m_Size;}
};