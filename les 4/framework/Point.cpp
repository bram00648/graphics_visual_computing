#include "Point.h"


namespace cg {

    int Point::X() const
    {
        return m_x;
    }

    int Point::Y() const
    {
        return m_y;
    }

    int Point::operator*(Point& point) const
    {
        return ((m_x * point.X()) + (m_y * point.Y()));
    }

    Point Point::operator-() const
    {
        return {-m_x, -m_y};
    }

}
