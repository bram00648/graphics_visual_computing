#pragma once
#include <vector>
#include "EdgeTableRow.h"
#include "Polygon.h"

namespace cg {
	class EdgeTable
	{
	public:
		EdgeTable();

		void Initialize(Polygon& polygon);
		EdgeTableRow GetEdgeTableRow(int y) const;

	private:
		std::vector<EdgeTableRow> m_rows;

		int m_minY{};
		int m_maxY{};

		void AddEdge(Edge edge);
	};
}


