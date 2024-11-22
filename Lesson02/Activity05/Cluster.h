#pragma once

#include <vector>
#include <iostream>

class Cluster
{
public:
	class Node
	{
	public:
		friend Cluster;

		int		popNextData();
		int		getIdxNextData() const;
		void	printDataListFromNextData() const;
		bool	isNextData() const;

	private:
		void	moveDataList(std::vector<int>&& dataList);

	private:
		std::vector<int>	m_dataList;
		int					m_idxNextData = 0;
	};

public:
	Cluster(int numNodes, int capacityNode);

	Node&		operator[](int idxNode);
	const Node& operator[](int idxNode) const;

	void		printInfoNodes() const;
	int			getNumNodes() const { return m_nodes.size(); }
	int			getCapacityNode() const { return m_nodes[0].m_dataList.size(); }
		 
private:
	std::vector<Node>		m_nodes;
};
