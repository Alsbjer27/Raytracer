#include "Hittable.h"

void hitRecord::setFaceNormal(const Ray& r, const glm::vec3& outwardNormal)
{
	frontFace = glm::dot(r.dir, outwardNormal);
	if (frontFace) {
		normal = outwardNormal;
	}
	else {
		normal = -outwardNormal;
	}
}
