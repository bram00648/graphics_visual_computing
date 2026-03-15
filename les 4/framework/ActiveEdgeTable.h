#pragma once
#include <list>
#include "Edge.h"
#include "EdgeTableRow.h"

namespace cg {

	class ActiveEdgeTable
	{
	public:
		ActiveEdgeTable();

		void Add(Edge edge);
		void Add(const EdgeTableRow& row);

		void UpdateCurrentXValues();
		void RemoveObsoleteEdges(int y);

		std::list<Edge> m_activeEdges;
	};

}


