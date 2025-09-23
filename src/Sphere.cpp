#include "Sphere.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

Sphere::Sphere(const glm::vec3& center, double radius)
    : center(center), radius(std::fmax(0,radius)) {
}

bool Sphere::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
    glm::vec3 originToSphereCenter = center - r.ori;
    auto a = glm::length2(r.dir);
    auto h = glm::dot(r.dir, originToSphereCenter);
    auto c = glm::length2(originToSphereCenter) - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return false;
    }
    auto sqrtd = std::sqrt(discriminant);


    auto root = (h - sqrtd) / a;
    if (!rayT.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!rayT.surrounds(root)) {
            return false;
        }  
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outwardNormal = (rec.p - center) / static_cast<float>(radius);
    rec.setFaceNormal(r, outwardNormal);
    return true;
}
