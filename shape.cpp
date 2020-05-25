#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "shape.hpp"

unsigned int ShapeVertexModel::getVertexArrayID() { return vertexArrayObjectID; }
unsigned int ShapeVertexModel::getVertexBufferID() { return vertexBufferObjectID; }
unsigned int ShapeVertexModel::getElementBufferID() { return elementBufferObjectID; }
const std::vector<float>& ShapeVertexModel::getVertices() { return vertices; }
const std::vector<unsigned int>& ShapeVertexModel::getIndices() { return indices; }

void Shape::update() {
    if (nextState) {
        worldCoord += nextState->velocity;
        velocity = nextState->velocity;
        SIZE = nextState->SIZE;
        mass = nextState->mass;
    }
    initializeNextState();

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, worldCoord);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(SIZE, SIZE, SIZE));
}

void Shape::initializeNextState() {
    nextState = new ShapeState();
    nextState->velocity = velocity;	//	set velocity to the shapes current velocity as when applying the physics, the velocity is added / subtracted to
    nextState->SIZE = SIZE;			//	and then this velocity is added onto the shapes world coord
    nextState->mass = mass;
}
