//
// Created by bvanherle on 25/04/2023.
//

#include "Shape.h"

glm::vec3 smallest_contribution_vector(glm::vec3 vector) {
    if (vector.x <= vector.y && vector.x <= vector.z)
        return {1.0, 0.0, 0.0};
    else if (vector.y <= vector.x && vector.y <= vector.z)
        return {0.0, 1.0, 0.0};
    else
        return {0.0, 0.0, 1.0};
}

void Shape::set_up(glm::vec3 up) {
    m_yrot = glm::normalize(up);

    auto temp = glm::normalize(smallest_contribution_vector(up));
    m_xrot = glm::normalize(glm::cross(up, temp));
    m_zrot = glm::normalize(glm::cross(m_xrot, m_yrot));
}
