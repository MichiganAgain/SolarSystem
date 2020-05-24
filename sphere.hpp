#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>

#include "shape.hpp"
#include "shader.hpp"
#include "textures.hpp"

class SphereVertexModel: public ShapeVertexModel {
    public:
        static SphereVertexModel* instance();
        SphereVertexModel();

    private:
        virtual void initVertices() override;
        virtual void initIndices() override;
        virtual void initGlObjects() override;

        static constexpr int stacks = 50;
        static constexpr int sectors = 100;
        static constexpr float radius = 1;
};

class Sphere: public Shape {
    public:
        Sphere(glm::vec3 pos, glm::vec3 initialVelocity, float SIZE, float mass, TEXTURES t);
        virtual void render(Shader* shader) override;
};

#endif
