#include "RtWeekend.h"
#include "BVH.h"
#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>



int main() {

    HittableList world;

    auto materialGround = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, materialGround));

    for (int a = -1; a < 11; a++) {
        for (int b = -1; b < 11; b++) {
            auto chooseMat = randomDouble();
            glm::vec3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    auto albedo = randomVec3() * randomVec3();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    auto center2 = center + glm::vec3(0, randomDouble(0, 0.5), 0);
                    world.add(make_shared<Sphere>(center, center2,0.2, sphereMaterial));
                }
                else if(chooseMat < 0.95){
                    auto albedo = randomVec3(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else {
                    sphereMaterial = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }




    auto material1 = make_shared<Dielectric>(1.50);
    auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);


    world.add(make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, material1));
    world.add(make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, material2));
    world.add(make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, material3));

    world = HittableList(make_shared<BVHNode>(world));

    Camera cam;
    
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 50;
    cam.maxDepth = 10;

    cam.vfov = 20;
    cam.lookFrom = glm::vec3(13, 2, 3);
    cam.lookAt = glm::vec3(0, 0, 0);
    cam.vup = glm::vec3(0, 1, 0);

    cam.defocusAngle = 0.6;
    cam.focusDistance = 10.0;

    cam.render(world);
}
