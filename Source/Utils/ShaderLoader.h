#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>


namespace ShaderUtil {

    std::string GetFileContents(const std::string& path);

    GLuint CompileShader(const GLchar* source, GLenum shaderType);

    GLuint LinkProgram(GLuint vertexID, GLuint fragmentID);

    GLuint LoadShader(const std::string& vertex,
        const std::string& fragment);
}


