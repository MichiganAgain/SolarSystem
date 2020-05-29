#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "physics.hpp"
#include "shape.hpp"
#include "sphere.hpp"

void Physics::gravitationalPull(std::vector<Shape*> shapes) {
    for (int i = 0; i < shapes.size(); i++) {
        for (int n = i + 1; n < shapes.size(); n++) {
            if (shapes[i]->mass != 0 && shapes[n]->mass != 0) {
                float xDiff = shapes[i]->worldCoord.x - shapes[n]->worldCoord.x;
                float yDiff = shapes[i]->worldCoord.y - shapes[n]->worldCoord.y;
                float zDiff = shapes[i]->worldCoord.z - shapes[n]->worldCoord.z;
                float distance = std::sqrt(std::pow(xDiff, 2) + std::pow(yDiff, 2) + std::pow(zDiff, 2));
                glm::vec3 differences = glm::normalize(glm::vec3(xDiff, yDiff, zDiff));

                    // Not the real equation as squaring the distance had too little effect to be interesting when the range increased
                float gravitationalForce = (GRAVITATIONAL_CONSTANT * shapes[i]->mass * shapes[n]->mass) / std::pow(distance, 1);
                shapes[i]->nextState->velocity.x -= differences.x * gravitationalForce / shapes[i]->mass;
                shapes[i]->nextState->velocity.y -= differences.y * gravitationalForce / shapes[i]->mass;
                shapes[i]->nextState->velocity.z -= differences.z * gravitationalForce / shapes[i]->mass;
                shapes[n]->nextState->velocity.x += differences.x * gravitationalForce / shapes[n]->mass;
                shapes[n]->nextState->velocity.y += differences.y * gravitationalForce / shapes[n]->mass;
                shapes[n]->nextState->velocity.z += differences.z * gravitationalForce / shapes[n]->mass;
            }
        }
    }
}
