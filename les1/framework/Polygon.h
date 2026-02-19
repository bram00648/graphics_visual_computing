#pragma once
#include "Point.h"
#include <vector>
#include <limits>

namespace cg {

	class Polygon
	{
	public:
		Polygon();

		void AddPoint(Point point);
		void Clear();
		Point GetPoint(int index) const;
		int GetSize() const;

		int GetLowestY() const;
		int GetHighestY() const;

	private:
		std::vector<Point> m_points;
	};

}


