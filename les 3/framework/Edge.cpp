#include "Edge.h"

namespace cg {
	Edge::Edge(Point p1, Point p2)
	{
		if (p1.Y() < p2.Y()) {
			m_down = p1;
			m_up = p2;
		}
		else {
			m_down = p2;
			m_up = p1;
		}
		if (m_up.Y() - m_down.Y() != 0)
			reversedM = (float)(m_up.X() - m_down.X()) / (float)(m_up.Y() - m_down.Y());
		else
			reversedM = 0.0;
	}
}

