#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>
#include <vector>

// part of the flyweight design to be inherited and used as a singleton (even tho maybe controversial to use)
class ShapeVertexModel {
    public:
        unsigned int vertexArrayObjectID;
        std::vector<float> vertices;
        std::vector<int> indices;
        
    protected:
        virtual void initGlObjects() = 0;
        virtual void initVertices() = 0;
        virtual void initIndices() = 0;

        unsigned int vertexBufferObjectID;
        unsigned int elementBufferObjectID;
};

class Shape {
    public:
        virtual void update() = 0;
        virtual void render() = 0;

    protected:
        ShapeVertexModel* model;
        glm::vec3 worldCoord;
        glm::mat4 modelMatrix;
};

#endif
