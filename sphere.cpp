#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>

#include "sphere.hpp"
#include "textures.hpp"
#include "shader.hpp"

SphereVertexModel* SphereVertexModel::instance() {
    static SphereVertexModel ssvm = SphereVertexModel();
    return &ssvm;
}

SphereVertexModel::SphereVertexModel() {
    initVertices();
    initIndices();
    initGlObjects();
}

void SphereVertexModel::initVertices() {
    constexpr float stackAngleStep = M_PI / float(stacks);
    constexpr float sectorAngleStep = (2 * M_PI) / float(sectors);

    int stack, sector;
    float stackAngle, sectorAngle;
    float x, y, z, cosOfStackAngle;
    for (stack = 0; stack <= stacks; stack++) {
        stackAngle = (M_PI / 2) - (stack * stackAngleStep);
        y = radius * std::sin(stackAngle);
        cosOfStackAngle = std::cos(stackAngle);
        for (sector = 0; sector <= sectors; sector++) {
            sectorAngle = sector * sectorAngleStep;
            x = radius * cosOfStackAngle * std::cos(sectorAngle);
            z = radius * cosOfStackAngle * std::sin(sectorAngle);
            vertices.push_back(x);  // position
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(float(sector) / sectors);    // texture coord
            vertices.push_back(float(stack) / stacks);
            vertices.push_back(x);  // surface normal
            vertices.push_back(y);  // x y z as unit sphere already
            vertices.push_back(z);  // instead of * by inverse of radius
        }
    }
}

void SphereVertexModel::initIndices() {
    int k1, k2;
    for (int stack = 0; stack < stacks; stack++) {
        k1 = stack * (sectors + 1);
        k2 = k1 + sectors + 1;
        for (int sector = 0; sector < sectors; sector++, k1++, k2++) {
            if (stack != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (stack != stacks - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

Sphere::Sphere(glm::vec3 pos) {
    worldCoord = pos;
    model = SphereVertexModel::instance();
    textureID = Texture::getTexture(TEXTURES::GRADIENT);
}

void Sphere::update() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, worldCoord);
}

void Sphere::render(Shader* shader) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    shader->setInt("texture0", 0);

    glBindVertexArray(model->getVertexArrayID());
    glBindBuffer(GL_ARRAY_BUFFER, model->getVertexBufferID());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getElementBufferID());
    glDrawElements(GL_TRIANGLES, model->getIndices().size(), GL_UNSIGNED_INT, 0);
}
