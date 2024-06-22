#ifndef TEXTURE_H
#define TEXTURE_H

#include "assert_utils.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "elementBuffer.h"
#include "shader.h"
#include <string>
#include <stb_image/stb_image.h>

class Texture{
private:
    std::string m_FilePath;
    unsigned int m_RenderID;
    unsigned char* m_Data;
    int m_Width, m_Height, m_nr_Channels;

public:
    Texture(std::string file_path);
    ~Texture();
    void Bind(unsigned int slot);
};
#endif
