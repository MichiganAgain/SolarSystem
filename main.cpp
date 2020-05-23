#include <iostream>
#include <stdexcept>

#include "game.hpp"

int main() {
    Game game;
    try {
        game.run();
    } catch (std::exception& e) {
        std::cout << "CAUGHT ERROR ----------->" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "CAUGHT ERROR ----------->" << std::endl;
    }

    return 0;
}