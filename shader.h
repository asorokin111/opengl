#pragma once
#include "material.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setMat3(const std::string& name, const glm::mat3& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMaterial(const std::string& name, const Material& mat) const;
    void setMaterial(const Material& mat) const;
    void use() const;
    void del() const;
};
