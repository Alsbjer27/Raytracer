#include "Camera.h"

Camera::Camera(int w, int h)
    : width(w), height(h), origin(0.0f, 2.0f, 2.0f)
{
    // Camera is currently creating a sqare image, might implement a non-square camera

    // Define camera plane in YZ-plane (x=1)
    lowerLeft = glm::vec3(1.0f, 1.5f, 1.5f);
    upperLeft = glm::vec3(1.0f, 1.5f, 2.5f);
    upperRight = glm::vec3(1.0f, 2.5f, 2.5f);
    lowerRight = glm::vec3(1.0f, 2.5f, 1.5f);

    horizontal = lowerRight - lowerLeft;
    vertical = upperLeft - lowerLeft;
}

Ray Camera::generateRay(int x, int y) const
{
    float u = (x + 0.5f) / static_cast<float>(width);
    float v = 1.0f - (y + 0.5f) / static_cast<float>(height); // flip y so top row is top

    glm::vec3 pointOnPlane = lowerLeft + u * horizontal + v * vertical;
    glm::vec3 direction = glm::normalize(pointOnPlane - origin);

    return Ray(origin, direction);
}

