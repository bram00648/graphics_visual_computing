#pragma once

#include <list>
#include "Edge.h"

namespace cg {
	class EdgeTableRow
	{
	public:
		EdgeTableRow();
		void AddEdge(Edge edge);

		std::list<Edge> m_edges;

	};
}


