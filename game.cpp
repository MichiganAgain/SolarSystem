#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "game.hpp"

void Game::run() {
    initWindow();
    initShaders();
    initGameObjects();
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

void Game::initShaders() {
    lightingShader = new Shader("resources/shaders/lightingVertex.shader", "resources/shaders/lightingFragment.shader");
}

void Game::initGameObjects() {
    camera = new Camera({-3.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, glm::radians(90.0f), float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 10000.0f);
    spheres.push_back(new Sphere({0.0f, 0.0f, 0.0f}));
}

void Game::mainloop() {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1875f, 0.1875f, 0.1875f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);

        lightingShader->use();
        camera->update();
        lightingShader->setMat4("viewMatrix", camera->getViewMatrix());
        lightingShader->setMat4("projectionMatrix", camera->getProjectionMatrix());

        for (Sphere* sphere : spheres) {
            sphere->update();
            lightingShader->setMat4("modelMatrix", sphere->modelMatrix);
            sphere->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Game::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}