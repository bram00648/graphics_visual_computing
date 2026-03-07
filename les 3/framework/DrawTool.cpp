#include "DrawTool.h"
#include "EdgeTable.h"
#include "ActiveEdgeTable.h"
#include <glm/ext/matrix_float4x4.hpp>

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


void DrawTool::Show(const unsigned int milliseconds)
{
    DrawClippingWindow();
    CheckCameraControls();
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
    /* Zet m_model, m_view en m_projection */
    m_model      = glm::mat4(1.0f);
    m_view       = glm::translate(glm::mat4(1.0f), -m_cameraPos);
    m_projection = GetProjectionMatrix(d);

    float axisLength = 100.0;
    Draw3DLine(glm::vec4(-axisLength, 0, 0, 1), glm::vec4(axisLength, 0, 0, 1), cg::RGBColor(255, 0, 0));
    Draw3DLine(glm::vec4(0, -axisLength, 0, 1), glm::vec4(0, axisLength, 0, 1), cg::RGBColor(0, 255, 0));
    Draw3DLine(glm::vec4(0, 0, -axisLength, 1), glm::vec4(0, 0, axisLength, 1), cg::RGBColor(0, 0, 255));

    /* Teken Cubes */
    PushMatrix();
    m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(25.0f, 25.0f, 25.0f));
    DrawUnitCube(cg::RGBColor(0, 200, 0));
    PopMatrix();

    PushMatrix();
    m_model = glm::translate(m_model, glm::vec3(50.0f, 50.0f, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(25.0f, 25.0f, 25.0f));
    DrawUnitCube(cg::RGBColor(200, 10, 0));
    PopMatrix();



}

bool DrawTool::CyrusBeckClip(cg::Line& line) const
{
    int x0 = line.x0();
    int y0 = line.y0();
    int x1 = line.x1();
    int y1 = line.y1();

    cg::Point P0(x0, y0), P1(x1, y1), D(x1 - x0, y1 - y0);

    OutCode OutCode0, OutCode1;
    float tE, tL, t, NiDotD;
    cg::Point Ni, Pei, P0_Pei;

    OutCode0 = CompOutCode(x0, y0);
    OutCode1 = CompOutCode(x1, y1);

    if ((OutCode0.all | OutCode1.all) == 0)					//triviaal aanvaard
    {
        line.SetData(cg::Point(x0, y0), cg::Point(x1, y1));
        return true;
    }
    else if ((OutCode0.all & OutCode1.all) != 0)					//triviaal geweigerd
    {
        return false;
    }
    else	//doe Cyrus-Beck
    {
        if (x0 - x1 <= 0.001 && x0 - x1 >= -0.001 && y0 - y1 <= 0.001 && y0 - y1 >= -0.001)
        {
            //begin- en eindpunt zijn gelijk
            return false;
        }
        else
        {

            tE = 0;
            tL = 1;

            for (int i = 0; i < 4; i++)		// vier kanten:		0 = onder | 1 = rechts | 2 = boven | 3 = links
            {
                switch (i)
                {
                    case 0:	// onder
                    {
                        Ni = cg::Point(0.0f, -1.0f);
                        Pei = cg::Point(ClipLeft(), ClipBottom());
                        break;
                    }
                    case 1:	// rechts
                    {
                        Ni = cg::Point(1.0f, 0.0f);
                        Pei = cg::Point(ClipRight(), ClipBottom());
                        break;
                    }
                    case 2:	// boven
                    {
                        Ni = cg::Point(0.0f, 1.0f);
                        Pei = cg::Point(ClipRight(), ClipTop());
                        break;
                    }
                    case 3:	// links
                    {
                        Ni = cg::Point(-1.0f, 0.0f);
                        Pei = cg::Point(ClipLeft(), ClipTop());
                        break;
                    }
                    default:
                        break;
                }

                NiDotD = Ni * D;

                if (NiDotD != 0)						// anders loopt ze parallell met de edge
                {
                    P0_Pei = cg::Point((P0.X() - Pei.X()), (P0.Y() - Pei.Y()));

                    // t berekenen:		t = (Ni * [P0 - Pei]) / (-Ni * D)
                    t = (float)(Ni * P0_Pei) / (float)(-Ni * D);

                    if (NiDotD > 0)	// => PL
                    {
                        if (t < tL)
                            tL = t;
                    }
                    else			// => PE
                    {
                        if (t > tE)
                            tE = t;
                    }
                }

            }

            if (tE < tL)
            {
                // draw the line
                cg::Point PtE((P0.X() + (tE * D.X())), (P0.Y() + (tE * D.Y())));
                cg::Point PtL((P0.X() + (tL * D.X())), (P0.Y() + (tL * D.Y())));

                line.SetData(PtE, PtL);
                return true;
            }
            else
            {
                return false;
            }

        }

    }

    //return 0;
}

