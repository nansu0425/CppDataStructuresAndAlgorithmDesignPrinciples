#include "Cluster.h"

#include <cassert>
#include <utility>
#include <random>
#include <algorithm>

int Cluster::Node::popNextData()
{
	assert(isNextData());

	int nextData = m_dataList[m_idxNextData];
	++m_idxNextData;

	return nextData;
}

int Cluster::Node::getIdxNextData() const
{
	return m_idxNextData;
}

void Cluster::Node::moveDataList(std::vector<int>&& dataList)
{
	m_dataList = std::move(dataList);
	std::sort(m_dataList.begin(), m_dataList.end());
}

void Cluster::Node::printDataListFromNextData() const
{
	std::cout << "[ ";

	for (int idxData = m_idxNextData; idxData < m_dataList.size(); ++idxData)
	{
		std::cout << m_dataList[idxData] << " ";
	}

	std::cout << "]";
}

bool Cluster::Node::isNextData() const
{
	return (m_idxNextData < m_dataList.size());
}

Cluster::Cluster(int numNodes, int capacityNode)
	: m_nodes(std::vector<Node>(numNodes))
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> distData(1, 100);

	// 무작위 값을 가지는 데이터 리스트 생성 후 노드에 전달
	for (int idxNode = 0; idxNode < numNodes; ++idxNode)
	{
		std::vector<int> dataList = std::vector<int>(capacityNode);

		for (int& data : dataList)
		{
			data = distData(rng);
		}

		m_nodes[idxNode].moveDataList(std::move(dataList));
	}
}

Cluster::Node& Cluster::operator[](int idxNode)
{
	return m_nodes[idxNode];
}

const Cluster::Node& Cluster::operator[](int idxNode) const
{
	return m_nodes[idxNode];
}

void Cluster::printInfoNodes() const
{
	for (int idxNode = 0; idxNode < m_nodes.size(); ++idxNode)
	{
		std::cout << "Node " << idxNode << ": ";
		m_nodes[idxNode].printDataListFromNextData();
		std::cout << std::endl;
	}
}
