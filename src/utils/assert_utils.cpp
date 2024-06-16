#include "assert_utils.h"

void __debugbreak() {
    std::cerr << "Assertion failed!" << std::endl;
    std::abort();
}

void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

bool GLLOGCALL(const char* function, const char* file, int line){
    while(GLenum error = glGetError()){
        std::cout<< "DEBUG: [Open GL ERROR] (0x" << std::hex << error << ") " << function <<
         " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}