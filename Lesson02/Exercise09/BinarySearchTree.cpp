#include "BinarySearchTree.h"

#include <cassert>

Node* BinarySearchTree::Find(int value) const
{
	return Find(value, m_pRoot);
}

Node* BinarySearchTree::Find(int value, Node* pCurrent) const
{
	// 찾으려는 노드가 없거나 찾았을 경우
	if ((pCurrent == nullptr) || 
		(pCurrent->data == value))
	{
		return pCurrent;
	}

	// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에서 탐색
	if (pCurrent->data < value)
	{
		pCurrent = Find(value, pCurrent->pRight);
	}
	else
	{
		pCurrent = Find(value, pCurrent->pLeft);
	}

	return pCurrent;
}

void BinarySearchTree::Insert(int value)
{
	if (IsEmpty())
	{
		m_pRoot = new Node{nullptr, nullptr, value};
		++m_numberNodes;

		return;
	}

	// 중복 값은 허용하지 않는다
	assert(m_pRoot->data != value);

	// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에 삽입
	if (m_pRoot->data < value)
	{
		m_pRoot->pRight = Insert(value, m_pRoot->pRight);
	}
	else
	{
		m_pRoot->pLeft = Insert(value, m_pRoot->pLeft);
	}
}

Node* BinarySearchTree::Insert(int value, Node* pCurrent)
{
	// 현재 노드가 삽입 위치인 경우
	if (pCurrent == nullptr)
	{
		pCurrent = new Node{nullptr, nullptr, value};
		++m_numberNodes;
	}
	else
	{
		// 중복 값은 허용하지 않는다
		assert(pCurrent->data != value);

		// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에 삽입
		if (pCurrent->data < value)
		{
			pCurrent->pRight = Insert(value, pCurrent->pRight);
		}
		else
		{
			pCurrent->pLeft = Insert(value, pCurrent->pLeft);
		}
	}

	return pCurrent;
}

void BinarySearchTree::DoInorderTraversal(std::ostream& os) const
{
	if (IsEmpty())
	{
		return;
	}

	int numberVisits = 0;
	DoInorderTraversal(os, m_pRoot, numberVisits);

	assert(numberVisits == m_numberNodes);
}

void BinarySearchTree::DoInorderTraversal(std::ostream& os, Node* pCurrent, int& numberVisits) const
{
	if (pCurrent == nullptr)
	{
		return;
	}

	DoInorderTraversal(os, pCurrent->pLeft, numberVisits);
	
	os << pCurrent;
	++numberVisits;

	// 현재 노드 방문이 마지막인 경우
	if (numberVisits == m_numberNodes)
	{
		return;
	}

	os << ", ";
	DoInorderTraversal(os, pCurrent->pRight, numberVisits);
}

std::ostream& operator<<(std::ostream& os, const Node* pNode)
{
	os << pNode->data;

	return os;
}

std::ostream& operator<<(std::ostream& os, const BinarySearchTree& bst)
{
	bst.DoInorderTraversal(os);

	return os;
}

bool BinarySearchTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}


