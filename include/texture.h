#ifndef TEXTURE_H
#define TEXTURE_H

#include "assert_utils.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "shader.h"
#include <string>
#include <stb_image/stb_image.h>

enum TextureType{
    None,
    Diffuse,
    Specular
};
class Texture{
    
private:
    std::string m_FilePath;
    unsigned int m_RenderID;
    unsigned char* m_Data;
    int m_Width, m_Height, m_nr_Channels;
    TextureType m_Type;

public:
    Texture(std::string file_path,  TextureType type);
    ~Texture();
    inline TextureType getType() const {return m_Type;};
    inline std::string getFilePath() const {return m_FilePath;};
    static std::string getTypeLiteral(TextureType);
    static TextureType getLiteralFromString(std::string type);
    void Bind(unsigned int slot);
};
#endif
