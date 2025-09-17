#include "Scene.h"


Scene::Scene() {}

void Scene::buildRoom()
{
	triangles.clear();

    // floor (grey)
    triangles.push_back(Triangle({ 0,0,0 }, { 4,4,0 }, { 4,0,0 }, { 0.8f,0.8f,0.8f }));
    triangles.push_back(Triangle({ 0,0,0 }, { 0,4,0 }, { 4,4,0 }, { 0.8f,0.8f,0.8f }));

    // ceiling (white)
    triangles.push_back(Triangle({ 0,0,4 }, { 4,4,4 }, { 0,4,4 }, { 0.9f,0.9f,0.9f }));
    triangles.push_back(Triangle({ 0,0,4 }, { 4,0,4 }, { 4,4,4 }, { 0.9f,0.9f,0.9f }));

    // left wall (red)
    triangles.push_back(Triangle({ 0,0,0 }, { 0,4,4 }, { 0,4,0 }, { 1.0f,0.0f,0.0f }));
    triangles.push_back(Triangle({ 0,0,0 }, { 0,0,4 }, { 0,4,4 }, { 1.0f,0.0f,0.0f }));

    // right wall (green)
    triangles.push_back(Triangle({ 4,0,0 }, { 4,4,4 }, { 4,0,4 }, { 0.0f,1.0f,0.0f }));
    triangles.push_back(Triangle({ 4,0,0 }, { 4,4,0 }, { 4,4,4 }, { 0.0f,1.0f,0.0f }));

    // back wall (blue)
    triangles.push_back(Triangle({ 0,0,0 }, { 4,0,4 }, { 0,0,4 }, { 0.0f,0.0f,1.0f }));
    triangles.push_back(Triangle({ 0,0,0 }, { 4,0,0 }, { 4,0,4 }, { 0.0f,0.0f,1.0f }));

    // front wall (yellow)
    triangles.push_back(Triangle({ 0,4,0 }, { 4,4,4 }, { 4,4,0 }, { 1.0f,1.0f,0.0f }));
    triangles.push_back(Triangle({ 0,4,0 }, { 4,4,4 }, { 0,4,4 }, { 1.0f,1.0f,0.0f }));
}

