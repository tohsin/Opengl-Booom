#include "particle.h"
#include <iostream>

Particle::Particle(glm::vec2 position)
    :m_Position(position){
}

glm::mat4 Particle::getModelMatrix(){
    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::translate(model, glm::vec3(m_Position, 0.0f));
    model = glm::scale(model, glm::vec3(m_Size, m_Size, 1.0f));
    return model;
}


void Particle::applyGravity(){
    accelerateParticle(getGravityVector());
}

void Particle::updatePosition(float dt){
    const vec2 velocity = m_Position - m_Prev_position;
    m_Prev_position = m_Position;
    m_Position = m_Position + (velocity * dt) + (m_Acceleration * dt * dt);
    resetGravity();

    // if it hits floo
    float floorY = 0.0f;
    if (m_Position.y <= floorY + m_Size * 0.5f) {
        m_Position.y = floorY + m_Size * 0.5f;
        m_Prev_position = m_Position;
    }
}
void Particle::Update(float dt){
    applyGravity();
    updatePosition(dt);

}
void Particle::accelerateParticle(vec2 acc){
    m_Acceleration += acc;
}

