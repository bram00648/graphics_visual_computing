#pragma once

namespace cg {

	class Point
	{
	private:
		int m_x;
		int m_y;

	public:
		Point() : m_x(0.0), m_y(0.0) {};
		Point(int x, int y) : m_x(x), m_y(y) {};

		int X() const;
		int Y() const;

		int operator*(Point& point) const;
		Point operator-() const;
	};
}
