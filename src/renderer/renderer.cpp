#include "renderer.h"

void Renderer::Draw(VertexArray& vertexArray, ElementBuffer& elementBuffer,Shader& shader) const {
        shader.Bind();
        vertexArray.Bind();
        GLCALL(glDrawElements(GL_TRIANGLES, elementBuffer.getCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::Clear() const {
    GLCALL( glClear(GL_COLOR_BUFFER_BIT));
}