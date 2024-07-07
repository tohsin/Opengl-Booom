#include "elementBuffer.h"

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCALL(glGenBuffers(1, &m_RenderID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
ElementBuffer::ElementBuffer(const std::vector<unsigned int> data)
    : m_Count(data.size())
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCALL(glGenBuffers(1, &m_RenderID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID)); 
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW));
}



ElementBuffer::~ElementBuffer(){
    GLCALL(glDeleteBuffers(1, &m_RenderID ))
}

void ElementBuffer:: Bind() const{
    GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
}
void ElementBuffer::UnBind() const {
    GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
