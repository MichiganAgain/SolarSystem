#include "shape.hpp"

unsigned int ShapeVertexModel::getVertexArrayID() { return vertexArrayObjectID; }
unsigned int ShapeVertexModel::getVertexBufferID() { return vertexBufferObjectID; }
unsigned int ShapeVertexModel::getElementBufferID() { return elementBufferObjectID; }
const std::vector<float>& ShapeVertexModel::getVertices() { return vertices; }
const std::vector<unsigned int>& ShapeVertexModel::getIndices() { return indices; }
