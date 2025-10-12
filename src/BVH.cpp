#include "BVH.h"

BVHNode::BVHNode(HittableList list)
: BVHNode(list.objects, 0, list.objects.size()) {}

BVHNode::BVHNode(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end)
{
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
