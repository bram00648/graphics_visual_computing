#include "ActiveEdgeTable.h"


namespace cg {

	ActiveEdgeTable::ActiveEdgeTable()
	= default;

	void ActiveEdgeTable::Add(Edge edge)
	{
        /* TODO */
	}

	void ActiveEdgeTable::Add(const EdgeTableRow& row)
	{
		for (auto current : row.m_edges) {
				current.currentX = (float)current.x_down();
			Add(current);
		}
	}

	void ActiveEdgeTable::UpdateCurrentXValues()
	{
        /* TODO */
	}

	void ActiveEdgeTable::RemoveObsoleteEdges(int y)
	{
        /* TODO */
	}

}