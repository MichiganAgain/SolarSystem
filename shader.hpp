#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>
#include <string>

class Shader {
    public:
        Shader(std::string vertexShaderFileName, std::string fragmentShaderFileName);
        void use();
        void setVec3(const char* name, const glm::vec3& vec3);
        void setMat4(const char* name, const glm::mat4& mat4);
        void setInt(const char* name, int value);

    private:
        unsigned int shaderProgramID;
};

#endif
