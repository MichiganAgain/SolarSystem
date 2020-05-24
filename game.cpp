#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "game.hpp"

extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
extern void mouse_callback(GLFWwindow* window, double xPos, double yPos);
extern void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

void Game::run() {
    initWindow();
    initShaders();
    initGameObjects();
    mainloop();
    cleanup();
}

void Game::framebuffer_size_callback_handler(GLFWwindow* window, int width, int height) {
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
void Game::mouse_callback_handler(GLFWwindow* window, double xPos, double yPos) {
    camera->handleMouse(xPos, yPos, deltaTime);
}
void Game::scroll_callback_handler(GLFWwindow* window, double xOffset, double yOffset) {

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (glewInit() != GLEW_OK) {
        cleanup();
        throw std::runtime_error("Failed to initialize GLEW");
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::initShaders() {
    lightingShader = new Shader("resources/shaders/lightingVertex.shader", "resources/shaders/lightingFragment.shader");
}

void Game::initGameObjects() {
    camera = new Camera({-3.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, glm::radians(45.0f), float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 10000.0f);
    spheres.push_back(new Sphere({0.0f, 0.0f, 0.0f}));
}

void Game::mainloop() {
    float currentTime = glfwGetTime();
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.1875f, 0.1875f, 0.1875f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->worldCoord += camera->cameraFrontDirection * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->worldCoord -= camera->cameraFrontDirection * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->worldCoord -= glm::normalize(glm::cross(camera->cameraFrontDirection, camera->cameraUp)) * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->worldCoord += glm::normalize(glm::cross(camera->cameraFrontDirection, camera->cameraUp)) * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera->worldCoord += camera->cameraUp * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera->worldCoord -= camera->cameraUp * deltaTime;
}

void Game::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}