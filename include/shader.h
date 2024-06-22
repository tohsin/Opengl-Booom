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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    // set uniforms

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

    void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
    void setUniformMat4(const std::string& name, const glm::mat4 mat);

    void setUniformVec2f(const std::string& name, float f0, float f1);
    void setUniformVec2f(const std::string& name, const glm::vec2 value);

    void setUniformVec3f(const std::string& name, float f0, float f1, float f2);
    void setUniformVec3f(const std::string& name, const glm::vec3 value);


};

#endif