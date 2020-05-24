#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>
#include <vector>

#include "shader.hpp"

enum class SHAPES {CUBE, SPHERE};

// part of the flyweight design to be inherited and used as a singleton (even tho maybe controversial to use but oh wellz)
class ShapeVertexModel {
    public:
        unsigned int getVertexArrayID();
        unsigned int getVertexBufferID();
        unsigned int getElementBufferID();
        const std::vector<float>& getVertices();
        const std::vector<unsigned int>& getIndices();
        
    protected:
        virtual void initVertices() = 0;
        virtual void initIndices() = 0;
        virtual void initGlObjects() = 0;

        unsigned int vertexArrayObjectID;
        unsigned int vertexBufferObjectID;
        unsigned int elementBufferObjectID;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};

class Shape {
    public:
        virtual void update() = 0;
        virtual void render(Shader* shader) = 0;
        glm::mat4 modelMatrix;
        glm::vec3 worldCoord;

    protected:
        unsigned int textureID;
        ShapeVertexModel* model;
};

#endif
