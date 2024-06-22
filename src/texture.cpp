#include "texture.h"

Texture::Texture(std::string file_path)
    :m_FilePath(file_path), m_RenderID(0), m_Data(NULL), m_Width(0), m_Height(0), m_nr_Channels(0)
{
    GLCALL(glGenTextures(1, &m_RenderID));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID)); 
    stbi_set_flip_vertically_on_load(true);

    m_Data = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_nr_Channels, 0);




    // set the texture wrapping parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // set texture filtering parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


    if(m_Data){
        GLenum format;
        if (m_nr_Channels == 1)
            format = GL_RED;
        else if (m_nr_Channels == 3)
            format = GL_RGB;
        else if (m_nr_Channels == 4)
            format = GL_RGBA;
        // generate texture and minmaps from data
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Data));
        GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    }else{
        std::cout << "DEBUG: Failed to load texture" << std::endl;
    }

        // free the image memory
    stbi_image_free(m_Data);
}
Texture::~Texture(){
    GLCALL(glDeleteTextures(1, &m_RenderID));
}

void Texture::Bind(unsigned int slot){
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}