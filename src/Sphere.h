#pragma once
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(const glm::vec3& center, double radius, shared_ptr<Material> mat);

	bool hit(const Ray& r, Interval rayT, hitRecord& rec) const override;

	AABB boundingBox() const override { return bBox; }

private:
	glm::vec3 center;
	double radius;
	shared_ptr<Material> mat;
	AABB bBox;
};

