#include "Sphere.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

Sphere::Sphere(const glm::vec3& staticCenter, double radius, shared_ptr<Material> mat)
    : center(staticCenter, glm::vec3(0,0,0)), radius(std::fmax(0, radius)), mat(mat) 
{
    auto rvec = glm::vec3(radius, radius, radius);
    bBox = AABB(staticCenter - rvec, staticCenter + rvec);
}

Sphere::Sphere(const glm::vec3& center1, const glm::vec3& center2, double radius, shared_ptr<Material> mat)
: center(center1, center2 - center1), radius(std::fmax(0, radius)), mat(mat) 
{
    auto rvec = glm::vec3(radius, radius, radius);
    AABB box1(center.at(0) - rvec, center.at(0) + rvec);
    AABB box2(center.at(1) - rvec, center.at(1) + rvec);
    bBox = AABB(box1, box2);
}


bool Sphere::hit(const Ray& r, Interval rayT, hitRecord& rec) const
{
    glm::vec3 currentCenter = center.at(r.time());
    glm::vec3 oc = currentCenter - r.origin();
    auto a = glm::length2(r.dir);
    auto h = glm::dot(r.dir, oc);
    auto c = glm::length2(oc) - radius * radius;
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
    glm::vec3 outwardNormal = (rec.p - currentCenter) / static_cast<float>(radius);
    rec.setFaceNormal(r, outwardNormal);
    rec.mat = mat;
    return true;
}

AABB Sphere::boundingBox() const
{
    return bBox;
}
