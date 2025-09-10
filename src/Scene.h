#pragma once
#include <iostream>
#include <glm/glm.hpp>



class Scene
{
public:
	Scene(int width, int height); // Set the resolution

	static glm::vec3 compute_normal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
};

