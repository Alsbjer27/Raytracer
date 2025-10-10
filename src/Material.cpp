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

	scattered = Ray(rec.p, scatterDirection, rIn.time());
	attenuation = albedo;
	return true;
}

Metal::Metal(const color& albedo, float fuzz)
: albedo(albedo), fuzz(fuzz < 1 ? fuzz: 1) {}

bool Metal::scatter(const Ray& rIn, const hitRecord& rec, color& attenuation, Ray& scattered) const
{
	glm::vec3 reflected = glm::reflect(glm::normalize(rIn.direction()), rec.normal);
	reflected += fuzz * randomUnitVector();
	scattered = Ray(rec.p, reflected, rIn.time());
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
    double cosTheta = std::fmin(dot(-unitDirection, rec.normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);
    
    bool cannotRefract = ri * sinTheta > 1.0;
    glm::vec3 direction;
    
    if (cannotRefract || reflectance(cosTheta, ri) > randomDouble()) {
        direction = glm::reflect(unitDirection, rec.normal);
    } else {
        direction = glm::refract(unitDirection, rec.normal, ri);
    }
    
    scattered = Ray(rec.p, direction, rIn.time());
	return true;
}

double Dielectric::reflectance(double cosine, double refractionIndex) {
    auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
    r0 = r0*r0;
    return r0 + (1-r0)*std::pow((1-cosine), 5);
}
