#pragma once
#include "AABB.h"
#include "Hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
	std::vector<shared_ptr<Hittable>> objects;

	HittableList();
	HittableList(shared_ptr<Hittable> object);

	void clear();
	void add(shared_ptr<Hittable> object);

	bool hit(const Ray& r, Interval rayT, hitRecord& rec) const override;

	AABB boundingBox() const override;

private:
	AABB bBox;

};

