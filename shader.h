#pragma once
#include "light.h"
#include "material.h"
#include "textured_material.h"
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
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setMaterial(const std::string& name, const Material& mat) const;
    void setMaterial(const Material& mat) const;
    void setMaterial(const std::string& name, const TexturedMaterial& mat) const;
    void setMaterial(const TexturedMaterial& mat) const;
    void setLight(const std::string& name, const Light& light) const;
    void setLight(const Light& light) const;
    void use() const;
    void del() const;
};
