#pragma once

#include "Point.h"

namespace cg {

	class Line
	{
	private:
		Point m_p0;
		Point m_p1;

	public:
		Line(Point p0, Point p1) : m_p0(p0), m_p1(p1) {}

		void SetData(Point p0, Point p1);

		int x0();
		int y0();
		int x1();
		int y1();
	};
}


