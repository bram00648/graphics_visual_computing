//
// Created by bvanherle on 25/04/2023.
//

#include "RayTracer.h"
#include "Sphere.h"


RayTracer::RayTracer(int width, int height)
    : m_width(width),
      m_height(height),
      m_canvas(width, height, 1, 3, false),
      m_display(m_canvas, "Raytracer")
{
    m_scene.eye = glm::vec3(0.0f, 0.0f, 300.0f);

    Material mat;
    mat.color = RGBColor(255, 0, 0);

    Sphere* sphere = new Sphere(
        glm::vec3(100.0f, 100.0f, -10.0f),
        50.0f,
        mat
    );

    m_scene.add_shape(sphere);
}

void RayTracer::put_pixel(int x, int y, RGBColor color) {
    const unsigned char c[] = {color.r(), color.g(), color.b()};

    if ((x > 0 && x < m_width) && (y > 0 && y < m_height)) {
        m_canvas.draw_point(x, y, c);
    }
}

void RayTracer::trace_view()
{
    float viewPlaneZ = 0.0f;

    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {

            glm::vec3 pixelPos(
                x - m_width / 2.0f,
                y - m_height / 2.0f,
                viewPlaneZ
            );

            glm::vec3 rayDir = pixelPos - m_scene.eye;

            Ray ray(m_scene.eye, rayDir);

            RayHit hit;

            if (m_scene.get_closest_intersection(ray, hit)) {
                RGBColor col = hit.object->get_material().color;
                put_pixel(x, y, col);
            }
            else {
                put_pixel(x, y, RGBColor(0, 0, 0));
            }
        }
    }
}
void RayTracer::show() {
    while(!m_display.is_closed() && !m_display.is_keyESC())
        m_display.display(m_canvas);
}
