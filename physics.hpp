#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>
#include <cmath>

#include "shape.hpp"

class Physics {
    public:
        static void gravitationalPull(std::vector<Shape*> shapes);

    private:
        static constexpr float GRAVITATIONAL_CONSTANT = 6.67 * std::pow(10, -5);
};

#endif
