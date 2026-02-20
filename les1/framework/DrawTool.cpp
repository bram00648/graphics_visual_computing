#include "DrawTool.h"
#include "EdgeTable.h"
#include "ActiveEdgeTable.h"
#include "Point.h"

void DrawTool::PutPixel(int x, int y, cg::RGBColor color)
{
    const unsigned char c[] = {color.r(), color.g(), color.b()};

	x += m_width / 2;
	y = m_height - (y + m_height / 2);

    m_canvas.draw_point(x, y, c);
}

void DrawTool::DrawDDALine(cg::Line line, cg::RGBColor color)
{
    /* TODO */
    float x {(float) line.x0()};
    float y {(float) line.y0()};
    float m {};
    int dx {line.x1() - line.x0()};
    int dy {line.y1() - line.y0()};
    float xInc {0};
    float yInc {0};

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    if (steps != 0) {
        xInc= (float) dx / steps;
        yInc = (float) dy / steps;
    } 
    
    // kleiner of gelijk aan anders mis je het eind punt in dit algoritme
    for (int i = 0; i <= steps; i++) {
        PutPixel((int) round(x), (int) round(y), color);
        x += xInc;
        y += yInc;
    }
}

void DrawTool::DrawMidPointLine(cg::Line line, cg::RGBColor color)
{
    int x0 = line.x0();
    int y0 = line.y0();
    int x1 = line.x1();
    int y1 = line.y1();

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    bool steep = dy > dx;

    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(dx, dy);
        std::swap(sx, sy);
    }

    int D = 2*dy - dx;

    int x = x0;
    int y = y0;

    for (int i = 0; i <= dx; i++) {

        if (steep)
            PutPixel(y, x, color);
        else
            PutPixel(x, y, color);

        if (D >= 0) {
            y += sy;
            D += 2*(dy - dx);
        } else {
            D += 2*dy;
        }

        x += sx;
    }
}

void DrawTool::DrawAllCirclePoints(cg::Point point, cg::Point center, cg::RGBColor color)
{
	PutPixel(center.X() + point.X(), center.Y() + point.Y(), color);
	PutPixel(center.X() + point.Y(), center.Y() + point.X(), color);
	PutPixel(center.X() + point.Y(), center.Y() - point.X(), color);
	PutPixel(center.X() + point.X(), center.Y() - point.Y(), color);
	PutPixel(center.X() - point.X(), center.Y() - point.Y(), color);
	PutPixel(center.X() - point.Y(), center.Y() - point.X(), color);
	PutPixel(center.X() - point.Y(), center.Y() + point.X(), color);
	PutPixel(center.X() - point.X(), center.Y() + point.Y(), color);
}

void DrawTool::DrawMidPointCircle(cg::Point center, int radius, cg::RGBColor color)
{
    /* TODO */
    int x {0};
    int y {radius};
    int D {1- radius};
    DrawAllCirclePoints(cg::Point(x, y), center, color);
    while ( x < y ) {
        if(D<0)
            D += x*2+3;
        else {
            D += (x-y) * 2 + 5;
            y--;
        }
        x++;
        DrawAllCirclePoints(cg::Point(x, y), center, color);

    }
}

void DrawTool::FillPolygon(cg::Polygon polygon, cg::RGBColor color)
{
    /* TODO */
}

void DrawTool::Show()
{
    m_display.display(m_canvas);
    while (!m_display.is_closed()) {
        m_display.wait();
    }
}

void DrawTool::Show(const unsigned int milliseconds)
{
    m_display.display(m_canvas);
    m_display.wait(milliseconds);
	
}

void DrawTool::Start()
{
	while (true) {
		Reset();
		Draw();
		Show(10);
	}
}

void DrawTool::Draw()
{
    /* Vervolledig de onderstaande functies zodat de lijnen, cirkels en polygonen getekend worden */
    DrawDDALine(cg::Line(cg::Point(-10, -10), cg::Point(50, 50)), cg::RGBColor(255, 0, 0));
    DrawMidPointLine(cg::Line(cg::Point(-10, -10), cg::Point(-50, 80)), cg::RGBColor(255, 0, 255));
    DrawMidPointCircle(cg::Point(-10, -10), 80, cg::RGBColor(0, 255, 255));

    cg::Polygon polygon;
    polygon.AddPoint(cg::Point(50, 50));
    polygon.AddPoint(cg::Point(100, 100));
    polygon.AddPoint(cg::Point(150, 50));
    polygon.AddPoint(cg::Point(100, 75));

    FillPolygon(polygon, cg::RGBColor(0, 255, 0));
}


void DrawTool::Reset()
{
    m_canvas.fill(0);
}
