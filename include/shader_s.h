#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <assert_utils.h>
#include <string>
#include <unordered_map>

struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;

    ShaderProgramSource(std::string vsource, std::string fsource)
        : vertexSource(vsource), fragmentSource(fsource){}
};
class Shader
{
private:
    unsigned int createShader(const std::string& vertexShaderSource,  const std::string& fragmentShaderSource);
    unsigned int compileShader(unsigned int type, const std::string &source);
    ShaderProgramSource parseShader(const char* vertexPath, const char* fragmentPath);
    int getUniformLocation(const std::string &name);
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    // program ID
    const char*  m_VertexFilePath;
    const char*  m_FragmentFilePath;
    unsigned int m_RenderID;


    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Bind();
    void UnBind();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

    void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);


};

#endif