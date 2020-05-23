#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>
#include <vector>

// part of the flyweight design to be inherited and used as a singleton (even tho maybe controversial to use but oh wellz)
class ShapeVertexModel {
    public:
        unsigned int vertexArrayObjectID;
        unsigned int vertexBufferObjectID;
        unsigned int elementBufferObjectID;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        
    protected:
        virtual void initVertices() = 0;
        virtual void initIndices() = 0;
        virtual void initGlObjects() = 0;
};

class Shape {
    public:
        virtual void update() = 0;
        virtual void render() = 0;
        glm::mat4 modelMatrix;

    protected:
        ShapeVertexModel* model;
        glm::vec3 worldCoord;
};

#endif
