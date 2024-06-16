#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <assert_utils.h>

class Shader
{
public:
    // program ID
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    unsigned int createShader(const std::string& vertexShaderSource,  const std::string& fragmentShaderSource);
    unsigned int compileShader(unsigned int type, const std::string &source);

};

#endif