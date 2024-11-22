#pragma once

#include <queue>
#include <vector>

class Cluster;

class StreamEngine
{
private:
	struct Node
	{
		int				data;
		int				idxClusterNode;

						Node(int data, int idxClusterNode);
	};

	struct ComparatorNode
	{
		bool			operator()(const Node& left, const Node& right) const { return left.data > right.data; }
	};

	using MinPriorityQueue = std::priority_queue<Node, std::vector<Node>, ComparatorNode>;

public:
	void				convertClusterData2StreamData(Cluster& cluster);
	void				printStreamData() const;

private:
	MinPriorityQueue	m_minValuesNodes;
	std::vector<int>	m_streamData;
};
