#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;


class HittableList : public Hittable
{
public:
	std::vector<shared_ptr<Hittable>> objects;

	HittableList();
	HittableList(shared_ptr<Hittable> object);

	void clear();
	void add(shared_ptr<Hittable> object);

	bool hit(const Ray& r, double rayTMin, double rayTMax, hitRecord& rec) const override;

};

