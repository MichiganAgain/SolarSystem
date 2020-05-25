#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>
#include <cmath>

#include "shape.hpp"

class Physics {
    public:
        static void gravitationalPull(std::vector<Shape*> shapes);

    private:
		//	Not the exact constant, but having it to the power of -11 had too little effect to be interesting
        static constexpr float GRAVITATIONAL_CONSTANT = 6.67 * std::pow(10, -5);
};

#endif
 