#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include <glm/glm.hpp>
#include "shader.hpp"
#include "shape.hpp"

class LightSource {
    public:
        LightSource(glm::vec3 pos, glm::vec4 lightColor, float SIZE);
        void update();
        void render(Shader* shader);

        Shape* shape;
        glm::vec4 lightColor;
        float SIZE;
};

#endif
