#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(glm::vec3 pos, glm::vec3 orientation, float fov, float aspectRatio, const int minFrustum, const int maxFrustum);
        void update();
        glm::mat4& getViewMatrix();
        glm::mat4& getProjectionMatrix();

    private:
        glm::vec3 worldCoord;
        glm::vec3 cameraFrontDirection;
        const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        float fieldOfView;
        float aspectRatio;
        float minFrustum;
        float maxFrustum;

        float roll, pitch, yaw;
};

#endif
