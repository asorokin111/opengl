#pragma once
#include <glm/glm.hpp>
struct SpotLight
{
    glm::vec3 position;
    glm::vec3 direction;
    float cutoff;
    float outerCutoff;
    float constant;
    float linear;
    float quadratic;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
