//
// Created by bvanherle on 25/04/2023.
//

#ifndef RAYTRACE_FRAMEWORK_RAYTRACER_H
#define RAYTRACE_FRAMEWORK_RAYTRACER_H

#include "CImg.h"
#include "RGBColor.h"
#include "Shape.h"

using namespace cimg_library;

class RayTracer {
private:
    int m_width;
    int m_height;

    CImg<unsigned char> m_canvas;
    CImgDisplay m_display;

    void put_pixel(int x, int y, RGBColor color);

public:
    RayTracer(int width, int height) : m_width(width), m_height(height), m_canvas(width, height, 1, 3, false), m_display(m_canvas, "Raytracer"){};

    void trace_view();
    void show();
};


#endif //RAYTRACE_FRAMEWORK_RAYTRACER_H
