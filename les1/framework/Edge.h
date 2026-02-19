#pragma once
#include "Point.h"

namespace cg {

	class Edge
	{
	public:
		Edge(Point p1, Point p2);

		int x_down() const { return m_down.X(); }
		int y_down() const { return m_down.Y(); }
		int y_up() const { return m_up.Y(); }

		float currentX{};
		float reversedM;

	private:
		Point m_down;
		Point m_up;
	};

}


