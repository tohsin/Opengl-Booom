#include "renderer.h"

void Renderer::Draw(VertexArray& vertexArray, ElementBuffer& elementBuffer,Shader& shader) const {
        shader.Bind();
        vertexArray.Bind();
        GLCALL(glDrawElements(GL_TRIANGLES, elementBuffer.getCount(), GL_UNSIGNED_INT, 0));
}
void Renderer::Draw(VertexArray& vertexArray, Shader& shader, int count) const {
        shader.Bind();
        vertexArray.Bind();
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, count););
}
void Renderer::Draw(VertexArray& vertexArray, Shader& shader, int count, glm::mat4 projection, glm::mat4 view, glm::mat4 model) const {
        shader.Bind();
        shader.setUniformMat4("projection", projection);
        shader.setUniformMat4("view", view);
        shader.setUniformMat4("model", model);
        vertexArray.Bind();
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, count););
}
void Renderer::Clear() const {
            // ------
    GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); 
//     GLCALL( glClear(GL_COLOR_BUFFER_BIT));
}