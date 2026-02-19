#include "DrawTool.h"
#include "EdgeTable.h"
#include "ActiveEdgeTable.h"


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
}

void DrawTool::DrawMidPointLine(cg::Line line, cg::RGBColor color)
{
    /* TODO */
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
