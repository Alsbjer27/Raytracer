#include "Scene.h"


Scene::Scene(int width, int height)
{

}

vec3 Scene::compute_normal(vec3 v0, vec3 v1, vec3 v2)
{
    vec3 edge1 = v0 - v1;
    vec3 edge2 = v2 - v0;
    vec3 normal = cross(edge1, edge2);
    
    return normalize(normal);
}
