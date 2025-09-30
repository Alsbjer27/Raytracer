#pragma once
#include "Hittable.h"
#include "AABB.h"

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

	AABB boundingBox() const override { return bBox; }
private:
	AABB bBox;
};

