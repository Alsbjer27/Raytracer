#pragma once
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(const glm::vec3& center, double radius, shared_ptr<Material> mat);

	bool hit(const Ray& r, Interval rayT, hitRecord& rec) const override;

private:
	glm::vec3 center;
	double radius;
	shared_ptr<Material> mat;
};

