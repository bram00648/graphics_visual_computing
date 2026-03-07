#include "Polygon.h"


namespace cg {

	Polygon::Polygon()
	{
	}

	void Polygon::AddPoint(Point point)
	{
		m_points.push_back(point);
	}

	void Polygon::Clear()
	{
		m_points.clear();
	}

	Point Polygon::GetPoint(int index) const
	{
		return m_points[index];
	}

	int Polygon::GetSize() const
	{
		return m_points.size();
	}

	int Polygon::GetLowestY() const
	{
		int lowestY = m_points[0].Y();
		for (auto& point : m_points) {
			if (point.Y() < lowestY)
				lowestY = point.Y();
		}

		return lowestY;
	}

	int Polygon::GetHighestY() const
	{
		int highestY = m_points[0].Y();
		for (auto& point : m_points) {
			if (point.Y() > highestY)
				highestY = point.Y();
		}

		return highestY;
	}

}

