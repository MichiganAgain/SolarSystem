#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "game.hpp"

void Game::run() {
    initWindow();
    mainloop();
    cleanup();
}

void Game::initWindow() {
    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW library");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowName, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        cleanup();
        throw std::runtime_error("Failed to initialize GLEW");
    }
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::mainloop() {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1875f, 0.1875f, 0.1875f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::processInput() {
    
}

void Game::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}