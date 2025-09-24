#pragma once
#include "RtWeekend.h"
#include "Hittable.h"
#include "Ray.h"
#include "Color.h"
#include <glm/glm.hpp>



class Camera {
public:
    
    double aspectRatio = 1.0;
    int imageWidth = 100;
    int samplesPerPixel = 100;
    
    void render(const Hittable& world);
    
private:
    
    int imageHeight = 0;
    double pixelSamplesScale;
    glm::vec3 cameraCenter;
    glm::vec3 pixelDeltaU;
    glm::vec3 pixelDeltaV;
    glm::vec3 topLeftPixelLoc;
    
    void initialize();
    color rayColor(const Ray& r, const Hittable& world) const;
    Ray getRay(int i, int j) const;
    glm::vec3 sampleSquare() const;
    
};
