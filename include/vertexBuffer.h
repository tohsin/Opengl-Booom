#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
// #pragma once
#include <assert_utils.h>

class VertexBuffer{
private:
    unsigned int m_RenderID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
#endif