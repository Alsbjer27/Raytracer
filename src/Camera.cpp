#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <iostream>



void Camera::render(const Hittable& world) {
    
    initialize();
    
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining " << (imageHeight - j) << " " << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            color pixelColor(0, 0, 0);
            for (int sample = 0; sample < samplesPerPixel; sample++) {
                Ray r = getRay(i, j);
                pixelColor += rayColor(r, maxDepth, world);
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

    cameraCenter = lookFrom;
 
    // Viewport dimensions
    auto theta = degreesToRadians(vfov);
    auto h = std::tan(theta / 2);
    auto viewportHeight = 2.0 * h * focusDistance;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

    w = glm::normalize(lookFrom - lookAt);
    u = glm::normalize(glm::cross(vup, w));
    v = glm::cross(w, u);

    // Horizontal and vertical vectors along viewport edges
    glm::vec3 viewportU = u * static_cast<float>(viewportWidth);
    glm::vec3 viewportV = -v * static_cast<float>(viewportHeight);

    // Horizontal and vertical deltas
    pixelDeltaU = viewportU / static_cast<float>(imageWidth);
    pixelDeltaV = viewportV / static_cast<float>(imageHeight);

    // Position of upper left pixel
    auto viewportUpperLeft = cameraCenter - (focusDistance * w) - viewportU / 2.0f - viewportV / 2.0f;
    topLeftPixelLoc = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);

    auto defocusRadius = focusDistance * std::tan(degreesToRadians(defocusAngle / 2));
    defocusDiskU = u * static_cast<float>(defocusRadius);
    defocusDiskV = v * static_cast<float>(defocusRadius);
}



color Camera::rayColor(const Ray& r, int depth, const Hittable& world) const {
    if (depth <= 0)
        return color(0, 0, 0);

    hitRecord rec;

    // ---------- Intersection ----------
    if (!world.hit(r, Interval(0.001, infinity), rec)) {
        // If nothing was hit just return background
        return background;
    }

    // ---------- Emission + Scattering ----------
    color emitted = rec.mat
        ? rec.mat->emitted(rec.u, rec.v, rec.p)
        : color(0, 0, 0);

    Ray scattered;
    color attenuation;

    if (!rec.mat || !rec.mat->scatter(r, rec, attenuation, scattered))
        return emitted; // hit light source or non-scattering surface

    return emitted + attenuation * rayColor(scattered, depth - 1, world);
}


glm::vec3 Camera::defocusDiskSample() const
{
    auto p = randomInUnitDisk();
    return cameraCenter + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
}

Ray Camera::getRay(int i, int j) const
{
    auto offset = sampleSquare();

    auto pixelSample = topLeftPixelLoc
        + pixelDeltaU * (i + offset.x)
        + pixelDeltaV * (j + offset.y);

    auto rayOrigin = (defocusAngle <= 0) ? cameraCenter : defocusDiskSample();
    auto rayDirection = pixelSample - rayOrigin;
    auto rayTime = randomDouble();

    return Ray(rayOrigin, rayDirection, rayTime);
}

glm::vec3 Camera::sampleSquare() const
{
    return glm::vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}
