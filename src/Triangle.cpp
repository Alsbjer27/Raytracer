#include "Triangle.h"

Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& color)
: v0(v0), v1(v1), v2(v2), color(color) 
{
	normal = glm::normalize(cross(v1 - v0, v2 - v0));
}

bool Triangle::intersect(const Ray& ray, float& t)
{
	constexpr float EPS = 1e-8; // To compare to

	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;

	glm::vec3 perpendicualarVec = glm::cross(edge1, edge2);
	float det = glm::dot(edge1, perpendicualarVec);

	if (fabs(det) < EPS) return false;
	float invDet = 1.0f / det;

	glm::vec3 triangleVec = ray.origin - v0;
	float u = glm::dot(triangleVec, perpendicualarVec) * invDet;
	if (u < 0.0f || u > 1.0f) return false;

	glm::vec3 qvec = glm::cross(triangleVec, edge1);
	float v = glm::dot(ray.direction, qvec) * invDet;
	if (v < 0.0f || u + v > 1.0f) return false;

	t = glm::dot(edge2, qvec) * invDet;

	return t > EPS;
}
