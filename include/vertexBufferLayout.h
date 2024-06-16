#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H
// #pragma once
#include <assert_utils.h>
#include <vector>
#include <glad/glad.h>


struct LayoutElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    LayoutElement(unsigned int type, unsigned int count, unsigned char normalized)
        : type(type), count(count), normalized(normalized) {}

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
            default: ASSERT(false); return 0;
        }
    }
};
class VertexBufferLayout{
private:
    std::vector<LayoutElement>  m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0){};

    template<typename T>
    void push( unsigned int  count);

    inline const std::vector<LayoutElement> getElements() const {return m_Elements;};
    inline unsigned int getStride() const { return m_Stride;};

};
// Forward declarations for template specializations
template<>
void VertexBufferLayout::push<float>(unsigned int count);
template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count);
template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count);

#endif