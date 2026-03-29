#include "Scene.h"

bool Scene::get_closest_intersection(const Ray& ray, RayHit& closestHit) const {

    bool found = false;
    float minDistance = std::numeric_limits<float>::max();

    for (const Shape* shape : shapes) {
        RayHit hit = shape->get_intersection(ray);

        if (hit.hit && hit.distance < minDistance) {
            found = true;
            minDistance = hit.distance;
            closestHit = hit;
        }
    }

    return found;
}