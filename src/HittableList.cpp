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
}

bool HittableList::hit(const Ray& r, double rayTMin, double rayTMax, hitRecord& rec) const
{
	hitRecord tempRec;
	bool hitAnything = false;
	auto closestSoFar = rayTMax;

	for (const auto& object : objects) {
		if (object->hit(r, rayTMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}
