#include "Camera.h"

Camera::Camera(int w, int h){
    // Camera is currently creating a sqare image, might implement a non-square camera

    origin = glm::vec3(-1.0f, 0.0f, 0.0f);              // We want to look in the YZ-plane
    direction = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));   // 
    width = w;
    height = h;

    double aspect = static_cast<double>(width) / height;
    double planeHeight = 2.0;
    double planeWidth = planeHeight * aspect;

    lowerLeft = glm::vec3(0.0, -planeHeight/2, -planeWidth/2); //  ^Z:  Working in YZ-Plane
    lowerRight = glm::vec3(0.0, planeHeight/2, -planeWidth/2); //  |
    upperLeft = glm::vec3(0.0, -planeHeight/2,  planeWidth/2);  // |
    upperRight = glm::vec3(0.0, planeHeight/2,  planeWidth/2);  // |______> Y

    this->pixelSize = static_cast<float>(planeHeight)/ height; // Avoids int division
}