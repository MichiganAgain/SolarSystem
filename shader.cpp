#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "shader.hpp"
#include "fileManager.hpp"

Shader::Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName) {
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShaderCode = FileManager::readFile(vertexShaderFileName);
    std::string fragmentShaderCode = FileManager::readFile(fragmentShaderFileName);
    const char* vertexShaderCodePointer = vertexShaderCode.c_str();
    const char* fragmentShaderCodePointer = fragmentShaderCode.c_str();

    glShaderSource(vertexShaderID, 1, &vertexShaderCodePointer, nullptr);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCodePointer, nullptr);
    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        std::cout << "Vertex Shader Compile Error: " << infoLog << std::endl;
        throw std::runtime_error("Failed to compile shader");
    }
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
        std::cout << "Fragment Shader Compile Error: " << infoLog << std::endl;
        throw std::runtime_error("Failed to compile shader");
    }

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    glGetShaderiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cout << "Failed to link shader program: " << infoLog << std::endl;
        throw std::runtime_error("Failed to link shader program");
    }
}

void Shader::use() {
    glUseProgram(shaderProgramID);
}

void Shader::setVec3(const char* name, const glm::vec3& vec3) {
    glUniform3fv(glGetUniformLocation(shaderProgramID, name), 1, &vec3[0]);
}

void Shader::setMat4(const char* name, const glm::mat4& mat4) {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name), 1, GL_FALSE, &mat4[0][0]);
}

void Shader::setInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(shaderProgramID, name), value);
}
