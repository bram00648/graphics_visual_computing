#include "DrawTool.h"
#include "EdgeTable.h"
#include "ActiveEdgeTable.h"
#include "FileLoader.h"
#include "RGBColor.h"

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
    m_model = glm::mat4(1.0f);
    m_projection = GetProjectionMatrix(d);
    m_view = glm::translate(glm::mat4(1.0f), m_cameraPos);

    float axisLength = 100.0;
    Draw3DLine(glm::vec4(-axisLength, 0, 0, 1), glm::vec4(axisLength, 0, 0, 1), cg::RGBColor(255, 0, 0));
    Draw3DLine(glm::vec4(0, -axisLength, 0, 1), glm::vec4(0, axisLength, 0, 1), cg::RGBColor(0, 255, 0));
    Draw3DLine(glm::vec4(0, 0, -axisLength, 1), glm::vec4(0, 0, axisLength, 1), cg::RGBColor(0, 0, 255));


    m_objects = FileLoader::LoadObjects("../objects.txt");
    std::cout << "Loaded objects: " << m_objects.size() << std::endl;

    m_model = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 50.0f));


    DrawObjectFromList(0);
    DrawObjectFromList(1);

    m_beziers = FileLoader::LoadCurves("../objects.txt");

    DrawBezierFromList(0);

}

bool DrawTool::CohenSutherlandClip(cg::Line& line) const
{
    float x0 = (float)line.x0();
    float y0 = (float)line.y0();
    float x1 = (float)line.x1();
    float y1 = (float)line.y1();

    OutCode OutCode0, OutCode1;
    OutCode0 = CompOutCode(x0, y0);
    OutCode1 = CompOutCode(x1, y1);

    bool done = false;

    while (!done) {
        if ((OutCode0.all | OutCode1.all) == 0)					//triviaal aanvaard
        {
            line.SetData(cg::Point(x0, y0), cg::Point(x1, y1));
            return true;
        }
        else if ((OutCode0.all & OutCode1.all) != 0)					//triviaal geweigerd
        {
            return false;
        }
        else
        {
            OutCode outcodeOut = OutCode1.all > OutCode0.all ? OutCode1 : OutCode0;
            float x, y;
            if (outcodeOut.top) {           // point is above the clip window
                x = x0 + (x1 - x0) * (ClipTop() - y0) / (y1 - y0);
                y = ClipTop();
            }
            else if (outcodeOut.bottom) { // point is below the clip window
                x = x0 + (x1 - x0) * (ClipBottom() - y0) / (y1 - y0);
                y = ClipBottom();
            }
            else if (outcodeOut.right) {  // point is to the right of clip window
                y = y0 + (y1 - y0) * (ClipRight() - x0) / (x1 - x0);
                x = ClipRight();
            }
            else if (outcodeOut.left) {   // point is to the left of clip window
                y = y0 + (y1 - y0) * (ClipLeft() - x0) / (x1 - x0);
                x = ClipLeft();
            }

            if (outcodeOut.all == OutCode0.all) {
                x0 = x;
                y0 = y;
                OutCode0 = CompOutCode(x0, y0);
            }
            else {
                x1 = x;
                y1 = y;
                OutCode1 = CompOutCode(x1, y1);
            }
        }
    }

    return true;
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

cg::Polygon DrawTool::SutherlandHodgemanPolygonClip(cg::Polygon polygon) const
{
    cg::Polygon result;
    cg::Point first, second;

    int edgeNo, value;

    int clipValues[] = {ClipBottom(), ClipRight(), ClipTop(), ClipLeft()};

    for (edgeNo = 0; edgeNo < 4; edgeNo++) {
        if (polygon.GetSize() <= 1)
            return polygon;

        value = clipValues[edgeNo];

        first = polygon.GetPoint(polygon.GetSize() - 1);

        for (int i = 0; i < polygon.GetSize(); i++) {
            second = polygon.GetPoint(i);

            std::cout << value << std::endl;

            if (Inside(first, edgeNo, value) && Inside(second, edgeNo, value))	// case 1
            {
                //alleen second toevoegen
                result.AddPoint(second);
            }
            else if (Inside(first, edgeNo, value))					// case 2
            {
                //alleen intersection toevoegen
                cg::Point intersection = GetIntersection(first, second, edgeNo, value);
                result.AddPoint(intersection);

            }
            else if (Inside(second, edgeNo, value))				// case 3
            {
                //eerst intersection en dan second toevoegen
                cg::Point intersection = GetIntersection(first, second, edgeNo, value);
                result.AddPoint(intersection);
                result.AddPoint(second);
            }
            else													// case 4
            {
                //niks doen
            }

            first = second;
        }

        polygon = result;
        result = cg::Polygon();
    }

    return polygon;
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

glm::mat4 DrawTool::GetProjectionMatrix(float d) const
{
    glm::mat4 projection(1.0f);
    projection[3][3] = 0.0f;
    projection[2][3] = 1.0f / d;

    return projection;
}

void DrawTool::CheckClipControls()
{
    if (m_display.is_keyARROWUP())
        ClipUp();
    if (m_display.is_keyARROWDOWN())
        ClipDown();
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

void DrawTool::DrawObjectFromList(int index)
{
    /* TODO */
    Object object = m_objects[index];
    for (auto & face : object.faces) {
        DrawFace(face);
    }
}

void DrawTool::DrawFace(Face face)
{
    /* TODO */
    Draw3DLine(face.vertices[0], face.vertices[1], cg::RGBColor(0, 255, 0));
    Draw3DLine(face.vertices[1], face.vertices[2], cg::RGBColor(0, 255, 0));
    Draw3DLine(face.vertices[2], face.vertices[0], cg::RGBColor(0, 255, 0));
}

cg::Point DrawTool::ObjectToScreen(glm::vec4 objectPoint) const {
    objectPoint = m_projection * m_view * m_model * objectPoint;
    objectPoint /= objectPoint.w;

    return cg::Point((int)objectPoint.x, (int)objectPoint.y);
}

void DrawTool::DrawBezierFromList(int index) {
    Bezier& bezier = m_beziers[index];
    bezier.iterate();

    int n = bezier.PointCount();
    for (int i = 0; i < n - 1; i++) {
        glm::vec3 p0 = bezier.GetPoint(i);
        glm::vec3 p1 = bezier.GetPoint(i + 1);

        glm::vec4 start(p0, 1.0f);
        glm::vec4 end(p1, 1.0f);

        Draw3DLine(start, end, cg::RGBColor(255, 50, 100));
    }
}
