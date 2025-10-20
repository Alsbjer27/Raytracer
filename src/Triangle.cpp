#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, shared_ptr<Material> mat)
: a(a), b(b), c(c), mat(mat)
{
    edge1 = b - a;
    edge2 = c - a;
    auto crossProduct = glm::cross(edge1, edge2);
    auto normSquared = glm::dot(crossProduct, crossProduct);
    degenerate = normSquared < 1e-12;

    if (!degenerate) {
        normal = glm::normalize(crossProduct);
        D = glm::dot(normal, a);
        d00 = glm::dot(edge1, edge1);
        d01 = glm::dot(edge1, edge2);
        d11 = glm::dot(edge2, edge2);
        invDenom = 1.0 / (d00 * d11 - d01 * d01);
    } else {
        normal = glm::vec3(0, 0, 0);
        D = 0.0;
        d00 = d01 = d11 = invDenom = 0.0;
    }

    setBoundingBox();
}

void Triangle::setBoundingBox()
{
    glm::vec3 minPoint(
        std::fmin(std::fmin(a.x, b.x), c.x),
        std::fmin(std::fmin(a.y, b.y), c.y),
        std::fmin(std::fmin(a.z, b.z), c.z));

    glm::vec3 maxPoint(
        std::fmax(std::fmax(a.x, b.x), c.x),
        std::fmax(std::fmax(a.y, b.y), c.y),
        std::fmax(std::fmax(a.z, b.z), c.z));

    const double delta = 1e-4;
    for (int axis = 0; axis < 3; ++axis) {
        if (maxPoint[axis] - minPoint[axis] < delta) {
            minPoint[axis] -= delta * 0.5;
            maxPoint[axis] += delta * 0.5;
        }
    }

    bBox = AABB(minPoint, maxPoint);
}

AABB Triangle::boundingBox() const
{
    return bBox;
}

bool Triangle::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
    if (degenerate) {
        return false;
    }

    const glm::vec3& rayOrigin = r.origin();
    const glm::vec3& rayDir = r.direction();
    double denom = glm::dot(normal, rayDir);

    if (std::fabs(denom) < 1e-8) {
        return false;
    }

    double t = (D - glm::dot(normal, rayOrigin)) / denom;

    if (!rayT.contains(t)) {
        return false;
    }

    glm::vec3 intersection = r.at(t);
    glm::vec3 planar = intersection - a;

    double d20 = glm::dot(planar, edge1);
    double d21 = glm::dot(planar, edge2);

    double v = (d11 * d20 - d01 * d21) * invDenom;
    double w = (d00 * d21 - d01 * d20) * invDenom;
    double u = 1.0 - v - w;

    if (!isInterior(u, v, w, rec)) {
        return false;
    }

    rec.t = t;
    rec.p = intersection;
    rec.mat = mat;
    rec.setFaceNormal(r, normal);

    return true;
}

bool Triangle::isInterior(double u, double v, double w, hitRecord& rec) const
{
    const double tolerance = 1e-8;

    if (u < -tolerance || v < -tolerance || w < -tolerance) {
        return false;
    }

    if (u > 1.0 + tolerance || v > 1.0 + tolerance || w > 1.0 + tolerance) {
        return false;
    }

    if (std::fabs(u + v + w - 1.0) > tolerance) {
        return false;
    }

    rec.u = v;
    rec.v = w;

    return true;
}

shared_ptr<HittableList> Triangle::tetrahedron(const glm::vec3& a, const glm::vec3& b,
                                               const glm::vec3& c, const glm::vec3& d,
                                               shared_ptr<Material> mat)
{
    auto faces = make_shared<HittableList>();

    faces->add(make_shared<Triangle>(a, b, c, mat));
    faces->add(make_shared<Triangle>(a, c, d, mat));
    faces->add(make_shared<Triangle>(a, d, b, mat));
    faces->add(make_shared<Triangle>(b, d, c, mat));

    return faces;
}


