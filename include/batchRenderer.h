#pragma once

#include "vertexArray.h"
#include "vertexBuffer.h"
#include <vector>

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using mat = glm::mat4;


class BatchRenderer{
private:
    VertexArray vetrexarray;
    VertexBuffer VertexBuffer;
    std::vector<Vetrex> vertices;
public:
    BatchRenderer();

};