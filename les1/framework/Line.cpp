#include "Line.h"

namespace cg {
    void Line::SetData(Point p0, Point p1)
    {
        m_p0 = p0;
        m_p1 = p1;
    }
    int Line::x0()
    {
        return m_p0.X();
    }

    int Line::y0()
    {
        return m_p0.Y();
    }

    int Line::x1()
    {
        return m_p1.X();
    }

    int Line::y1()
    {
        return m_p1.Y();
    }

}

