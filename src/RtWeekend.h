#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <random>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// C++ std Using

using std::make_shared;
using std::shared_ptr;

// Constants 

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double degreesToRadians(double degrees) {
	return degrees * pi / 180;
}

inline double randomDouble() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double randomDouble(double min, double max) {
	return min + (max - min) * randomDouble();
}

// Utility functions for GLM

inline glm::vec3 randomVec3() {
	return glm::vec3(randomDouble(), randomDouble(), randomDouble());
}

inline glm::vec3 randomVec3(double min, double max) {
	return glm::vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline glm::vec3 randomUnitVector() {
	while (true) {
		auto p = randomVec3(-1, 1);
		auto lenSqrt = glm::length2(p);
		if (1e-160 < lenSqrt && lenSqrt <= 1) {
			return p / sqrt(lenSqrt);
		}
	}
}

inline glm::vec3 randomOnHemisphere(const glm::vec3& normal) {
	glm::vec3 onUnitSphere = randomUnitVector();
	if (glm::dot(onUnitSphere, normal) > 0.0) {
		return onUnitSphere;
	}
	else
	{
		return -onUnitSphere;
	}
}

inline bool nearZero(const glm::vec3 v) {
	const auto s = 1e-8f;
	return (std::fabs(v.x) < s) &&
		(std::fabs(v.y) < s) &&
		(std::fabs(v.z) < s);
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
	return v - 2 * glm::dot(v, n) * n;
}

// Utility functions for GLM Refraction

inline glm::vec3 refract(const glm::vec3& uv, const glm::vec3& n, float etaiOverEtat) {
	auto cosTheta = std::fmin(glm::dot(-uv, n), 1.0f);
	glm::vec3 refOutPerp = etaiOverEtat * (uv + cosTheta * n);
	glm::vec3 refOutPara = -std::sqrt(std::fabs(1.0f - glm::length2(refOutPerp))) * n;
	return refOutPerp + refOutPara;
}

// Common headers
#include "Color.h"
#include "Ray.h"
#include "Interval.h"

