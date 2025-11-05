#include "RtWeekend.h"
#include "BVH.h"
#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "Quad.h"
#include "Sphere.h"
#include "Triangle.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>



int main() {

    HittableList world;

    auto red = make_shared<Lambertian>(color(.65, .05, .05));
    auto white = make_shared<Lambertian>(color(.73, .73, .73));
    auto green = make_shared<Lambertian>(color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(color(15, 15, 15));
    auto metal = make_shared<Metal>(color(1.0, 1.0, 1.0), 0.0);
    auto blue = make_shared<Lambertian>(color(0.1, 0.2, 0.7));
    auto purple = make_shared<Lambertian>(color(0.3, 0.0, 0.5));
    auto trans = make_shared<Dielectric>(1.3);

    // Quads
    world.add(make_shared<Quad>(glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 800), green)); // Left Wall
    world.add(make_shared<Quad>(glm::vec3(0, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 800), blue)); // Right Wall
    world.add(make_shared<Quad>(glm::vec3(343, 554, 500), glm::vec3(-130, 0, 0), glm::vec3(0, 0, -105), light)); //Light
    world.add(make_shared<Quad>(glm::vec3(0, 0, 0), glm::vec3(555, 0, 0), glm::vec3(0, 0, 800), white)); // Floor
    world.add(make_shared<Quad>(glm::vec3(555, 555, 800), glm::vec3(-555, 0, 0), glm::vec3(0, 0, -800), white)); // Ceiling
    world.add(make_shared<Quad>(glm::vec3(0, 0, 800), glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), metal)); // Back Wall
    world.add(make_shared<Quad>(glm::vec3(0, 0, -10), glm::vec3(580, 0, 0), glm::vec3(0, 580, 0), red)); // Behind Camera Wall



    world.add(make_shared<Sphere>(glm::vec3(350, 400, 550), 75, trans));
    // Boxes
    // Switch for sphere
   /* shared_ptr<Hittable> box1 = Quad::box(glm::vec3(0, 0, 0), glm::vec3(165, 330, 165), white);
    box1 = make_shared<RotateY>(box1, 15);
    box1 = make_shared<Translate>(box1, glm::vec3(265, 0, 295));
    world.add(box1);*/



    // Keep but lift higher
    shared_ptr<Hittable> box2 = Quad::box(glm::vec3(0, 0, 0), glm::vec3(100, 100, 100), white);
    box2 = make_shared<RotateY>(box2, -18);
    box2 = make_shared<Translate>(box2, glm::vec3(330, 30, 600));
    world.add(box2);

    shared_ptr<Hittable> tetrahedron = Triangle::tetrahedron(
        glm::vec3(0, 0, 0),
        glm::vec3(120, 0, -20),
        glm::vec3(60, 0, 120),
        glm::vec3(60, 100, 50),
        purple);

    // Rotate slightly so one face points toward the camera
    tetrahedron = make_shared<RotateY>(tetrahedron, 25);

    // Move it beside the cube
    tetrahedron = make_shared<Translate>(tetrahedron, glm::vec3(60, 30, 500));

    world.add(tetrahedron);



    Camera cam;

    cam.aspectRatio = 1.0;
    cam.imageWidth = 200;
    cam.samplesPerPixel = 400;
    cam.maxDepth = 20;
    cam.background = color(0, 0, 0);

    cam.vfov = 70;
    cam.lookFrom = glm::vec3(278, 278, -5);
    cam.lookAt = glm::vec3(278, 278, 0);
    cam.vup = glm::vec3(0, 1, 0);

    cam.defocusAngle = 0;

    cam.render(world);
}
