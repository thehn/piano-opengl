#ifndef UTILS_H
#define UTILS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "models/shaderprogram.h"
namespace Utils{
    extern void assignVBOtoAttribute(ShaderProgram *shaderProgram,char* attributeName, GLuint bufVBO, int vertexSize);
    extern GLuint makeBuffer(void *data, int vertexCount, int vertexSize);
}
#endif