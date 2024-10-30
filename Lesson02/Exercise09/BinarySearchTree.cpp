#include "BinarySearchTree.h"

#include <cassert>

Node* BinarySearchTree::Find(int value) const
{
	return Find(m_pRoot, value);
}

Node* BinarySearchTree::Find(Node* pCurrent, int value) const
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
		pCurrent = Find(pCurrent->pRight, value);
	}
	else
	{
		pCurrent = Find(pCurrent->pLeft, value);
	}

	return pCurrent;
}

void BinarySearchTree::Insert(int value)
{
	if (IsEmpty())
	{
		m_pRoot = new Node{nullptr, nullptr, value};
		return;
	}

	// 중복 값은 허용하지 않는다
	assert(m_pRoot->data != value);

	// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에 삽입
	if (m_pRoot->data < value)
	{
		m_pRoot->pRight = Insert(m_pRoot->pRight, value);
	}
	else
	{
		m_pRoot->pLeft = Insert(m_pRoot->pLeft, value);
	}
}

Node* BinarySearchTree::Insert(Node* pCurrent, int value)
{
	// 현재 노드가 삽입 위치인 경우
	if (pCurrent == nullptr)
	{
		pCurrent = new Node{nullptr, nullptr, value};
	}
	else
	{
		// 중복 값은 허용하지 않는다
		assert(pCurrent->data != value);

		// 값 비교 후 왼쪽 혹은 오른쪽 서브트리에 삽입
		if (pCurrent->data < value)
		{
			pCurrent->pRight = Insert(pCurrent->pRight, value);
		}
		else
		{
			pCurrent->pLeft = Insert(pCurrent->pLeft, value);
		}
	}

	return pCurrent;
}

bool BinarySearchTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}


