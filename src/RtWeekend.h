#pragma once
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

// Common headers
#include "Color.h"
#include "Ray.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include "Interval.h"

