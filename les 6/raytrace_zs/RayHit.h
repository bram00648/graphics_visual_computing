#pragma once
#include "glm/glm.hpp"

class Shape;

struct RayHit {
    bool hit = false;
    float distance = 0.0f;
    glm::vec3 position;
    glm::vec3 normal;
    const Shape* object = nullptr;
};