#include "RtWeekend.h"
#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "Quad.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>



int main() {

    HittableList world;

    auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = make_shared<Lambertian>(color(0.1, 0.8, 0.5));
    auto materialLeft = make_shared<Dielectric>(1.50);
    auto materialBubble = make_shared<Dielectric>(1.00 / 1.50);
    auto materialRight = make_shared<Metal>(color(0.8, 0.6, 1.0), 0.0);


   
    world.add(make_shared<Sphere>(glm::vec3(0.6, 0, -1.2), 0.5, materialCenter));
    world.add(make_shared<Sphere>(glm::vec3(-0.6, 0, -1.2), 0.5, materialRight));

    world.add(make_shared<Sphere>(glm::vec3(0, -100.5, -1.2), 100, materialGround));


    Camera cam;
    
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 10;
    cam.maxDepth = 5;

    cam.render(world);
}
