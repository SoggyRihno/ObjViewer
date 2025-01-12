#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Camera::updateMouse(float x, float y) {
    yaw += (x - lastX) * sensitivity;
    pitch += (lastY - y) * sensitivity;

    pitch = std::max(std::min(pitch, 89.0f), -89.0f);

    cameraFront = glm::normalize(
            glm::vec3(
                    cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                    sin(glm::radians(pitch)),
                    sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
    lastX = x;
    lastY = y;
}

void Camera::forward(float deltaTime) {
    cameraPos += speed * sprintMultiplier * cameraFront * deltaTime;

}

void Camera::back(float deltaTime) {
    cameraPos -= speed * sprintMultiplier * cameraFront * deltaTime;

}

void Camera::right(float deltaTime) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * sprintMultiplier * deltaTime;
}

void Camera::left(float deltaTime) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed * sprintMultiplier * deltaTime;
}

void Camera::sprint(float mult) {
    sprintMultiplier = mult < 0 ? 0 : mult;
}

void Camera::updateUniforms(const Program &program) const {
    program.setMatx4fv("projection", glm::perspective(glm::radians(fov), width / height, 0.1f, 10000.0f));
    program.setMatx4fv("view", glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp));
    program.set3fv("viewPos", cameraPos);
    program.set3fv("lightPos", cameraPos);
}

glm::vec3 Camera::getPosition() {
    return cameraPos;
}

