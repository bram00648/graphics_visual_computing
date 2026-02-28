#pragma once

#include "Polygon.h"
#include "RGBColor.h"
#include "CImg.h"
#include "Line.h"

#include <stack>
#include <iostream>
#include <fstream>
#include <string>

using namespace cimg_library;

struct OutCode {
    int all = 0;
    int left = 0;
    int right = 0;
    int bottom = 0;
    int top = 0;
};

class DrawTool
{
private:
    int m_width;
    int m_height;

    int m_windowSize;

    CImg<unsigned char> m_canvas;
    CImgDisplay m_display;

    void DrawClippingWindow();
    void ClipUp();
    void ClipDown();

    int ClipTop() const { return m_windowSize; };
    int ClipBottom() const { return -m_windowSize; };
    int ClipRight() const { return m_windowSize; };
    int ClipLeft() const { return -m_windowSize; };

    OutCode CompOutCode(int x, int y) const;
    bool Inside(cg::Point point, int edgeNo, int value) const;
    cg::Point GetIntersection(cg::Point first, cg::Point second, int edgeNo, int value) const;

    void CheckClipControls();

public:
    DrawTool(int width, int height) : m_width(width), m_height(height), m_canvas(width, height, 1, 3, false), m_display()
    {
        m_windowSize = 200;
        Reset();
    };

    void PutPixel(int x, int y, cg::RGBColor color);

    void DrawDDALine(cg::Line line, cg::RGBColor color);
    void DrawMidPointLine(cg::Line line, cg::RGBColor color);

    void DrawAllCirclePoints(cg::Point point, cg::Point center, cg::RGBColor color);
    void DrawMidPointCircle(cg::Point center, int radius, cg::RGBColor color);

    void FillPolygon(cg::Polygon polygon, cg::RGBColor color);

    void Show();
    void Show(const unsigned int milliseconds);
    void Start();
    void Draw();

    bool CohenSutherlandClip(cg::Line& line) const;
    bool CyrusBeckClip(cg::Line& line) const;
    cg::Polygon SutherlandHodgemanPolygonClip(cg::Polygon polygon) const;

    void Reset();
};

