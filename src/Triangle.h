#pragma once
#include <glm/glm.hpp>
#include "Ray.h"


class Triangle
{
public:
	Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& color);

	bool intersect(const Ray& ray, float& t);

	glm::vec3 v0, v1, v2;
	glm::vec3 color;
	glm::vec3 normal;
};

