#include "RtWeekend.h"
#include "BVH.h"
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

    auto red = make_shared<Lambertian>(color(.65, .05, .05));
    auto white = make_shared<Lambertian>(color(.73, .73, .73));
    auto green = make_shared<Lambertian>(color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(color(15, 15, 15));

    // Quads
    world.add(make_shared<Quad>(glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 555), green));
    world.add(make_shared<Quad>(glm::vec3(0, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 555), red));
    world.add(make_shared<Quad>(glm::vec3(343, 554, 332), glm::vec3(-130, 0, 0), glm::vec3(0, 0, -105), light));
    world.add(make_shared<Quad>(glm::vec3(0, 0, 0), glm::vec3(555, 0, 0), glm::vec3(0, 0, 555), white));
    world.add(make_shared<Quad>(glm::vec3(555, 555, 555), glm::vec3(-555, 0, 0), glm::vec3(0, 0, -555), white));
    world.add(make_shared<Quad>(glm::vec3(0, 0, 555), glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), white));


    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = 600;
    cam.samplesPerPixel = 200;
    cam.maxDepth = 50;
    cam.background = color(0, 0, 0);

    cam.vfov = 40;
    cam.lookFrom = glm::vec3(278, 278, -800);
    cam.lookAt = glm::vec3(278, 278, 0);
    cam.vup = glm::vec3(0, 1, 0);

    cam.defocusAngle = 0;

    cam.render(world);
}
