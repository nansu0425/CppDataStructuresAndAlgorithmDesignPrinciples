#include "StreamEngine.h"
#include "Cluster.h"

#include <iostream>

StreamEngine::Node::Node(int data, int idxClusterNode)
	: data(data)
	, idxClusterNode(idxClusterNode)
{}

void StreamEngine::convertClusterData2StreamData(Cluster& cluster)
{
	m_streamData.reserve(cluster.getNumNodes() * cluster.getCapacityNode());

	// cluster 모든 node의 최솟값을 힙에 넣는다
	for (int idxClusterNode = 0; idxClusterNode < cluster.getNumNodes(); ++idxClusterNode)
	{
		m_minValuesNodes.emplace(cluster[idxClusterNode].popNextData(), idxClusterNode);
	}

	// cluster 모든 데이터를 하나의 stream data에 정렬한다
	while (!m_minValuesNodes.empty())
	{
		Node node = Node(m_minValuesNodes.top());
		m_minValuesNodes.pop();

		m_streamData.emplace_back(node.data);

		if (cluster[node.idxClusterNode].isNextData())
		{
			m_minValuesNodes.emplace(cluster[node.idxClusterNode].popNextData(), node.idxClusterNode);
		}
	}
}

void StreamEngine::printStreamData() const
{
	std::cout << "[ ";

	for (int idxData = 0; idxData < m_streamData.size(); ++idxData)
	{
		std::cout << m_streamData[idxData] << " ";
	}

	std::cout << "]";
}
