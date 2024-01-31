#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
    enum Direction
    {
        forwards,
        backwards,
        left,
        right,
    };
    glm::mat4 view = glm::mat4(1.0f);
    void moveCamera(Direction dir);
    void updateView();
private:
    const float m_cameraSpeed = 0.05f;
    glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
};
