#pragma once
#include <glm/glm.hpp>
#include "RtWeekend.h"

class hitRecord {
public:
	glm::vec3 p;
	glm::vec3 normal;
	double t;
	bool frontFace;

	void setFaceNormal(const Ray& r, const glm::vec3& outwardNormal);
};

class Hittable {
public:
	virtual ~Hittable() = default;

	// Different geometry will implement its own def for a hit, therefore pure virtual function
	virtual bool hit(const Ray& r, double rayTMin, double rayTMax, hitRecord& rec) const = 0;

};