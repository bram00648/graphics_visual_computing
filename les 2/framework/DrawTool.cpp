#include "DrawTool.h"
#include "EdgeTable.h"
#include "ActiveEdgeTable.h"

#include <iostream>

void DrawTool::PutPixel(int x, int y, cg::RGBColor color)
{
    const unsigned char c[] = {color.r(), color.g(), color.b()};

    x += m_width / 2;
    y = m_height - (y + m_height / 2);

    m_canvas.draw_point(x, y, c);
}

void DrawTool::DrawDDALine(cg::Line line, cg::RGBColor color)
{
    int x0 = line.x0();
    int y0 = line.y0();
    int x1 = line.x1();
    int y1 = line.y1();

    float dy, dx, m, x, y;

    int temp;

    dy = (float)(y1 - y0);
    dx = (float)(x1 - x0);
    m = dy / dx;

    if (m >= -1 && m <= 1)
    {
        //rc (m) tussen -1 en 1

        // delta == 1  => steeds van links naar rechts
        if (x0 > x1)
        {
            temp = x1;
            x1 = x0;
            x0 = temp;

            temp = y1;
            y1 = y0;
            y0 = temp;
        }


        y = (float)y0;
        for (x = (float)x0; x <= x1; x++)
        {
            PutPixel((int)x, (int)(y + 0.5), color);
            y += m;
        }

    }
    else
    {
        // delta == 1  => steeds van onder naar boven

        if (y0 > y1)
        {
            temp = x1;
            x1 = x0;
            x0 = temp;

            temp = y1;
            y1 = y0;
            y0 = temp;
        }

        m = dx / dy;
        x = (float)x0;
        for (y = (float)y0; y <= y1; y++)
        {
            PutPixel((int)(x + 0.5), (int)y, color);
            x += m;
        }
    }
}

