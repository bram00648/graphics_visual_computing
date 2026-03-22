//
// Created by bvanherle on 01/03/2023.
//

#include "ParamCubeCurve.h"
#include <glm/ext/vector_float4.hpp>

ParamCubeCurve::ParamCubeCurve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int steps) : m_geometric(p0, p1, p2, p3), m_base(1.0f), m_steps(steps) {}

// evaluate gaat gewoon de formule toepassen, T * m_base * m_geometric, je krijgt al de coordinaten van uw hele curve terug.
// een glm vec4 naar vec3 omzetten neemt gewoon de 3 eerste elementen, dus x, y en z, en negeert de w component.
glm::vec3 ParamCubeCurve::Evaluate(double t) {
    /* TODO */
    glm::vec4 T = glm::vec4(t*t*t, t*t, t, 1.0f);
    glm::vec4 result = T * m_base * m_geometric;
    return glm::vec3(result);

}

void ParamCubeCurve::AddPoint(glm::vec3 point) {
    m_points.push_back(point);
}

void ParamCubeCurve::ClearPoints() {
    m_points.clear();
}

int ParamCubeCurve::PointCount() const {
    return (int)m_points.size();
}

glm::vec3 ParamCubeCurve::GetPoint(int index) const {
    return m_points[index];
}
