//
// Created by bvanherle on 25/04/2023.
//

#ifndef RAYTRACE_FRAMEWORK_RAYTRACER_H
#define RAYTRACE_FRAMEWORK_RAYTRACER_H

#include "CImg.h"
#include "RGBColor.h"
#include "Shape.h"
#include "Scene.h"

using namespace cimg_library;

class RayTracer {
private:
    int m_width;
    int m_height;
    Scene m_scene;

    CImg<unsigned char> m_canvas;
    CImgDisplay m_display;

    void put_pixel(int x, int y, RGBColor color);

public:
    RayTracer(int width, int height);
    void trace_view();
    void show();
};


#endif //RAYTRACE_FRAMEWORK_RAYTRACER_H