void DrawTool::DrawMidPointLine(cg::Line line, cg::RGBColor color)
{
    int x0 = line.x0();
    int y0 = line.y0();
    int x1 = line.x1();
    int y1 = line.y1();

    int dx, dy, IncrementToE, IncrementToN, IncrementToS, IncrementToSE, IncrementToNE, d, x, y;
    float m;				// 1 float om m juist te berekenen : per lijn 1 maal

    // steeds van links naar rechts tekenen.

    if (x0 > x1)
    {
        int temp;
        temp = x1;
        x1 = x0;
        x0 = temp;

        temp = y1;
        y1 = y0;
        y0 = temp;
    }


    // het algoritme

    dy = y1 - y0;
    dx = x1 - x0;
    m = (float)dy / (float)dx;



    if (m >= -1 && m <= 1)
    {
        if (m >= 0)
        {
            //rc (m) tussen 0 en 1 (=> E en NE)

            d = (dy * 2) - dx;				// startwaarde
            IncrementToE = dy * 2;			// increment voor d, na verplaatsing naar E
            IncrementToNE = (dy - dx) * 2;	// increment voor d, na verplaatsing naar NE

            x = x0;
            y = y0;

            PutPixel(x, y, color);		// eerste punt

            while (x < x1)
            {
                if (d <= 0)				// Naar E gaan
                {
                    d += IncrementToE;
                }
                else					// Naar NE gaan
                {
                    d += IncrementToNE;
                    y++;
                }
                x++;

                PutPixel(x, y, color);	// Teken nieuwe pixel
            }
        }
        else if (m < 0)
        {
            //rc (m) tussen 0 en -1 (=> E en SE)

            d = (dy * 2) + dx;				// startwaarde
            IncrementToE = dy * 2;			// increment voor d, na verplaatsing naar E
            IncrementToSE = (dy + dx) * 2;	// increment voor d, na verplaatsing naar SE

            x = x0;
            y = y0;

            PutPixel(x, y, color);		// eerste punt

            while (x < x1)
            {
                if (d <= 0)				// Naar SE gaan
                {
                    d += IncrementToSE;
                    y--;
                }
                else					// Naar E gaan
                {
                    d += IncrementToE;
                }
                x++;

                PutPixel(x, y, color);	// Teken nieuwe pixel
            }
        }

    }

    else
    {
        // m > 1 of m < -1

        if (m > 1)
        {
            //rc (m) groter dan 1 (=> N en NE)

            d = dy - (dx * 2);				// startwaarde
            IncrementToN = -(dx * 2);		// increment voor d, na verplaatsing naar N
            IncrementToNE = (dy - dx) * 2;	// increment voor d, na verplaatsing naar NE

            x = x0;
            y = y0;

            PutPixel(x, y, color);		// eerste punt

            while (y < y1)
            {
                if (d >= 0)				// Naar N gaan
                {
                    d += IncrementToN;
                }
                else					// Naar NE gaan
                {
                    d += IncrementToNE;
                    x++;
                }
                y++;

                PutPixel(x, y, color);	// Teken nieuwe pixel
            }
        }

        else if (m < -1)
        {
            //rc (m) kleiner dan -1 (=> S en SE)

            d = dy + (dx * 2);				// startwaarde
            IncrementToS = (dx * 2);		// increment voor d, na verplaatsing naar S
            IncrementToSE = (dy + dx) * 2;	// increment voor d, na verplaatsing naar SE

            x = x0;
            y = y0;

            PutPixel(x, y, color);	// eerste punt

            while (y > y1)
            {
                if (d <= 0)			// Naar S gaan
                {
                    d += IncrementToS;
                }
                else				// Naar SE gaan
                {
                    d += IncrementToSE;
                    x++;
                }
                y--;

                PutPixel(x, y, color);	// Teken nieuwe pixel
            }
        }
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
    int x = 0;
    int y = radius;
    int der = 1 - radius;
    DrawAllCirclePoints(cg::Point(x, y), center, color);
    while (y > x) {
        if (der < 0)
            der += 2 * x + 3;
        else {
            der += 2 * (x - y) + 5;
            y--;
        }
        x++;
        DrawAllCirclePoints(cg::Point(x, y), center, color);
    }
}

void DrawTool::FillPolygon(cg::Polygon polygon, cg::RGBColor color)
{
    if (polygon.GetSize() <= 0)
        return;

    int minY = polygon.GetLowestY();
    int maxY = polygon.GetHighestY();

    cg::EdgeTable edgeTable;
    cg::ActiveEdgeTable activeEdgeTable;

    edgeTable.Initialize(polygon);

    for (int y = minY; y <= maxY; y++) {

        cg::EdgeTableRow row = edgeTable.GetEdgeTableRow(y);
        activeEdgeTable.Add(row);


        bool par = true;
        int firstX, secondX;

        for (auto & m_activeEdge : activeEdgeTable.m_activeEdges) {
            if (par) {
                firstX = (int)m_activeEdge.currentX;
                par = false;
            }
            else {
                secondX = (int) m_activeEdge.currentX;
                DrawMidPointLine(cg::Line(cg::Point(firstX, y), cg::Point(secondX, y)), color);
                par = true;
            }
        }

        activeEdgeTable.RemoveObsoleteEdges(y);
        activeEdgeTable.UpdateCurrentXValues();
    }
}

void DrawTool::Show()
{
    DrawClippingWindow();
    m_display.display(m_canvas);
    while (!m_display.is_closed()) {
        m_display.wait();
        if (m_display.is_keyARROWUP())
            ClipUp();
        if (m_display.is_keyARROWDOWN())
            ClipDown();
    }
}

void DrawTool::Show(const unsigned int milliseconds)
{
    CheckClipControls();
    DrawClippingWindow();
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
    /* Voorbeeld code om jouw implementaties te testen */

    cg::Line line(cg::Point(10, 10), cg::Point(50, 100));
    if(CohenSutherlandClip(line)) {
        DrawDDALine(line, cg::RGBColor(255, 0, 0));
    }


    cg::Polygon polygon;
    polygon.AddPoint(cg::Point(50, 50));
    polygon.AddPoint(cg::Point(100, 100));
    polygon.AddPoint(cg::Point(150, 50));
    polygon.AddPoint(cg::Point(100, 75));

    polygon = SutherlandHodgemanPolygonClip(polygon);
    FillPolygon(polygon, cg::RGBColor(0, 255, 255));

}

bool DrawTool::CohenSutherlandClip(cg::Line& line) const
{
    const int LEFT   = 1;
    const int RIGHT  = 2;
    const int BOTTOM = 4;
    const int TOP    = 8;

    float x0 = line.x0();
    float y0 = line.y0();
    float x1 = line.x1();
    float y1 = line.y1();

    int outcode0 = CompOutCode(x0, y0).all;
    int outcode1 = CompOutCode(x1, y1).all;

    while (true)
    {
        // Trivial accept
        if ((outcode0 | outcode1) == 0)
        {
            line.SetData(cg::Point(x0, y0), cg::Point(x1, y1));
            return true;
        }

        // Trivial reject
        if (outcode0 & outcode1)
        {
            return false;
        }

        float x, y;
        int outcodeOutside = outcode0 ? outcode0 : outcode1;

        if (outcodeOutside & LEFT)
        {
            x = ClipLeft();
            y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);
        }
        else if (outcodeOutside & RIGHT)
        {
            x = ClipRight();
            y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);
        }
        else if (outcodeOutside & BOTTOM)
        {
            y = ClipBottom();
            x = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        }
        else // TOP
        {
            y = ClipTop();
            x = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        }

        if (outcodeOutside == outcode0)
        {
            x0 = x;
            y0 = y;
            outcode0 = CompOutCode(x0, y0).all;
        }
        else
        {
            x1 = x;
            y1 = y;
            outcode1 = CompOutCode(x1, y1).all;
        }
    }
}

