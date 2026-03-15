//
// Created by bvanherle on 02/03/2023.
//

#include <iostream>
#include "Bezier.h"

Bezier::Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int steps, Bezier::IterationMethod method) : ParamCubeCurve(p0, p1, p2, p3, steps), m_method(method) {
}

void Bezier::iterate() {
    ClearPoints();

    switch (m_method) {
        case IterationMethod::BRUTEFORCE:
            Bruteforce(m_steps);
            break;
        case IterationMethod::FD:
            ForwardDifference(m_steps);
            break;
        case IterationMethod::CASTELJAU:
            Casteljau(m_steps);
            break;
        default:
            std::cerr << "Method not implemented" << std::endl;
    }
}

void Bezier::Bruteforce(int steps) {
    /* TODO */
}

Bezier::Bezier() : ParamCubeCurve(glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3(), 0), m_method(IterationMethod::BRUTEFORCE) {

}

void Bezier::ForwardDifference(int steps) {
    /* TODO */
}

void Bezier::Casteljau(int steps) {
    /* TODO */
}
