#include <glm/glm.hpp>

#include "lightSource.hpp"
#include "cube.hpp"
#include "sphere.hpp"

LightSource::LightSource(glm::vec3 pos, glm::vec4 lightColor, float SIZE) {
    shape = new Sphere(pos, SIZE, TEXTURES::SUN);
    this->SIZE = SIZE;
    this->lightColor = lightColor;
}

void LightSource::update() {
    shape->update();
}

void LightSource::render(Shader* shader) {
    shape->render(shader);
}
