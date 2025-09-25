#include "Material.h"

bool Material::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	return false;
}

Lambertian::Lambertian(const color& albedo)
 : albedo(albedo) {}

bool Lambertian::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	auto scatterDirection = rec.normal + randomUnitVector();

	if (nearZero(scatterDirection)) {
		scatterDirection = rec.normal;
	}

	scattered = Ray(rec.p, scatterDirection);
	attenuation = albedo;
	return true;
}

Metal::Metal(const color& albedo)
: albedo(albedo) {}

bool Metal::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	glm::vec3 reflected = reflect(rIn.direction(), rec.normal);
	scattered = Ray(rec.p, reflected);
	attenuation = albedo;
	return true;
}
