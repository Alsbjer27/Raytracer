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

    auto leftRed = make_shared<Lambertian>(color(1.0, 0.2, 0.2));
    auto backGreen = make_shared<Lambertian>(color(0.2, 1.0, 0.2));
    auto rightBlue = make_shared<Lambertian>(color(0.2, 0.2, 1.0));
    auto upperOrange = make_shared<Lambertian>(color(1.0, 0.5, 0.0));
    auto lowerTeal = make_shared<Lambertian>(color(0.2, 0.8, 0.8));

    world.add(make_shared<Quad>(glm::vec3(-3, -2, 5), glm::vec3(0, 0, -4), glm::vec3(0, 4, 0), leftRed));
    world.add(make_shared<Quad>(glm::vec3(-2, -2, 0), glm::vec3(4, 0, 0), glm::vec3(0, 4, 0), backGreen));
    world.add(make_shared<Quad>(glm::vec3(3, -2, 1), glm::vec3(0, 0, 4), glm::vec3(0, 4, 0), rightBlue));
    world.add(make_shared<Quad>(glm::vec3(-2, 3, 1), glm::vec3(4, 0, 0), glm::vec3(0, 0, 4), upperOrange));
    world.add(make_shared<Quad>(glm::vec3(-2, -3, 5), glm::vec3(4, 0, 0), glm::vec3(0, 0, -4), lowerTeal));

    auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = make_shared<Lambertian>(color(0.1, 0.8, 0.5));
    auto materialLeft = make_shared<Dielectric>(1.50);
    auto materialBubble = make_shared<Dielectric>(1.00 / 1.50);
    auto materialRight = make_shared<Metal>(color(0.8, 0.6, 1.0), 0.2);


   
    world.add(make_shared<Sphere>(glm::vec3(0, 0, -1.2), 0.5, materialCenter));

    Camera cam;
    
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 100;
    cam.maxDepth = 50;

    cam.render(world);
}
