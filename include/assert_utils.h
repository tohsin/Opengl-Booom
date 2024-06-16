#ifndef ASSERT_UTILS_H
#define ASSERT_UTILS_H

#include <iostream>
#include <cstdlib> // For abort()
#include <glad/glad.h>

void __debugbreak();
void GLClearError();
bool GLLOGCALL(const char* function, const char* file, int line);




// Assertion macros
#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLOGCALL(#x, __FILE__, __LINE__ ))

#endif // ASSERT_UTILS_H