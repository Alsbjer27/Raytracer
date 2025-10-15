#pragma once
#include "RtWeekend.h"
#include "Hittable.h"
#include "Material.h"
#include "Ray.h"
#include "Color.h"
#include <glm/glm.hpp>



class Camera {
public:
    
    double aspectRatio = 1.0;
    int imageWidth = 100;
    int samplesPerPixel = 10;
    int maxDepth = 10;
    color background;

    double vfov = 90;
    glm::vec3 lookFrom = glm::vec3(0, 0, 0);
    glm::vec3 lookAt = glm::vec3(0, 0, -1);
    glm::vec3 vup = glm::vec3(0, 1, 0);

    double defocusAngle = 0;
    float focusDistance = 10.0f;
    
    void render(const Hittable& world);
    
private:
    
    int imageHeight = 0;
    double pixelSamplesScale;
    glm::vec3 cameraCenter;
    glm::vec3 pixelDeltaU;
    glm::vec3 pixelDeltaV;
    glm::vec3 topLeftPixelLoc;

    glm::vec3 u, v, w;
    glm::vec3 defocusDiskU;
    glm::vec3 defocusDiskV;
    
    void initialize();
    color rayColor(const Ray& r, int depth, const Hittable& world) const;
    glm::vec3 defocusDiskSample() const;
    Ray getRay(int i, int j) const;
    glm::vec3 sampleSquare() const;
    
};
