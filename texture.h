#pragma once
#include <plog/Log.h>
#include <string>
class Texture
{
public:
    unsigned int id;
    unsigned int texture;
    enum WrapMode
    {
        repeat,
        mirroredRepeat,
        clampToEdge,
        clampToBorder,
    };
    enum FilterMode
    {
        nearest,
        linear,
    };
    Texture(const std::string& imageLocation, bool hasAlpha, WrapMode wrapMode, FilterMode filterMode);
    void bindTexture() const;
private:
    static unsigned int m_counter;
};
