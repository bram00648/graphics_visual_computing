#include <iostream>
#include "RayTracer.h"

int main() {
    CImg<unsigned char> m_canvas;
    CImgDisplay m_display;


    RayTracer raytracer(200, 200);
    raytracer.trace_view();

    raytracer.show();

    return 0;
}
