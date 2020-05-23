#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>

#include "shape.hpp"

class SphereVertexModel: public ShapeVertexModel {
    public:
        static SphereVertexModel* instance();
        SphereVertexModel();

    private:
        virtual void initGlObjects() override;
        virtual void initVertices() override;
        virtual void initIndices() override;

        static constexpr int stacks = 10;
        static constexpr int sectors = 20;
        static constexpr float radius = 1;
};

class Sphere: public Shape {
    public:
        Sphere(glm::vec3 pos);
        virtual void update() override;
        virtual void render() override;
};

#endif
