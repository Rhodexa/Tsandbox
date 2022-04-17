#pragma once

#include <GL/glew.h>
#include <iostream>

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#define ASSERT(x) if (!(x)) __debugbreak();
#define gltry(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))


