#pragma once
#include "Ray.h"
#include "Hittable.h"

class Sphere : public hittable
{
public:
	Sphere(const glm::vec3& center, double radius);

	bool hit(const Ray& r, double rayTMin, double rayTMax, hitRecord& rec) const override;

private:
	glm::vec3 center;
	double radius;
};

