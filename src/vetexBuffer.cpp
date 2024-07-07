#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size):
    isDynamic(false) 
{
    GLCALL(glGenBuffers(1, &m_RenderID));
    GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer(std::vector<Vertex> vertices)
    :isDynamic(false) 
{
    GLCALL(glGenBuffers(1, &m_RenderID));
    GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(unsigned int size)
    :isDynamic(true) 
{
    GLCALL(glGenBuffers(1, &m_RenderID));
    GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));
}


VertexBuffer::~VertexBuffer(){
    GLCALL(glDeleteBuffers(1, &m_RenderID ))
}

void VertexBuffer:: Bind() const {
    GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}
void VertexBuffer::UnBind() const {
    GLCALL( glBindBuffer(GL_ARRAY_BUFFER, 0));
}
