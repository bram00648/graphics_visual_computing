#pragma once
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(glm::vec3 pos,
           float radius,
           Material material)
        : Shape(pos, material),   // ← verplicht
          radius(radius)
    {}


    virtual RayHit get_intersection(const Ray& ray) const override;

private:
    glm::vec3 center;
    float radius;
};