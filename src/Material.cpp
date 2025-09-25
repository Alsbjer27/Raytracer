#include "Material.h"

bool Material::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	(void)rIn;
	(void)rec;
	(void)attenuation;
	(void)scattered;

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

Metal::Metal(const color& albedo, float fuzz)
: albedo(albedo), fuzz(fuzz < 1 ? fuzz: 1) {}

bool Metal::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	glm::vec3 reflected = glm::reflect(glm::normalize(rIn.direction()), rec.normal);
	reflected += fuzz * randomUnitVector();
	scattered = Ray(rec.p, reflected);
	attenuation = albedo;
	return (glm::dot(scattered.direction(), rec.normal) > 0);
}

Dielectric::Dielectric(float refractionIndex)
: refractionIndex(refractionIndex) {}

bool Dielectric::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	attenuation = color(1.0f, 1.0f, 1.0f);
	float ri = rec.frontFace ? (1.0f / refractionIndex) : refractionIndex;

	glm::vec3 unitDirection = glm::normalize(rIn.direction());
	glm::vec3 refracted = refract(unitDirection, rec.normal, ri);

	scattered = Ray(rec.p, refracted);

	return true;
}
