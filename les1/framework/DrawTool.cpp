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
    

    for (int i = 0; i < steps; i++) {
        PutPixel((int) round(x), (int) round(y), color);
        x += xInc;
        y += yInc;
    }
}

void DrawTool::DrawMidPointLine(cg::Line line, cg::RGBColor color)
{
    /* TODO */
    int dy {line.y1() - line.y0()};
    int dx {line.x1() - line.x0()};
    int d  {dy * 2 - dx};
    int incrE {dy*2};
    int incrNE {(dy - dx) * 2};
    int x {line.x0()};
    int y {line.y0()};
    PutPixel(x, y, color);
    while (x < line.x1()) {
        if (d<=0)
            d += incrE;
        else {
            d += incrNE;
            y ++;
        }
        x++;
        PutPixel(x, y, color);
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
