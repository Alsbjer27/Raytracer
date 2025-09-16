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


	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Ray r = cam.generateRay(x, y);
			//std::cout << "pixel (" << x << "," << y << "): direction = (" << r.direction.x << ", " << r.direction.y << ", " << r.direction.z << ")\n";

			glm::vec3 color = 0.5f * (r.direction + glm::vec3(1.0f));
			fb.setPixel(x, y, color);
		}
	}
	fb.savePPM("output.ppm");
	return 0;
}
