#pragma once
#include "Color.h"

inline double linearToGamma(double linearComponent) {
	if (linearComponent > 0) {
		return std::sqrt(linearComponent);
	}
	return 0;
}

void writeColor(std::ostream& out, const color& pixelColor)
{
	auto r = pixelColor.x;
	auto g = pixelColor.y;
	auto b = pixelColor.z;

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	static const Interval intensity(0.000, 0.999);

	int rByte = int(255 * intensity.clamp(r));
	int gByte = int(255 * intensity.clamp(g));
	int bByte = int(255 * intensity.clamp(b));

	out << rByte << " " << gByte << " " << bByte << "\n";
}
