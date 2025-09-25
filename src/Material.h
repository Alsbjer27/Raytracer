#pragma once
#include "Hittable.h"

class Material
{
public:
	virtual ~Material() = default;
	virtual bool scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const;
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
	Metal(const color& albedo);

	bool scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const override;

private:
	color albedo;
};

