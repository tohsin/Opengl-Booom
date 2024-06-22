#include "simulator.h"

Simulator::Simulator(Renderer& r, Camera& c, Shader& s,  VertexArray& arr, int count, vec2 emitPos = vec2(0.0f, 0.0f))
        : emitPosition(emitPos), time_step(0.0f), has_emited(false), shouldEmitParticle(false), lastFrameTime(0.0f),
          vertexCount(count), renderer(r), camera(c), shader(s), vertexArray(arr) {
    }
void Simulator::Step(){
    float dt = getDeltaTime();
    this->time_step += dt;
    Update(dt);
    Draw();
}

float Simulator::getDeltaTime(){
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - this->lastFrameTime;
    this->lastFrameTime = currentTime;
    return deltaTime;
}
void Simulator::Update(float dt){
    if (this->shouldEmitParticle && this->time_step >= 5 && !this->has_emited){
        emitParticle();
        this->has_emited = true;
    }
        
    resolveCollisons();
    if( this->time_step > 1){
        for(auto & particle : this->particles)
            particle.Update(dt);
    }

}


void Simulator::Draw() {
    for(auto & particle : this->particles){
        this->renderer.Draw(this->vertexArray, 
                    this->shader, this->vertexCount, 
                    this->camera.getProjectionMatrix(), 
                    particle.getModelMatrix());
    }
   
}
void Simulator::resolveCollisons(){
    // we have more than one particle
    if(this->particles.size() > 1){
        for( int i = 0; i< this->particles.size(); i++){
            Particle& particle_1 = this->particles[i];
            for(int j = i + 1; j < this->particles.size(); j++){
                Particle& particle_2 = this->particles[j];
                resolveCollision(particle_1, particle_2);

            }
        }
    }
}

void Simulator::resolveCollision(Particle& particle_1, Particle& particle_2) {
    vec2 col_axis = particle_1.getPosition() - particle_2.getPosition();
    float distance_magnitude = glm::length(col_axis); 
    const float max_collsion_distance = particle_1.getSize();
    
    if (distance_magnitude <= max_collsion_distance){
        const vec2 normal = col_axis / distance_magnitude;
        const float dx =  max_collsion_distance - distance_magnitude;
        particle_1.setPosition( particle_1.getPosition() + dx * normal );
        particle_2.setPosition( particle_2.getPosition() - dx * normal );
    }
}