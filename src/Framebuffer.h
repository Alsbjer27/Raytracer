#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <fstream>
#include <algorithm>


class Framebuffer
{
public:
	Framebuffer(int width, int height);

	void setPixel(int x, int y, const glm::vec3& color);

	void savePPM(const std::string& filename) const;

private:
	int width, height;
	std::vector<glm::vec3> pixels;
};

