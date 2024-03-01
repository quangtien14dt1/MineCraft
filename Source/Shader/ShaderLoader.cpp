#include "ShaderLoader.h"



std::string ShaderUtil::GetFileContents(const std::string& path) {
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + path);
    }
    std::stringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
}

GLuint ShaderUtil::CompileShader(const GLchar* source, GLenum shaderType) {
    auto shaderID = glCreateShader(shaderType);

    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    GLint isSuccess = 0;
    GLchar infoLog[512];

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
    if (!isSuccess) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        throw std::runtime_error("Unable to load a shader: " +
            std::string(infoLog));
    }

    return shaderID;

}

GLuint ShaderUtil::LinkProgram(GLuint vertexID, GLuint fragmentID) {
    auto id = glCreateProgram();
    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);
    glLinkProgram(id);
    return id;
}

GLuint ShaderUtil::LoadShader(const std::string& vertex,
    const std::string& fragment) {

    /* load content from file */
    auto vertexSource = ShaderUtil::GetFileContents("Resource/shaders/" + vertex + ".vert");
    auto fragmentSource = ShaderUtil::GetFileContents("Resource/shaders/" + fragment + ".frag");

    /* creat by shader type : VERTEX_SHADER or FRAGMENT_SHADER */
    auto vertexShaderID = ShaderUtil::CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    auto fragmentShaderID = ShaderUtil::CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

    /* linking shader program */
    auto shaderID = ShaderUtil::LinkProgram(vertexShaderID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return shaderID;
}