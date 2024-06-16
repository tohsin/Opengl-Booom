#include <shader_s.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
         std::cout << "DEBUG::ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    ID = createShader(vertexCode, fragmentCode);
    // compile shaders

}

void Shader::use(){
    GLCALL(glUseProgram(ID));
}

void Shader::setBool(const std::string &name, bool value) const {
    GLCALL(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}

void Shader::setInt(const std::string &name, int value) const
{
    GLCALL(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}
void Shader::setFloat(const std::string &name, float value) const
{
    GLCALL(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

unsigned int Shader::createShader(const std::string& vertexShaderSource,  const std::string& fragmentShaderSource){
    unsigned int shaderProgram = glCreateProgram();
    GLCALL(unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource));
    GLCALL(unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource));  // fragment shader for color output of the pixels
    
    GLCALL(glAttachShader(shaderProgram, vertexShader));
    GLCALL(glAttachShader(shaderProgram, fragmentShader));
    GLCALL(glLinkProgram(shaderProgram));

    int success;
    char infoLog[512];
    GLCALL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Debug: ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    GLCALL(glDeleteShader(vertexShader));
    GLCALL(glDeleteShader(fragmentShader));
    return shaderProgram;
}
unsigned int Shader::compileShader(unsigned int type, const std::string &source){
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    GLCALL(glShaderSource(shader, 1, &src, NULL));
    GLCALL(glCompileShader(shader));


    int success;
    char infoLog[512];
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Debug: ERROR::SHADER::"<<
        (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
         <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
