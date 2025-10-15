#include "Quad.h"

Quad::Quad(const glm::vec3& Q, const glm::vec3& u, const glm::vec3& v, shared_ptr<Material> mat)
: Q(Q), u(u), v(v), mat(mat) 
{
	auto n = glm::cross(u, v);
	normal = glm::normalize(n);
	D = glm::dot(normal, Q);
	w = n / glm::dot(n, n);

	setBoundingBox();
}

void Quad::setBoundingBox()
{
	auto bBoxDiagonal1 = AABB(Q, Q + u + v);
	auto bBoxDiagonal2 = AABB(Q + u, Q + v);
	bBox = AABB(bBoxDiagonal1, bBoxDiagonal2);

}

AABB Quad::boundingBox() const
{
	return bBox;
}

bool Quad::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
	auto denom = glm::dot(normal, r.direction());

	if (std::fabs(denom) < 1e-8) {
		return false;
	}
	
	auto t = (D - glm::dot(normal, r.origin())) / denom;

	if (!rayT.contains(t)) {
		return false;
	}

	auto intersection = r.at(t);
	glm::vec3 planarHitPtVector = intersection - Q;
	auto alpha = glm::dot(w, glm::cross(planarHitPtVector, v));
	auto beta = glm::dot(w, glm::cross(u, planarHitPtVector));

	if (!isInterior(alpha, beta, rec)) {
		return false;
	}


	rec.t = t;
	rec.p = intersection;
	rec.mat = mat;
	rec.setFaceNormal(r, normal);

	return true;
}

bool Quad::isInterior(double a, double b, hitRecord& rec) const
{
	Interval unitInterval = Interval(0, 1);

	if (!unitInterval.contains(a) || !unitInterval.contains(b)) {
		return false;
	}

	rec.u = a;
	rec.v = b;

	return true;
}
