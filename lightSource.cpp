#include <glm/glm.hpp>

#include "lightSource.hpp"
#include "cube.hpp"
#include "sphere.hpp"

LightSource::LightSource(glm::vec3 pos, glm::vec4 lightColor) {
    shape = new Sphere(pos, 2, TEXTURES::SUN);
    this->lightColor = lightColor;
}

void LightSource::update() {
    shape->update();
}

void LightSource::render(Shader* shader) {
    shape->render(shader);
}
