#include "HittableList.h"

HittableList::HittableList()
{}

HittableList::HittableList(shared_ptr<Hittable> object)
{
	add(object);
}

void HittableList::clear() {
	objects.clear();
}

void HittableList::add(shared_ptr<Hittable> object)
{
	objects.push_back(object);
	bBox = AABB(bBox, object->boundingBox());
}

bool HittableList::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
	hitRecord tempRec;
	bool hitAnything = false;
	auto closestSoFar = rayT.max;

	for (const auto& object : objects) {
		if (object->hit(r, Interval(rayT.min, closestSoFar), tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

AABB HittableList::boundingBox() const
{
	return bBox;
}
