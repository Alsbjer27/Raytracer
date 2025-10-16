#include "Hittable.h"

void hitRecord::setFaceNormal(const Ray& r, const glm::vec3& outwardNormal)
{
	frontFace = glm::dot(r.dir, outwardNormal) < 0;
	if (frontFace) {
		normal = outwardNormal;
	}
	else {
		normal = -outwardNormal;
	}
}

Translate::Translate(shared_ptr<Hittable> object, const glm::vec3& offset)
: object(object), offset(offset) 
{
	bBox = object->boundingBox() + offset;
}

bool Translate::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
	Ray offsetR(r.origin() - offset, r.direction(), r.time());

	if (!object->hit(offsetR, rayT, rec)) {
		return false;
	}

	rec.p += offset;
	return true;
}

AABB Translate::boundingBox() const
{
	return bBox;;
}
