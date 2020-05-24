#ifndef CUBE_HPP
#define CUBE_HPP

#include <glm/vec3.hpp>

#include "shape.hpp"
#include "shader.hpp"
#include "textures.hpp"

class CubeVertexModel: public ShapeVertexModel {
    public:
        static CubeVertexModel* instance();
        CubeVertexModel();

    private:
        virtual void initVertices() override;
        virtual void initIndices() override;
        virtual void initGlObjects() override;
};

class Cube: public Shape {
    public:
        Cube(glm::vec3 pos, glm::vec3 initialVelocity, float SIZE, float mass, TEXTURES t);
        virtual void render(Shader* shader) override;
};

#endif
