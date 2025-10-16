#pragma once
#include "hittable.h"
#include "HittableList.h"

class Quad : public Hittable
{
public:
	Quad(const glm::vec3& Q, const glm::vec3& u, const glm::vec3& v, shared_ptr<Material> mat);

	virtual void setBoundingBox();

	AABB boundingBox() const override;

	bool hit(const Ray& r, Interval rayT, hitRecord& rec) const override;

	virtual bool isInterior(double a, double b, hitRecord& rec) const;

	static shared_ptr<HittableList> box(const glm::vec3& a, const glm::vec3& b, shared_ptr<Material> mat);

private:
	glm::vec3 Q;
	glm::vec3 u, v;
	glm::vec3 w;
	shared_ptr<Material> mat;
	AABB bBox;
	glm::vec3 normal;
	double D;
};

