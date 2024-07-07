#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_Vertices(vertices),  m_Indices(indices), m_Textures(textures), m_VertexBuffer(m_Vertices), m_ElementBuffer(m_Indices)
{
    m_VertexArray = VertexArray();
    setupMesh();
}


void Mesh::setupMesh(){
    VertexBufferLayout layout;
    layout.push<float>(3);  // position
    layout.push<float>(3);  // normals
    layout.push<float>(2);// texture coordinates
    m_VertexArray.AddBuffer(m_VertexBuffer, layout);
    m_VertexArray.UnBind();
}

void Mesh::Draw(Shader& shader, Renderer& renderer){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for(unsigned int i = 0; i < m_Textures.size(); i++){
        m_Textures[i].Bind(i);
        std::string number;
        TextureType texture_type =  m_Textures[i].getType();
        std::string name = Texture::getTypeLiteral(texture_type);
        
        if ( texture_type == TextureType::Diffuse){
            number = std::to_string(diffuseNr++);
        }else if ( texture_type == TextureType::Specular){
            number = std::to_string(specularNr++);
        }

        shader.setFloat(("material." + name + number).c_str(), i );
    }

    m_VertexArray.Bind();
    renderer.Draw(m_VertexArray, m_ElementBuffer, shader);
    m_VertexArray.UnBind();
}