bool DrawTool::CyrusBeckClip(cg::Line& line) const
{
    /* TODO */
    return true;
}

cg::Polygon DrawTool::SutherlandHodgemanPolygonClip(cg::Polygon polygon) const
{
    /* TODO */
    return polygon;
}

void DrawTool::DrawClippingWindow()
{

    DrawDDALine(cg::Line(cg::Point(ClipLeft(), ClipBottom()), cg::Point(ClipRight(), ClipBottom())), cg::RGBColor(255, 255, 255));
    DrawDDALine(cg::Line(cg::Point(ClipRight(), ClipBottom()), cg::Point(ClipRight(), ClipTop())), cg::RGBColor(255, 255, 255));
    DrawDDALine(cg::Line(cg::Point(ClipRight(), ClipTop()), cg::Point(ClipLeft(), ClipTop())), cg::RGBColor(255, 255, 255));
    DrawDDALine(cg::Line(cg::Point(ClipLeft(), ClipTop()), cg::Point(ClipLeft(), ClipBottom())), cg::RGBColor(255, 255, 255));
}

void DrawTool::ClipUp()
{
    if (ClipTop() < m_height && ClipRight() < m_width)
        m_windowSize += 5;
}

void DrawTool::ClipDown()
{
    if (m_windowSize >= 10)
        m_windowSize -= 5;
}

OutCode DrawTool::CompOutCode(int x, int y) const
{
    OutCode code;

    if (y > ClipTop()) {
        code.top = 1;
        code.all += 8; // eerste bit aanzetten
    }
    else if (y < ClipBottom()) {
        code.bottom = 1;
        code.all += 4; // tweede bit aanzetten
    }

    if (x > ClipRight()) {
        code.right = 1;
        code.all += 2; // derde bit aanzetten
    }
    else if (x < ClipLeft()) {
        code.left = 1;
        code.all += 1; // vierde bit aanzetten
    }

    return code;
}

bool DrawTool::Inside(cg::Point point, int edgeNo, int value) const
{
    switch (edgeNo)
    {
        case 0:						// onder
        {
            if (point.Y() > value)
                return true;
            else
                return false;
            break;
        }
        case 1:						// rechts
        {
            if (point.X() < value)
                return true;
            else
                return false;
            break;
        }
        case 2:						// boven
        {
            if (point.Y() < value)
                return true;
            else
                return false;
            break;
        }
        case 3:						// links
        {
            if (point.X() > value)
                return true;
            else
                return false;
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

cg::Point DrawTool::GetIntersection(cg::Point first, cg::Point second, int edgeNo, int value) const
{
    float x0 = first.X();
    float y0 = first.Y();
    float x1 = second.X();
    float y1 = second.Y();

    float x = 0.0f;
    float y = 0.0f;

    if (edgeNo == 0)							// intersectie met onderkant berekenen
    {
        x = x0 + ((x1 - x0) * ((value - y0) / (y1 - y0)));
        y = value;
    }
    else if (edgeNo == 1)						// intersectie met rechterkant berekenen
    {
        y = y0 + ((y1 - y0) * ((value - x0) / (x1 - x0)));
        x = value;
    }
    else if (edgeNo == 2)						// intersectie met bovenkant berekenen
    {
        x = x0 + ((x1 - x0) * ((value - y0) / (y1 - y0)));
        y = value;
    }
    else if (edgeNo == 3)						// intersectie met linkerkant berekenen
    {
        y = y0 + ((y1 - y0) * ((value - x0) / (x1 - x0)));
        x = value;
    }

    return cg::Point(x, y);
}

void DrawTool::CheckClipControls()
{
    if (m_display.is_keyARROWUP())
        ClipUp();
    if (m_display.is_keyARROWDOWN())
        ClipDown();
}


void DrawTool::Reset()
{
    m_canvas.fill(0);
}
