#pragma once
#include <vector>
#include "Shape.h"

class Scene {
public:
    glm::vec3 eye;

    void add_shape(Shape* shape) {
        shapes.push_back(shape);
    }

    bool get_closest_intersection(const Ray& ray, RayHit& closestHit) const;

private:
    std::vector<Shape*> shapes;
};