//
// Created by bvanherle on 25/04/2023.
//

#include "RayTracer.h"

void RayTracer::put_pixel(int x, int y, RGBColor color) {
    const unsigned char c[] = {color.r(), color.g(), color.b()};

    if ((x > 0 && x < m_width) && (y > 0 && y < m_height)) {
        m_canvas.draw_point(x, y, c);
    }
}

void RayTracer::trace_view() {
    for(int x = 0; x < m_width; x++) {
        for(int y = 0; y < m_height; y++) {
            RGBColor c(x/(float)m_width * 255, 127, y/(float)m_height * 255);
            put_pixel(x, y, c);
        }
    }
}

void RayTracer::show() {
    while(!m_display.is_closed() && !m_display.is_keyESC())
        m_display.display(m_canvas);
}
