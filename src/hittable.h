#pragma once
#include <glm/glm.hpp>
#include "RtWeekend.h"
#include "AABB.h"

class Material;

class hitRecord {
public:
	glm::vec3 p;
	glm::vec3 normal;
	shared_ptr<Material> mat;
	double t;
	bool frontFace;

	double u;
	double v;

	void setFaceNormal(const Ray& r, const glm::vec3& outwardNormal);
};

class Hittable {
public:
	virtual ~Hittable() = default;

	// Different geometry will implement its own def for a hit, therefore pure virtual function
	virtual bool hit(const Ray& r, Interval rayT, hitRecord& rec) const = 0;
	
	virtual AABB boundingBox() const = 0;
};
