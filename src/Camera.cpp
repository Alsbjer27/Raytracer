#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <iostream>



void Camera::render(const Hittable& world) {
    
    initialize();
    
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining" << (imageHeight - j) << " " << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            color pixelColor(0, 0, 0);
            for (int sample = 0; sample < samplesPerPixel; sample++) {
                Ray r = getRay(i, j);
                pixelColor += rayColor(r, world);
            }
            writeColor(std::cout, pixelColor * static_cast<float>(pixelSamplesScale));
        }
    }
    std::clog << "\rDone.       \n";
}



void Camera::initialize() {
    
    imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    pixelSamplesScale = 1.0 / samplesPerPixel;

    cameraCenter = glm::vec3(0, 0, 0);
 
    // Viewport dimensions
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

    // Horizontal and vertical vectors along viewport edges
    auto viewportU = glm::vec3(viewportWidth, 0, 0);
    auto viewportV = glm::vec3(0, -viewportHeight, 0);

    // Horizontal and vertical deltas
    pixelDeltaU = viewportU / static_cast<float>(imageWidth);
    pixelDeltaV = viewportV / static_cast<float>(imageHeight);

    // Position of upper left pixel
    auto viewportUpperLeft = cameraCenter - glm::vec3(0, 0, focalLength) - viewportU / 2.0f - viewportV / 2.0f;
    topLeftPixelLoc = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
}



color Camera::rayColor(const Ray& r, const Hittable& world) const {
    hitRecord rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
        return 0.5f * (rec.normal + color(1, 1, 1));
    }

    glm::vec3 normalizedDir = glm::normalize(r.dir);
    auto a = 0.5f * (normalizedDir.y + 1.0f);
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
}

Ray Camera::getRay(int i, int j) const
{
    auto offset = sampleSquare();

    auto pixelSample = topLeftPixelLoc
        + pixelDeltaU * (i + offset.x)
        + pixelDeltaV * (j + offset.y);
    auto rayOrigin = cameraCenter;
    auto rayDirection = pixelSample - rayOrigin;

    return Ray();
}

glm::vec3 Camera::sampleSquare() const
{
    return glm::vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}
