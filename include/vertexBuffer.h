#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
// #pragma once
#include <assert_utils.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertex.h"
#include <iostream>
#include <vector>
class VertexBuffer{
private:
    unsigned int m_RenderID;
    bool isDynamic;
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(std::vector<Vertex> vertices);
    VertexBuffer(unsigned int size); // dynamic use
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;

    inline bool getIsDynamic()const{ return isDynamic;}
};
#endif