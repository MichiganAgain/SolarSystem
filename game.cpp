#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "game.hpp"
#include "textures.hpp"

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
    camera->updateCameraAspectRatio(float(WINDOW_WIDTH) / WINDOW_HEIGHT);
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
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::initShaders() {
    lightingShader = new Shader("resources/shaders/lightingVertex.shader", "resources/shaders/lightingFragment.shader");
    lightObjectShader = new Shader("resources/shaders/lightObjectVertex.shader", "resources/shaders/lightObjectFragment.shader");
}

void Game::initGameObjects() {
    camera = new Camera({-200.0f, 0.0f, 200.0f}, {0.0f, 0.0f, 0.0f}, glm::radians(45.0f), float(WINDOW_WIDTH) / WINDOW_HEIGHT);
    spheres.push_back(new Sphere({0.0f, 0.0f, 150.0f}, 0.24397f, TEXTURES::MERCURY));
    spheres.push_back(new Sphere({0.0f, 0.0f, 170.0f}, 0.60518f, TEXTURES::VENUS));
    spheres.push_back(new Sphere({0.0f, 0.0f, 190.0f}, 0.6371f, TEXTURES::EARTH));
    spheres.push_back(new Sphere({0.0f, 0.0f, 192.0f}, 0.17375f, TEXTURES::MOON));
    spheres.push_back(new Sphere({0.0f, 0.0f, 210.0f}, 0.33895f, TEXTURES::MARS));
    spheres.push_back(new Sphere({0.0f, 0.0f, 260.0f}, 6.9911f, TEXTURES::JUPITER));
    spheres.push_back(new Sphere({0.0f, 0.0f, 300.0f}, 5.8232f, TEXTURES::SATURN));
    spheres.push_back(new Sphere({0.0f, 0.0f, 330.0f}, 2.5362f, TEXTURES::URANUS));
    spheres.push_back(new Sphere({0.0f, 0.0f, 360.0f}, 2.4622f, TEXTURES::NEPTUNE));
    lightSources.push_back(new LightSource({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 69.5508f));
}

void Game::mainloop() {
    float currentTime = glfwGetTime();
    float lastTime = currentTime;
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.1875f, 0.1875f, 0.1875f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);
        lightingShader->use();
        camera->update();
        lightingShader->setVec4("lightColor", lightSources[0]->lightColor);
        lightingShader->setVec4("lightPos", lightSources[0]->shape->worldCoord);
        lightingShader->setVec3("viewPos", camera->worldCoord);
        lightingShader->setMat4("viewMatrix", camera->getViewMatrix());
        lightingShader->setMat4("projectionMatrix", camera->getProjectionMatrix());

        for (Sphere* sphere : spheres) {
            sphere->update();
            lightingShader->setMat4("modelMatrix", sphere->modelMatrix);
            sphere->render(lightingShader);
        }
        for (Cube* cube : cubes) {
            cube->update();
            lightingShader->setMat4("modelMatrix", cube->modelMatrix);
            cube->render(lightingShader);
        }

        lightObjectShader->use();
        lightObjectShader->setMat4("viewMatrix", camera->getViewMatrix());
        lightObjectShader->setMat4("projectionMatrix", camera->getProjectionMatrix());
        for (LightSource* lightSource : lightSources) {
            lightSource->update();
            lightingShader->setMat4("modelMatrix", lightSource->shape->modelMatrix);
            lightSource->render(lightObjectShader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->handleKeyboard(GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->handleKeyboard(GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->handleKeyboard(GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->handleKeyboard(GLFW_KEY_D, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera->handleKeyboard(GLFW_KEY_SPACE, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camera->handleKeyboard(GLFW_KEY_LEFT_CONTROL, deltaTime);
}

void Game::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}