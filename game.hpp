#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>
#include <vector>

#include "sphere.hpp"
#include "shader.hpp"

class Game {
public:
    void run();

private:
    void initWindow();
    void initShaders();
    void initGameObjects();
    void mainloop();
    void processInput(GLFWwindow* window);
    void cleanup();

    GLFWwindow* window;
    int WINDOW_WIDTH = 1000;
    int WINDOW_HEIGHT = 1000;
    const char* windowName = "Solar System";

    Shader* lightingShader;
    std::vector<Sphere*> spheres;
};

#endif
