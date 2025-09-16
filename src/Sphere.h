#pragma once
#include <glm/glm.hpp>

class Sphere
{
public:
	Sphere(const glm::vec3& center, float radius);

	glm::vec3 center;
	float radius;
};

