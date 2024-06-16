#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "assert_utils.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray{
private:
    unsigned int m_RenderID;
    
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;

    void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
};
#endif