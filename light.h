#pragma once
#include <glm/glm.hpp>
struct Light
{
    float cutoff;
    float outerCutoff;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
