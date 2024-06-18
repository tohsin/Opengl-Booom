#include "vertexBufferLayout.h"

template<>
void VertexBufferLayout::push<float>( unsigned int  count){
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * LayoutElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::push<unsigned int>( unsigned int  count){
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * LayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>( unsigned int  count){
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * LayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
