#include <iostream>
#include "Color.h"
#include "Ray.h"
#include <glm/glm.hpp>


bool hitShpere(const glm::vec3& center, double radius, const Ray& r) {
    glm::vec3 originToSphereCenter = center - r.ori;
    auto a = glm::dot(r.dir, r.dir);
    auto b = -2.0 * glm::dot(r.dir, originToSphereCenter);
    auto c = glm::dot(originToSphereCenter, originToSphereCenter) - radius*radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

color rayColor(const Ray& r) {
    if (hitShpere(glm::vec3(0, 0, -1), 0.1, r)) {
        return color(1, 0, 0);
    }

    glm::vec3 normalizedDir = glm::normalize(r.dir);
    auto a = 0.5f * (normalizedDir.y + 1.0f);
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // Image height
    int imageHeight = int(imageWidth / aspectRatio); 
    if (imageHeight < 1){                               // Ensures that imageHeight is at least 1
        imageHeight = 1;
    }
    else {
        imageHeight = imageHeight;
    }

    // Camera
    auto focalLenght = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = glm::vec3(0, 0, 0);

    // Horizontal and vertical vectors along viewport edges
    auto viewportU = glm::vec3(viewportWidth, 0, 0);
    auto viewportV = glm::vec3(0, -viewportHeight, 0);

    // Horizontal and vertical deltas
    auto pixelDeltaU = viewportU / static_cast<float>(imageWidth);
    auto pixelDeltaV = viewportV / static_cast<float>(imageHeight);

    // Position of upper left pixel
    auto viewportUpperLeft = cameraCenter - glm::vec3(0, 0, focalLenght) - viewportU / 2.0f - viewportV - 2.0f;
    auto topLeftPixelLoc = viewportUpperLeft + 5.0f * (pixelDeltaU + pixelDeltaV);

    // Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining" << (imageHeight - j) << " " << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter = topLeftPixelLoc + (pixelDeltaU * static_cast<float>(i)) + (static_cast<float>(j) * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.       \n";
}