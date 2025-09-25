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
