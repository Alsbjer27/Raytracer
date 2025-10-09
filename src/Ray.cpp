#include "Ray.h"

Ray::Ray()
	: ori(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, -1.0f) {
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction, double time)
 : ori(origin), dir(direction), tm(time) {}


Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
: Ray(origin, direction, 0) {}

const glm::vec3& Ray::origin() const
{
	return ori;
}

const glm::vec3& Ray::direction() const
{
	return dir;
}

double Ray::time() const
{
	return tm;
}

glm::vec3 Ray::at(float t) const
{
	return ori + dir * t;
}
