//
// Created by bvanherle on 02/03/2023.
//

#include <iostream>
#include "Bezier.h"

// dit is eigenlijk de formule voor een param cube curve en dan naar matrixvorm omgezet, hier kan je mee werken.
Bezier::Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int steps, Bezier::IterationMethod method) : ParamCubeCurve(p0, p1, p2, p3, steps), m_method(method) {
    m_base = glm::mat4(
        glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
        glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
        glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
    );
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
    for (int i = 0; i <= steps; i++) {
    double t = i / (double)steps;
    AddPoint(Evaluate(t));
}
}

Bezier::Bezier() : ParamCubeCurve(glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3(), 0), m_method(IterationMethod::BRUTEFORCE) {

}

void Bezier::ForwardDifference(int steps) {
    ClearPoints();

    float dt = 1.0 / steps;
    float dt2 = dt * dt;
    float dt3 = dt2 * dt;

    // Coëfficiënten van de kubische veelterm: P(t) = a t^3 + b t^2 + c t + d
    glm::mat4 B = m_base;       // basis matrix
    glm::mat4 G = m_geometric;  // controlepunten

    glm::vec3 a = glm::vec3(B[0] * G);
    glm::vec3 b = glm::vec3(B[1] * G);
    glm::vec3 c = glm::vec3(B[2] * G);
    glm::vec3 d = glm::vec3(B[3] * G);

    glm::vec3 P = d;
    glm::vec3 dP = c * dt + b * dt2 + a * dt3;
    glm::vec3 d2P = 2.0f * b * dt2 + 6.0f * a * dt3;
    glm::vec3 d3P = 6.0f * a * dt3;

    for (int i = 0; i <= steps; i++) {
        AddPoint(P);
        P += dP;
        dP += d2P;
        d2P += d3P;
    }
}

void Bezier::Casteljau(int steps) {
    /* TODO */
}
