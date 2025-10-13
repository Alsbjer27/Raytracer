#include "BVH.h"
#include <algorithm>

bool BVHNode::boxCompare(
	const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axisIndex
) {
	auto aAxisInterval = a->boundingBox().axisInterval(axisIndex);
	auto bAxisInterval = b->boundingBox().axisInterval(axisIndex);
	return aAxisInterval.min < bAxisInterval.min;
}

bool BVHNode::boxXCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
	return boxCompare(a, b, 0);
}

bool BVHNode::boxYCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
	return boxCompare(a, b, 1);
}

bool BVHNode::boxZCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
	return boxCompare(a, b, 2);
}

BVHNode::BVHNode(HittableList list)
: BVHNode(list.objects, 0, list.objects.size()) {}

BVHNode::BVHNode(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end)
{

	bBox = AABB::empty;
	for (size_t objectIndex = start; objectIndex < end; objectIndex++)
		bBox = AABB(bBox, objects[objectIndex]->boundingBox());

	int axis = bBox.longestAxis();

	auto comparator = (axis == 0) ? boxXCompare
					: (axis == 1) ? boxYCompare
							      : boxZCompare;

	size_t objectSpan = end - start;

	if (objectSpan == 1) {
        left = right = objects[start];
    } else if (objectSpan == 2) {
        left = objects[start];
        right = objects[start + 1];
    } else {
        std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

        auto mid = start + objectSpan / 2;
        left = make_shared<BVHNode>(objects, start, mid);
        right = make_shared<BVHNode>(objects, mid, end);
    }
    bBox = AABB(left->boundingBox(), right->boundingBox());  // "Add this line" - cursor
	// the line above is added by cursor, and helps with performance
}

bool BVHNode::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
	if (!bBox.hit(r, rayT)) {
		return false;
	}

	bool hitLeft = left->hit(r, rayT, rec);
	bool hitRight = right->hit(r, Interval(rayT.min, hitLeft ? rec.t : rayT.max), rec);

	return hitLeft || hitRight;
}

AABB BVHNode::boundingBox() const
{
	return bBox;
}
