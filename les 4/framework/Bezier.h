//
// Created by bvanherle on 02/03/2023.
//

#ifndef FRAMEWORK_BEZIER_H
#define FRAMEWORK_BEZIER_H


#include "ParamCubeCurve.h"

class Bezier : public ParamCubeCurve {
public:
    enum IterationMethod {
        BRUTEFORCE,
        FD,
        CASTELJAU
    };

    Bezier();
    Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int steps, IterationMethod method = IterationMethod::BRUTEFORCE);

    void iterate();

private:
    IterationMethod m_method;

    void Bruteforce(int steps);
    void ForwardDifference(int steps);
    void Casteljau(int steps);
};


#endif //FRAMEWORK_BEZIER_H
