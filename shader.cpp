#include "light.h"
#include "material.h"
#include "shader.h"
#include "textured_material.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <plog/Log.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertCode;
    std::string fragCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch(std::ifstream::failure& e)
    {
        PLOG_ERROR << "Error: could not read shader files";
    }
    const char* vShaderCode = vertCode.c_str();
    const char* fShaderCode = fragCode.c_str();
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::del() const
{
    glDeleteProgram(ID);
}

Shader::~Shader()
{
    del();
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    setVec3(name, glm::vec3{x, y, z});
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    setVec4(name, glm::vec4(x, y, z, w));
}

void Shader::setMaterial(const std::string& name, const Material& mat) const
{
    setVec3(name + ".ambient", mat.ambient);
    setVec3(name + ".diffuse", mat.diffuse);
    setVec3(name + ".specular", mat.specular);
    setFloat(name + ".shininess", mat.shininess);
}

// Uses the default name for the material uniform, which is "material"
void Shader::setMaterial(const Material& mat) const
{
    setMaterial("material", mat);
}

void Shader::setMaterial(const std::string& name, const TexturedMaterial& mat) const
{
    setInt(name + ".diffuse", mat.diffuseId);
    setInt(name + ".specular", mat.specularId);
    setFloat(name + ".shininess", mat.shininess);
}

void Shader::setMaterial(const TexturedMaterial& mat) const
{
    setMaterial("material", mat);
}

void Shader::setLight(const std::string& name, const Light& light) const
{
    setVec3(name + ".position", light.position);
    setVec3(name + ".ambient", light.ambient);
    setVec3(name + ".diffuse", light.diffuse);
    setVec3(name + ".specular", light.specular);
}

void Shader::setLight(const Light& light) const
{
    setLight("light", light);
}
