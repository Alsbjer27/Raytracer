#pragma once
#include "RtWeekend.h"
#include "Hittable.h"
#include "Ray.h"
#include "Color.h"
#include <glm/glm.hpp>



class Camera {
public:
    
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    
    void render(const Hittable& world);
    
private:
    
    int imageHeight = 0;
    glm::vec3 cameraCenter;
    glm::vec3 pixelDeltaU;
    glm::vec3 pixelDeltaV;
    glm::vec3 topLeftPixelLoc;
    
    void initialize();
    color rayColor(const Ray& r, const Hittable& world) const;
    
};