void DrawTool::Draw3DLine(glm::vec4 start, glm::vec4 end, cg::RGBColor color)
{
    cg::Point startPoint = ObjectToScreen(start);
    cg::Point endPoint = ObjectToScreen(end);

    cg::Line line(startPoint, endPoint);

    if (CyrusBeckClip(line))
        DrawMidPointLine(line, color);

}

void DrawTool::DrawUnitCube(cg::RGBColor color)
{

    Draw3DLine(glm::vec4(-0.5, -0.5,  0.5, 1.0), glm::vec4(-0.5, 0.5, 0.5, 1.0), color);
    Draw3DLine(glm::vec4(-0.5, 0.5, 0.5, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0), color);
    Draw3DLine(glm::vec4(0.5, 0.5, 0.5, 1.0), glm::vec4(0.5, -0.5, 0.5, 1.0), color);
    Draw3DLine(glm::vec4(0.5, -0.5, 0.5, 1.0), glm::vec4(-0.5, -0.5, 0.5, 1.0), color);

    Draw3DLine(glm::vec4(-0.5, -0.5, -0.5, 1.0), glm::vec4(-0.5, 0.5, -0.5, 1.0), color);
    Draw3DLine(glm::vec4(-0.5, 0.5, -0.5, 1.0), glm::vec4(0.5, 0.5, -0.5, 1.0), color);
    Draw3DLine(glm::vec4(0.5, 0.5, -0.5, 1.0), glm::vec4(0.5, -0.5, -0.5, 1.0), color);
    Draw3DLine(glm::vec4(0.5, -0.5, -0.5, 1.0), glm::vec4(-0.5, -0.5, -0.5, 1.0), color);

    Draw3DLine(glm::vec4(-0.5, -0.5, 0.5, 1.0), glm::vec4(-0.5, -0.5, -0.5, 1.0), color);
    Draw3DLine(glm::vec4(-0.5, 0.5, 0.5, 1.0), glm::vec4(-0.5, 0.5, -0.5, 1.0), color);
    Draw3DLine(glm::vec4(0.5, 0.5, 0.5, 1.0), glm::vec4(0.5, 0.5, -0.5, 1.0), color);
    Draw3DLine(glm::vec4(0.5, -0.5, 0.5, 1.0), glm::vec4(0.5, -0.5, -0.5, 1.0), color);

}

void DrawTool::PushMatrix()
{
    m_matrixStack.push(m_model);
}

void DrawTool::PopMatrix()
{
    if (!m_matrixStack.empty()) {
        m_model = m_matrixStack.top();
        m_matrixStack.pop();
    }
}

void DrawTool::DrawClippingWindow()
{

    DrawDDALine(cg::Line(cg::Point(ClipLeft(), ClipBottom()), cg::Point(ClipRight(), ClipBottom())), cg::RGBColor(255, 255, 255));
    DrawDDALine(cg::Line(cg::Point(ClipRight(), ClipBottom()), cg::Point(ClipRight(), ClipTop())), cg::RGBColor(255, 255, 255));
    DrawDDALine(cg::Line(cg::Point(ClipRight(), ClipTop()), cg::Point(ClipLeft(), ClipTop())), cg::RGBColor(255, 255, 255));
    DrawDDALine(cg::Line(cg::Point(ClipLeft(), ClipTop()), cg::Point(ClipLeft(), ClipBottom())), cg::RGBColor(255, 255, 255));
}

OutCode DrawTool::CompOutCode(float x, float y) const
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


glm::mat4 DrawTool::GetProjectionMatrix(float d) const
{
    /* TODO */
    glm::mat4 projectionMatrix {};

    projectionMatrix[0][0] = d;
    projectionMatrix[1][1] = d;
    projectionMatrix[2][2] = d;
    projectionMatrix[2][3] = 1.0f;

    return projectionMatrix;
}


void DrawTool::CheckCameraControls()
{
    float speed = 1.0f;
    if (m_display.is_keyARROWUP())
        m_cameraPos.y += speed;
    if (m_display.is_keyARROWDOWN())
        m_cameraPos.y -= speed;
    if (m_display.is_keyARROWRIGHT())
        m_cameraPos.x += speed;
    if (m_display.is_keyARROWLEFT())
        m_cameraPos.x -= speed;
}


void DrawTool::Reset()
{
    m_canvas.fill(0);
}

cg::Point DrawTool::ObjectToScreen(glm::vec4 objectPoint) const {
    glm::vec4 clipPoint = m_projection * m_view * m_model * objectPoint;

    float screenX = clipPoint.x / clipPoint.w;
    float screenY = clipPoint.y / clipPoint.w;

    return cg::Point(screenX, screenY);
}
