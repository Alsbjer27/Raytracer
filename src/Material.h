#pragma once
#include "Hittable.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

class Material
{
public:
	virtual ~Material() = default;
	virtual bool scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const;
	virtual color emitted(double u, double v, const glm::vec3& p) const;
};

class Lambertian : public Material {
public:
	Lambertian(const color& albedo);

	bool scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const override;

private:
	color albedo;
};

class Metal : public Material {
public:
	Metal(const color& albedo, float fuzz);

	bool scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const override;

private:
	color albedo;
	float fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(float refractionIndex);

	bool scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const override;

private:
	float refractionIndex;
    static double reflectance(double cosine, double refractionIndex);
};

class DiffuseLight : public Material {
public:
	color emitColor;

	DiffuseLight(const color& emit);

	color emitted(double u, double v, const glm::vec3& p) const override;

};
