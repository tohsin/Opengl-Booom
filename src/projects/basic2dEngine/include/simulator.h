#pragma once
#include <vector>
#include "particle.h"
#include "renderer.h"
#include <GLFW/glfw3.h>
#include "camera.h"

class Simulator{

private:
    std::vector<Particle> particles;
    vec2 emitPosition;
    float time_step;
    bool has_emited;
    bool shouldEmitParticle;
    float lastFrameTime;
    int vertexCount;
    Renderer& renderer;  // Reference to renderer
    Camera& camera;      // Reference to camera
    Shader& shader;      // Reference to shader
    VertexArray& vertexArray;

public:
    // Simulator(vec2 emitPos =  vec2(0.0f, 0.0f));
    Simulator(Renderer& r, Camera& c, Shader& s, VertexArray& arr, int vertexCount, vec2 emitPos);

    inline void addParticle(const Particle& particle) { this->particles.push_back(particle); }
    inline void emitParticle( ){ this->particles.push_back(Particle(this->emitPosition));}; // emits 1 particle  from a given position
    inline void  setEmitPosition(vec2 position ) { this->emitPosition = position;}
    inline void enableEmmiter() {this->shouldEmitParticle = true; }
    void Update(float dt);
    void Draw();
    void resolveCollisons();
    void resolveCollision(Particle& particle_1, Particle& particle_2);
    float getDeltaTime();
    void Step();
};