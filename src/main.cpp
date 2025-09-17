#include <iostream>
#include <glm/glm.hpp>            // core (vec*, dot, etc.)
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Framebuffer.h"

int main() {
    int width = 200;
    int height = 200;

    Camera cam(width, height);
    Framebuffer fb(width, height);

    // Instead of scene.buildRoom(), just one test triangle
    std::vector<Triangle> tris;
    tris.clear();
    tris.push_back(Triangle(
        { 2, 1, 1 },   // bottom-left
        { 2, 3, 1 },   // top-left
        { 2, 2, 3 },   // right
        { 1.0f, 0.0f, 0.0f } // red
    ));

    // Render loop
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Ray r = cam.generateRay(x, y);

            if (x == width / 2 && y == height / 2) {
                std::cout << "DEBUG: Ray at center pixel\n";
                std::cout << "Origin = ("
                    << r.origin.x << ", " << r.origin.y << ", " << r.origin.z << ")\n";
                std::cout << "Dir    = ("
                    << r.direction.x << ", " << r.direction.y << ", " << r.direction.z << ")\n";
            }

            float nearest_t = std::numeric_limits<float>::max();
            const Triangle* hit = nullptr;

            for (const Triangle& tri : tris) {
                float t;
                if (tri.intersect(r, t)) {
                    if (x == width / 2 && y == height / 2) {
                        std::cout << "DEBUG: Intersection found at t = " << t << "\n";
                    }
                    if (t < nearest_t) {
                        nearest_t = t;
                        hit = &tri;
                    }
                }
            }
            if (hit && x == width / 2 && y == height / 2) {
                std::cout << "DEBUG: Center pixel hit! Color=("
                    << hit->color.r << ","
                    << hit->color.g << ","
                    << hit->color.b << ")\n";
            }

            glm::vec3 color(0.0f); // background
            if (hit) {
                color = hit->color;
            }
            else {
                color = glm::vec3(0.0f); // background
            }
            fb.setPixel(x, y, color);
        }
    }

    fb.savePPM("test_triangle.ppm");
    std::cout << "Wrote test_triangle.ppm\n";
    return 0;
}