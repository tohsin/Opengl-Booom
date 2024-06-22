#ifndef RENDERER_H
#define RENDERER_H

#include "assert_utils.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "shader.h"

class Renderer{
public:
    void Draw(VertexArray& vertexArray, ElementBuffer& elementBuffer, Shader& shader)  const ;
    void Draw(VertexArray& vertexArray, Shader& shader, int count)  const ;
    void Draw(VertexArray& vertexArray, Shader& shader, int count, glm::mat4 projection, glm::mat4 view, glm::mat4 model) const;
    void Draw(VertexArray& vertexArray, Shader& shader, int count, glm::mat4 projection, glm::mat4 model) const;
    void Clear(const glm::vec3& bgColor) const;
    void setBGColor() const;
};
#endif
