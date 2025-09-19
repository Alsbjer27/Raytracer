#pragma once
#include "Ray.h"

class hitRecord {
public:
	glm::vec3 p;
	glm::vec3 normal;
	double t;
};

class hittable {
public:
	virtual ~hittable() = default;

	// Different geometry will implement its own def for a hit
	virtual bool hit(const Ray& r, double rayTMin, double rayTMax, hitRecord& rec) const = 0;
};