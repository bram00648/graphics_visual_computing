#include "ActiveEdgeTable.h"


namespace cg {

	ActiveEdgeTable::ActiveEdgeTable()
	= default;

	void ActiveEdgeTable::Add(Edge edge)
	{
		if (edge.y_down() == edge.y_up())
			return;

		std::list<Edge>::iterator iterator;

		for (iterator = m_activeEdges.begin(); iterator != m_activeEdges.end(); iterator++) {
			if (edge.currentX == iterator->currentX && edge.reversedM < iterator->reversedM) {
				m_activeEdges.insert(iterator, edge);
				return;
			}
			if (edge.currentX < iterator->currentX) {
				m_activeEdges.insert(iterator, edge);
				return;
			}
		}
		m_activeEdges.insert(iterator, edge);
	}

	void ActiveEdgeTable::UpdateCurrentXValues()
	{
		for (auto & m_activeEdge : m_activeEdges) {
			m_activeEdge.currentX += m_activeEdge.reversedM;
		}
	}

	void ActiveEdgeTable::RemoveObsoleteEdges(int y)
	{
		auto iterator = m_activeEdges.begin();
		while (iterator != m_activeEdges.end()) {
			if (iterator->y_up() == y)
				iterator = m_activeEdges.erase(iterator);
			else
				iterator++;
		}
	}

    void ActiveEdgeTable::Add(const EdgeTableRow &row) {
        for (auto current : row.m_edges) {
            current.currentX = (float)current.x_down();
            Add(current);
        }
    }

}