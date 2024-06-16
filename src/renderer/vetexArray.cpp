#include "vertexArray.h"

VertexArray::VertexArray(){
    GLCALL(glGenVertexArrays(1, &m_RenderID));

}


VertexArray::~VertexArray(){
    GLCALL(glDeleteVertexArrays(1, &m_RenderID ))
}

void VertexArray:: Bind() const {
    GLCALL( glBindVertexArray(m_RenderID));
}
void VertexArray::UnBind() const {
    GLCALL( glBindVertexArray(0));
}


void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout){
    Bind();
    vertexBuffer.Bind();
    unsigned int offset = 0;
    const auto& elements = layout.getElements();
    for( unsigned int i =0; i<elements.size(); i++ ){
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset));
        offset += element.count * LayoutElement::GetSizeOfType(element.type);
    }

}