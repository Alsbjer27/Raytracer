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

shared_ptr<HittableList> Quad::box(const glm::vec3& a, const glm::vec3& b, shared_ptr<Material> mat)
{
	auto sides = make_shared<HittableList>();

	auto min = glm::vec3(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
	auto max = glm::vec3(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));

	auto dx = glm::vec3(max.x - min.x, 0, 0);
	auto dy = glm::vec3(0, max.y - min.y, 0);
	auto dz = glm::vec3(0, 0, max.z - min.z);

	sides->add(make_shared<Quad>(glm::vec3(min.x, min.y, max.z), dx, dy, mat)); // front
	sides->add(make_shared<Quad>(glm::vec3(max.x, min.y, max.z), -dz, dy, mat)); // right
	sides->add(make_shared<Quad>(glm::vec3(max.x, min.y, min.z), -dx, dy, mat)); // back
	sides->add(make_shared<Quad>(glm::vec3(min.x, min.y, min.z), dz, dy, mat)); // left
	sides->add(make_shared<Quad>(glm::vec3(min.x, max.y, max.z), dx, -dz, mat)); // top
	sides->add(make_shared<Quad>(glm::vec3(min.x, min.y, min.z), dx, dz, mat)); // bottom

	return sides;
}
