#include "BinarySearchTree.h"

#include <cassert>

BinarySearchTree::~BinarySearchTree()
{
	Clear();
}

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

	// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에 삽입
	if (m_pRoot->data < value)
	{
		m_pRoot->pRight = Insert(value, m_pRoot->pRight);
	}
	else if (value < m_pRoot->data)
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

		return pCurrent;
	}

	// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에 삽입
	if (pCurrent->data < value)
	{
		pCurrent->pRight = Insert(value, pCurrent->pRight);
	}
	else if (value < pCurrent->data)
	{
		pCurrent->pLeft = Insert(value, pCurrent->pLeft);
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

void BinarySearchTree::Remove(int value)
{
	assert(!IsEmpty());

	m_pRoot = Remove(value, m_pRoot);
}

Node* BinarySearchTree::Remove(int value, Node* pCurrent)
{
	// value 값을 가진 노드가 트리에 없는 경우
	if (pCurrent == nullptr)
	{
		return pCurrent;
	}

	// 현재 노드가 삭제하려는 노드가 아닌 경우
	if (pCurrent->data < value)
	{
		pCurrent->pRight = Remove(value, pCurrent->pRight);
		return pCurrent;
	}
	else if (value < pCurrent->data)
	{
		pCurrent->pLeft = Remove(value, pCurrent->pLeft);
		return pCurrent;
	}

	bool bLeft = (pCurrent->pLeft != nullptr);
	bool bRight = (pCurrent->pRight != nullptr);

	// 삭제할 노드의 자식이 없는 경우
	if (!bLeft && !bRight)
	{
		delete pCurrent;
		--m_numberNodes;

		pCurrent = nullptr;
	}
	// 삭제할 노드의 자식이 하나인 경우
	else if (bLeft != bRight)
	{
		Node* pDel = pCurrent;
		pCurrent = bLeft ?
				   pCurrent->pLeft :
				   pCurrent->pRight;

		delete pDel;
		--m_numberNodes;
	}
	// 삭제할 노드의 자식이 두 개인 경우
	else
	{
		Node* pSuccessor = GetSuccessor(pCurrent);
		
		pCurrent->data = pSuccessor->data;
		pCurrent->pRight = Remove(pSuccessor->data, pCurrent->pRight);
	}

	return pCurrent;
}

void BinarySearchTree::DoInorderTraversal(std::ostream& os, const Node* pCurrent, int& numberVisits) const
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

Node* BinarySearchTree::GetSuccessor(const Node* pRoot)
{
	assert(pRoot != nullptr);

	Node* pCurrent = pRoot->pRight;

	if (pCurrent == nullptr)
	{
		return pCurrent;
	}

	// 루트 노드의 오른쪽 서브트리에서 가장 작은 값을 갖는 노드를 찾는다
	while (pCurrent->pLeft != nullptr)
	{
		pCurrent = pCurrent->pLeft;
	}

	return pCurrent;
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

void BinarySearchTree::Clear()
{
	m_pRoot = Clear(m_pRoot);

	assert(IsEmpty() &&
		   (m_numberNodes == 0));
}

Node* BinarySearchTree::Clear(Node* pCurrent)
{
	if (pCurrent == nullptr)
	{
		return pCurrent;
	}

	pCurrent->pLeft = Clear(pCurrent->pLeft);
	pCurrent->pRight = Clear(pCurrent->pRight);
	
	delete pCurrent;
	--m_numberNodes;
	pCurrent = nullptr;

	return pCurrent;
}
