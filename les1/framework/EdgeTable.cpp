#include "EdgeTable.h"

namespace cg {

	EdgeTable::EdgeTable()
	= default;

	void EdgeTable::Initialize(Polygon& polygon)
	{
		m_minY = polygon.GetLowestY();
		m_maxY = polygon.GetHighestY();

		if (!m_rows.empty())
			m_rows.clear();

		int row_count = m_maxY - m_minY + 1;

		for (int i = 0; i < row_count; i++)
			m_rows.emplace_back();

		for (int j = 0; j < polygon.GetSize() - 1; j++) {
			auto p1 = polygon.GetPoint(j);
			auto p2 = polygon.GetPoint(j + 1);
			Edge edge(p1, p2);
			AddEdge(edge);
		}
		Edge edge(polygon.GetPoint(0), polygon.GetPoint(polygon.GetSize() - 1));
		AddEdge(edge);
	}

	EdgeTableRow EdgeTable::GetEdgeTableRow(int y) const
	{
		return m_rows[y - m_minY];
	}

	void EdgeTable::AddEdge(Edge edge)
	{
		m_rows[edge.y_down() - m_minY].AddEdge(edge);
	}

}

