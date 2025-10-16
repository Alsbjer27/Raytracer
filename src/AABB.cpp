#include "AABB.h"

AABB::AABB() {}

AABB::AABB(const Interval& x, const Interval& y, const Interval& z)
: x(x), y(y), z(z) {}

AABB::AABB(const glm::vec3& a, const glm::vec3& b)
{
	x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
	y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
	z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);
}

AABB::AABB(const AABB& box0, const AABB& box1)
{
	x = Interval(box0.x, box1.x);
	y = Interval(box0.y, box1.y);
	z = Interval(box0.z, box1.z);
}

const Interval& AABB::axisInterval(int n) const
{
	if (n == 1) return y;
	if (n == 2) return z;
	return x;
}

bool AABB::hit(const Ray& r, Interval& rayT) const //the & is from cursor, helps with performance
{
	const glm::vec3& rayOrigin = r.origin();
	const glm::vec3& rayDirection = r.direction();

	for (int axis = 0; axis < 3; axis++) {
		const Interval& ax = axisInterval(axis);
		const double adinv = 1.0 / rayDirection[axis];

		auto t0 = (ax.min - rayOrigin[axis]) * adinv;
		auto t1 = (ax.max - rayOrigin[axis]) * adinv;

		if (t0 < t1) {
			if (t0 > rayT.min) {
				rayT.min = t0;
			}
			if (t1 < rayT.max) {
				rayT.max = t1;
			}
		}
		else {
			if (t1 > rayT.min) {
				rayT.min = t1;
			}
			if (t0 < rayT.max) {
				rayT.max = t0;
			}
		}
		if (rayT.max <= rayT.min) {
			return false;
		}
	}
	return true;
}

int AABB::longestAxis() const
{
	// Returns the index of the longest axis of the bounding box.
	if (x.size() > y.size())
		return x.size() > z.size() ? 0 : 2;
	else
		return y.size() > z.size() ? 1 : 2;
}

void AABB::padToMinimums()
{
	double delta = 0.0001;
	if (x.size() < delta) x = x.expand(delta);
	if (y.size() < delta) y = y.expand(delta);
	if (z.size() < delta) z = z.expand(delta);

}

const AABB AABB::empty = AABB(Interval::empty, Interval::empty, Interval::empty);
const AABB AABB::universe = AABB(Interval::universe, Interval::universe, Interval::universe);

AABB operator+(const AABB& bBox, const glm::vec3& offset)
{
	return AABB(bBox.x + offset.x, bBox.y + offset.y, bBox.z + offset.z);
}

AABB operator+(const glm::vec3& offset, const AABB& bBox)
{
	return bBox + offset;
}
