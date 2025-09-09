#pragma once
#include <iostream>
#include <glm/glm.hpp>

using namespace glm;

class Scene
{
public:
	Scene(int width, int height); // Set the resolution

	static vec3 compute_normal(vec3 v0, vec3 v1, vec3 v2);
};

