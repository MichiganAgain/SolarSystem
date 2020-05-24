#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 orientation, float fov, float ar, const int minF, const int maxF) {
    worldCoord = pos;
    roll = orientation.x;
    pitch = orientation.y;
    yaw = orientation.z;
    fieldOfView = fov;
    aspectRatio = ar;
    minFrustum = minF;
    maxFrustum = maxF;
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

glm::mat4& Camera::getViewMatrix() { return viewMatrix; }
glm::mat4& Camera::getProjectionMatrix() { return projectionMatrix; }
