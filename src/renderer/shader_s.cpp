#include <shader_s.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)    
    :m_VertexFilePath(vertexPath), m_FragmentFilePath(fragmentPath), m_RenderID(0)

{

    ShaderProgramSource source = parseShader(vertexPath, fragmentPath);

    m_RenderID = createShader(source.vertexSource, source.fragmentSource);
    // compile shaders

}
Shader::~Shader(){
    GLCALL(glDeleteProgram(m_RenderID));
}
ShaderProgramSource Shader::parseShader(const char* vertexPath, const char* fragmentPath){
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

    return{vertexCode, fragmentCode};
}

void Shader::Bind(){
    GLCALL(glUseProgram(m_RenderID));
}
void Shader::UnBind(){
    GLCALL(glUseProgram(0));
}


void Shader::setBool(const std::string &name, bool value) const {
    GLCALL(glUniform1i(glGetUniformLocation(m_RenderID, name.c_str()), (int)value));
}

void Shader::setInt(const std::string &name, int value)
{
    GLCALL(glUniform1f(getUniformLocation(name), value));
}
void Shader::setFloat(const std::string &name, float value)
{
    // GLCALL(glUniform1f(glGetUniformLocation(m_RenderID, name.c_str()), value));
    GLCALL(glUniform1f(getUniformLocation(name), value));
}

int Shader::getUniformLocation(const std::string &name){
    if (uniformLocationCache.find(name) != uniformLocationCache.end()){
        return uniformLocationCache[name];
    }
    GLCALL( int location = glGetUniformLocation(m_RenderID, name.c_str()))
    if(location == -1){
        std::cout<< "DEBUG: " << "Warning Uniform " << name << " doesn't exist" << std::endl; 
    }
    uniformLocationCache[name] = location;
    return location;    
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
