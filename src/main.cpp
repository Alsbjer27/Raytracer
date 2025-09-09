#include <iostream>
#include <glm/glm.hpp>            // core (vec*, dot, etc.)
// #include <glm/gtx/norm.hpp>    // <-- remove this (experimental)
#include "Scene.h"

int main() {
    vec3 v0(0, 3, 2);
    vec3 v1(2, 3, 2);
    vec3 v2(4, 5, 1);

    vec3 normal = Scene::compute_normal(v0, v1, v2);

    std::cout << "Normal: ("
        << normal.x << ", "
        << normal.y << ", "
        << normal.z << ")\n";

    std::cout << "Length: " << length(normal) << "\n";
}
