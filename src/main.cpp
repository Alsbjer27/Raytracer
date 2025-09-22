#include "RtWeekend.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>


color rayColor(const Ray& r, const Hittable& world) {
    hitRecord rec;
    if (world.hit(r,0,infinity, rec)) {
        return 0.5f * (rec.normal + color(1, 1, 1));
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

    HittableList world;
    world.add(make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(glm::vec3(0, -100.5, -1), 100));

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
    auto viewportUpperLeft = cameraCenter - glm::vec3(0, 0, focalLenght) - viewportU / 2.0f - viewportV / 2.0f;
    auto topLeftPixelLoc = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);

    // Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining" << (imageHeight - j) << " " << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter = topLeftPixelLoc + (pixelDeltaU * static_cast<float>(i)) + (static_cast<float>(j) * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            color pixelColor = rayColor(r,world);
            writeColor(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.       \n";
}