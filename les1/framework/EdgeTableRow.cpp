#include "EdgeTableRow.h"

namespace cg {

	EdgeTableRow::EdgeTableRow()
	= default;

	void EdgeTableRow::AddEdge(Edge edge)
	{
		bool inserted = false;

		std::list<Edge>::iterator iterator;
		for (iterator = m_edges.begin(); iterator != m_edges.end() && !inserted; iterator++) {
			if (iterator->x_down() > edge.x_down()) {
				m_edges.insert(iterator, edge);
				inserted = true;
			}
		}
		if (!inserted)
			m_edges.push_back(edge);
	}

}

