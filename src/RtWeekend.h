#pragma once
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

// Common headers
#include "Color.h"
#include "Ray.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include "Interval.h"

