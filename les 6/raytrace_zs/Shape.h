//
// Created by bvanherle on 25/04/2023.
//

#ifndef RAYTRACE_FRAMEWORK_SHAPE_H
#define RAYTRACE_FRAMEWORK_SHAPE_H

#include <glm/glm.hpp>
#include "RGBColor.h"
#include "Ray.h"
#include "RayHit.h"

struct Material {
    RGBColor color;
};


class Shape {
    
protected:
    glm::vec3 m_pos;

    glm::vec3 m_xrot;
    glm::vec3 m_yrot;
    glm::vec3 m_zrot;

    Material m_material;

public:
    virtual ~Shape() {}
    Shape(glm::vec3 pos, Material material) : m_pos(pos), m_material(material), m_xrot{0.0, 0.0, 0.0}, m_yrot{0.0, 0.0, 0.0}, m_zrot{0.0, 0.0, 0.0} {};

    void set_up(glm::vec3 up);

    Material get_material() const {
        return m_material;
    }

    glm::vec3 get_pos() const {
        return m_pos;
    }

    virtual RayHit get_intersection(const Ray &ray) const = 0;
};


#endif //RAYTRACE_FRAMEWORK_SHAPE_H
