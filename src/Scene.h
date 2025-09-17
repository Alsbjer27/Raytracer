#pragma once
#include <iostream>
#include<vector>
#include <glm/glm.hpp>
#include "Triangle.h"



class Scene
{
public:
	Scene(); // Set the resolution

	void buildRoom();

	const std::vector<Triangle>& getTriangle() const { return triangles; }


private: 
	std::vector<Triangle> triangles;
};

