#pragma once

#include "Hittable.h"
#include "HittableList.h"

class Triangle : public Hittable
{
public:
    Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, shared_ptr<Material> mat);

    void setBoundingBox();

    AABB boundingBox() const override;

    bool hit(const Ray& r, Interval rayT, hitRecord& rec) const override;

    virtual bool isInterior(double u, double v, double w, hitRecord& rec) const;

    static shared_ptr<HittableList> tetrahedron(const glm::vec3& a, const glm::vec3& b,
                                                const glm::vec3& c, const glm::vec3& d,
                                                shared_ptr<Material> mat);

private:
    glm::vec3 a, b, c;
    glm::vec3 edge1, edge2;
    glm::vec3 normal;
    bool degenerate;
    double d00;
    double d01;
    double d11;
    double invDenom;
    double D;
    shared_ptr<Material> mat;
    AABB bBox;
};


