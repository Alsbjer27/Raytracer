#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <iostream>


class Camera
{
public:
	Camera(int width, int height);

	Ray generateRay(int x, int y) const;

private:

	glm::vec3 origin;

	glm::vec3 lowerLeft, lowerRight, upperLeft, upperRight;

	int width, height;

	glm::vec3 horizontal;
	glm::vec3 vertical;
};

