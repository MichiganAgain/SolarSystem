#ifndef GAME_HPP
#define GAME_HPP

#include <GLFW/glfw3.h>
#include <vector>

#include "sphere.hpp"
#include "cube.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "lightSource.hpp"

class Game {
public:
    void run();
    void framebuffer_size_callback_handler(GLFWwindow* window, int width, int height);
    void mouse_callback_handler(GLFWwindow* window, double xPos, double yPos);
    void scroll_callback_handler(GLFWwindow* window, double xOffset, double yOffset);

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
    float deltaTime;

    Shader* lightingShader;
    Shader* lightObjectShader;
    
    Camera* camera;
    std::vector<Shape*> shapes;
    std::vector<Shape*> shapeTextures;
    std::vector<LightSource*> lightSources;
};

#endif
