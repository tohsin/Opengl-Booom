#ifndef RENDERER_H
#define RENDERER_H

#include "assert_utils.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "shader_s.h"

class Renderer{
public:
    void Draw(VertexArray& vetrexAray, ElementBuffer& elementBuffer, Shader& shader)  const ;
    void Clear() const;
    void setBGColor() const;
};
#endif
