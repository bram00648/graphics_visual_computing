#include "Sphere.h"
#include <glm/glm.hpp>
#include <cmath>

RayHit Sphere::get_intersection(const Ray& ray) const
{
    RayHit hitResult;


    glm::vec3 oc = ray.origin() - m_pos;

    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2.0f * glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f)
        return hitResult; 

    float sqrtD = std::sqrt(discriminant);

    float t1 = (-b - sqrtD) / (2.0f * a);
    float t2 = (-b + sqrtD) / (2.0f * a);

    float t = t1;

    if (t < 0.0f)
        t = t2;

    if (t < 0.0f)
        return hitResult;

    hitResult.hit = true;
    hitResult.distance = t;
    hitResult.position = ray.at(t);
    hitResult.normal = glm::normalize(hitResult.position - m_pos);
    hitResult.object = this;

    return hitResult;
}