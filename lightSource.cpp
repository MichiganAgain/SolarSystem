#include <glm/glm.hpp>

#include "lightSource.hpp"
#include "cube.hpp"
#include "sphere.hpp"

LightSource::LightSource(glm::vec3 pos, glm::vec3 intialVelocity, glm::vec4 lightColor, float SIZE, float mass = 0.0f) {
    shape = new Sphere(pos, intialVelocity, SIZE, mass, TEXTURES::SUN);
    shape->lightSource = true;
    this->SIZE = SIZE;
    this->lightColor = lightColor;
}

void LightSource::update() {
    if (shape) shape->update();
}

void LightSource::render(Shader* shader) {
    shape->render(shader);
}
