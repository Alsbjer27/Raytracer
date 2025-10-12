#pragma once
#include "RtWeekend.h"

class AABB
{
public:
	Interval x, y, z;

	AABB();

	AABB(const Interval& x, const Interval& y, const Interval& z);

	AABB(const glm::vec3& a, const glm::vec3& b);

	AABB(const AABB& box0, const AABB& box1);

	const Interval& axisInterval(int n) const;

	bool hit(const Ray& r, Interval rayT) const;

};

