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

RotateY::RotateY(shared_ptr<Hittable> object, double angle)
: object(object) 
{
	auto radians = degreesToRadians(angle);
	sinTheta = std::sin(radians);
	cosTheta = std::cos(radians);

	bBox = object->boundingBox();

	glm::vec3 min(infinity, infinity, infinity);
	glm::vec3 max(-infinity, -infinity, -infinity);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				auto x = i * bBox.x.max + (1 - i) * bBox.x.min;
				auto y = j * bBox.y.max + (1 - j) * bBox.y.min;
				auto z = k * bBox.z.max + (1 - k) * bBox.z.min;

				auto newX = cosTheta * x + sinTheta * z;
				auto newZ = -sinTheta * x + cosTheta * z;

				glm::vec3 tester(newX, y, newZ);

				for (int c = 0; c < 3; c++) {
					min[c] = std::fmin(min[c], tester[c]);
					max[c] = std::fmax(max[c], tester[c]);
				}
			}
		}
	}
	bBox = AABB(min, max);
}

bool RotateY::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
	auto origin = glm::vec3((cosTheta * r.origin().x) - (sinTheta * r.origin().z), r.origin().y,
		(sinTheta * r.origin().x) + (cosTheta * r.origin().z));

	auto direction = glm::vec3((cosTheta * r.direction().x) - (sinTheta * r.direction().z),
		r.direction().y,
		(sinTheta * r.direction().x) + (cosTheta * r.direction().z));

	Ray rotatedR(origin, direction, r.time());

	if (!object->hit(rotatedR, rayT, rec)) {
		return false;
	}

	rec.p = glm::vec3((cosTheta * rec.p.x) + (sinTheta * rec.p.z),
		rec.p.y,
		(-sinTheta * rec.p.x) + (cosTheta * rec.p.z));

	rec.normal = glm::vec3((cosTheta * rec.normal.x) + (sinTheta * rec.normal.z),
		rec.normal.y,
		(-sinTheta * rec.normal.x) + (cosTheta * rec.normal.z));

	return true;
}

AABB RotateY::boundingBox() const
{
	return bBox;
}
