#include "RtWeekend.h"
#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>



int main() {

    HittableList world;
    world.add(make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(glm::vec3(0, -100.5, -1), 100));

    Camera cam;
    
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 100;

    cam.render(world);
}
