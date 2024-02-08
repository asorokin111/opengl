#include "texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <string>

unsigned int Texture::m_counter = 0;

Texture::Texture(const std::string& imageLocation, bool hasAlpha, WrapMode wrapMode, FilterMode filterMode)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum wrap, filter;

    switch (wrapMode)
    {
    case Texture::repeat:
        wrap = GL_REPEAT;
        break;
    case Texture::mirroredRepeat:
        wrap = GL_MIRRORED_REPEAT;
        break;
    case Texture::clampToEdge:
        wrap = GL_CLAMP_TO_EDGE;
        break;
    case Texture::clampToBorder:
        wrap = GL_CLAMP_TO_BORDER;
        break;
    default:
        PLOG_WARNING << "Unknown wrap mode passed to texture constructor, using default wrap mode.";
        wrap = GL_REPEAT;
        break;
    }

    switch (filterMode)
    {
    case Texture::nearest:
        filter = GL_NEAREST;
        break;
    case Texture::linear:
        filter = GL_LINEAR;
        break;
    default:
        PLOG_WARNING << "Unknown filter mode passed to texture constructor, using default filter mode.";
        filter = GL_NEAREST;
        break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(imageLocation.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        auto format = hasAlpha ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        PLOG_ERROR << "Failed to load texture from image, path: " << imageLocation;
    }
    stbi_image_free(data);
    id = m_counter++;
}

void Texture::bindTexture() const
{
    const unsigned int baseTexture = 0x84C0;
    glActiveTexture(baseTexture + id);
    glBindTexture(GL_TEXTURE_2D, texture);
}
