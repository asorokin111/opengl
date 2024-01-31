#include "camera.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera::moveCamera(Direction dir, float deltaTime)
{
    const float speed = m_cameraSpeed * deltaTime;
    switch (dir)
    {
    case forwards:
        m_cameraPos += speed * m_cameraFront;
        break;
    case backwards:
        m_cameraPos -= speed * m_cameraFront;
        break;
    case left:
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
        break;
    case right:
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
        break;
    }
}

void Camera::updateView()
{
    view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::updateDirection(float pitch, float yaw)
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_cameraFront = glm::normalize(direction);
}
