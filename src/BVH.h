#pragma once
#include "AABB.h"
#include "hittable.h"
#include "HittableList.h"

class BVHNode : public Hittable
{
public:
	BVHNode(HittableList list);

	BVHNode(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end);

	bool hit(const Ray& r, Interval rayT, hitRecord& rec) const override;

	AABB boundingBox() const override;
private:
	shared_ptr<Hittable> left;
	shared_ptr<Hittable> right;
	AABB bBox;

};

