#pragma once
#include <iostream>
#include <vector>
#include <assert_utils.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "vertexBufferLayout.h"
#include "shader.h"
#include "texture.h"
#include "renderer.h"


class Mesh{

public:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader& shader, Renderer& renderer);
private:
    VertexArray m_VertexArray;
    VertexBuffer m_VertexBuffer;
    ElementBuffer m_ElementBuffer;
    void setupMesh();
    
};