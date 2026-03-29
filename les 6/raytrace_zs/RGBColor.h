#pragma once


#include <glm/vec3.hpp>

class RGBColor
{
private:
    unsigned char m_r;
    unsigned char m_g;
    unsigned char m_b;

public:
    explicit RGBColor(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255) : m_r(r), m_g(g), m_b(b) {};
    explicit RGBColor(glm::vec3 color) : m_r(255 * color.x), m_g(255 * color.y), m_b(255 * color.z) {};

    unsigned char r() const {return m_r; };
    unsigned char g() const {return m_g; };
    unsigned char b() const {return m_b; };

    glm::vec3 as_vec3() const {
        return {(float) m_r / 255.0, (float) m_g / 255.0, (float) m_b / 255.0};
    }

};


