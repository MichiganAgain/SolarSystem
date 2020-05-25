#include <iostream>
#include <stdexcept>

#include "game.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
Game* gamePointer;	// as opengl can't have callback functions as member functions, use pointer to
					// hold game instance and call the game object's respective callback

int main() {
    Game game;
    gamePointer = &game;
    try {
        game.run();
    } catch (std::exception& e) {
        std::cout << "CAUGHT ERROR ----------->" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "CAUGHT ERROR ----------->" << std::endl;
    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    gamePointer->framebuffer_size_callback_handler(window, width, height);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    gamePointer->mouse_callback_handler(window, xPos, yPos);
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    gamePointer->scroll_callback_handler(window, xOffset, yOffset);
}
