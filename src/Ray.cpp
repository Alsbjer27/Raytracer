#include "Ray.h"

Ray::Ray()
	: ori(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, -1.0f) {
}


Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
: ori(origin), dir(direction) {}

const glm::vec3& Ray::origin() const
{
	return ori;
}

const glm::vec3& Ray::direction() const
{
	return dir;
}

glm::vec3 Ray::at(float t) const
{
	return ori + dir * t;
}
