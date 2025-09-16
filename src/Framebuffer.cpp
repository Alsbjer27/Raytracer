#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height)
: width(width), height(height), pixels(width*height, glm::vec3(0.0f)) {}

void Framebuffer::setPixel(int x, int y, const glm::vec3& color)
{
	pixels[y * width + x] = color;
}

void Framebuffer::savePPM(const std::string& filename) const
{
	std::ofstream out(filename);
	out << "P3\n" << width << " " << height << "\n255\n";
	for (const auto& c : pixels) {
		int r = static_cast<int>(255.99f * std::clamp(c.r, 0.0f, 1.0f));
		int g = static_cast<int>(255.99f * std::clamp(c.g, 0.0f, 1.0f));
		int b = static_cast<int>(255.99f * std::clamp(c.b, 0.0f, 1.0f));
		out << r << " " << g << " " << b << "\n";
	}
}
