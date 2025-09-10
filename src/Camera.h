#pragma once
#include <glm/glm.hpp>
#include <iostream>


class Camera
{
public:
	Camera(int width, int height);

	glm::vec3 origin;
	glm::vec3 direction;

	glm::vec3 lowerLeft, lowerRight, upperLeft, upperRight;

	int width, height;
	double pixelSize;

};

