#include <GL/glew.h>

#include "shape.hpp"

unsigned int ShapeVertexModel::getVertexArrayID() { return vertexArrayObjectID; }
unsigned int ShapeVertexModel::getVertexBufferID() { return vertexBufferObjectID; }
unsigned int ShapeVertexModel::getElementBufferID() { return elementBufferObjectID; }
const std::vector<float>& ShapeVertexModel::getVertices() { return vertices; }
const std::vector<unsigned int>& ShapeVertexModel::getIndices() { return indices; }

void ShapeVertexModel::initGlObjects() {
    glGenVertexArrays(1, &vertexArrayObjectID);
    glBindVertexArray(vertexArrayObjectID);

    glGenBuffers(1, &vertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &elementBufferObjectID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
