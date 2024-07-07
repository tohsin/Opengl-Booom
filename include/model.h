#pragma once
#include <vector>
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "texture.h"
class Model{
private:
    // std::vector<Texture> textures_loaded;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene );
    Mesh processMesh(aiMesh *mesh, const aiScene *scene );
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

public:
    Model(const char* path);
    void Draw(Shader &shader, Renderer& renderer);
};