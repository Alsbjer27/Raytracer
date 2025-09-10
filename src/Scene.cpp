#include "Scene.h"


//Scene::Scene(int width, int height)
//{
//
//}

glm::vec3 Scene::compute_normal(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
{
    glm::vec3 edge1 = v0 - v1;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 normal = cross(edge1, edge2);
    
    return glm::normalize(normal);
}
