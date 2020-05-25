#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <algorithm>

#include "camera.hpp"


		//	Camera currently uses Euler angles
Camera::Camera(glm::vec3 pos, glm::vec3 orientation, float fov, float ar) {
    worldCoord = pos;
    roll = orientation.x;
    pitch = orientation.y;
    yaw = orientation.z;
    fieldOfView = fov;
    aspectRatio = ar;
}

void Camera::update() {
    float xDirection = std::cos(pitch) * std::cos(yaw);
    float yDirection = std::sin(pitch);
    float zDirection = std::cos(pitch) * std::sin(yaw);
    cameraFrontDirection = glm::normalize(glm::vec3(xDirection, yDirection, zDirection));

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(worldCoord, cameraFrontDirection + worldCoord, cameraUp);

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::perspective(fieldOfView, aspectRatio, minFrustum, maxFrustum);
}

void Camera::handleMouse(float xPos, float yPos, float deltaTime) {
    float xOffset = xPos - lastXPos;
    float yOffset = lastYPos - yPos;

    lastXPos = xPos;
    lastYPos = yPos;

    pitch += yOffset * lookSensitivity * deltaTime;
    yaw += xOffset * lookSensitivity * deltaTime;

    if (pitch > glm::radians(89.0f)) pitch = glm::radians(89.0f);
    else if (pitch < glm::radians(-89.0f)) pitch = glm::radians(-89.0f);
}

void Camera::handleScroll(float xOffset, float yOffset, float deltaTime) {
    float scrollValue = yOffset * zoomSensitivity * deltaTime;
    fieldOfView += scrollValue;

    if (fieldOfView > maxZoom) fieldOfView = maxZoom;
    else if (fieldOfView < minZoom) fieldOfView = minZoom;
}

void Camera::handleKeyboard(int KEY, float deltaTime) {
    if (KEY == GLFW_KEY_W) worldCoord += cameraFrontDirection * movementSpeed * deltaTime;
    if (KEY == GLFW_KEY_S) worldCoord -= cameraFrontDirection * movementSpeed * deltaTime;
    if (KEY == GLFW_KEY_A) worldCoord -= glm::normalize(glm::cross(cameraFrontDirection, cameraUp)) * movementSpeed * deltaTime;
    if (KEY == GLFW_KEY_D) worldCoord += glm::normalize(glm::cross(cameraFrontDirection, cameraUp)) * movementSpeed * deltaTime;
    if (KEY == GLFW_KEY_SPACE) worldCoord += cameraUp * movementSpeed * deltaTime;
    if (KEY == GLFW_KEY_LEFT_CONTROL) worldCoord -= cameraUp * movementSpeed * deltaTime;
}

void Camera::updateCameraAspectRatio(float ar) {
    this->aspectRatio = ar;
}

glm::mat4& Camera::getViewMatrix() { return viewMatrix; }
glm::mat4& Camera::getProjectionMatrix() { return projectionMatrix; }
