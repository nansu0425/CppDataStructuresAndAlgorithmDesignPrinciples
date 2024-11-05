#pragma once

/*------------*
 *    Node    *
 *------------*/

template<typename K, typename V>
struct Node
{
	K			key;
	V			value;
	Node*		pRight = nullptr;
	Node*		pLeft = nullptr;
	bool		isRed = true;

				Node(K key, V value);
};

template<typename K, typename V>
inline Node<K, V>::Node(K key, V value)
	: key(key)
	, value(value)
{}

/*--------------------*
 *    RedBlackTree    *
 *--------------------*/

template<typename K, typename V>
class RedBlackTree
{
private:
	using			Node = Node<K, V>;

	enum class		Rotation
	{
		None,
		Right,
		RightLeft,
		Left,
		LeftRight,
	};

public:
	void			Insert(K key, V value);

private:
	static Node*	Insert(K key, V value, Node* pCurrent);
	static Node*	RotateRight(Node* pRoot);
	static Node*	RotateLeft(Node* pRoot);
	static Node*	RotateRightLeft(Node* pRoot);
	static Node*	RotateLeftRight(Node* pRoot);
	static Node*	HandleRedRed(Node* pGrandParent, Rotation rotation);

private:
	Node*			pRoot = nullptr;
};

template<typename K, typename V>
inline void RedBlackTree<K, V>::Insert(K key, V value)
{
	pRoot = Insert(key, value, pRoot);
	
	// 루트 노드는 항상 블랙
	pRoot->isRed = false;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::Insert(K key, V value, Node* pCurrent)
{
	static bool s_isRedRed = false;
	static bool s_isRightChild = false;
	static bool s_isRotated = false;

	s_isRotated = false;

	// 현재 위치가 삽입할 위치
	if (pCurrent == nullptr)
	{
		pCurrent = new Node(key, value);

		return pCurrent;
	}

	// 오른쪽 서브트리에 삽입
	if (pCurrent->key < key)
	{
		pCurrent->pRight = Insert(key, value, pCurrent->pRight);

		// 회전이 한번이라도 발생했다면 레드 노드는 연속적으로 존재하지 않는다
		if (s_isRotated)
		{
			return pCurrent;
		}

		if (s_isRedRed)
		{
			// 왼쪽 자식 노드가 레드인지 확인
			if ((pCurrent->pLeft != nullptr) &&
				pCurrent->pLeft->isRed)
			{
				pCurrent = HandleRedRed(pCurrent, 
										Rotation::None);
			}
			else
			{
				pCurrent = HandleRedRed(pCurrent,
										(s_isRightChild)
										? Rotation::Left
										: Rotation::RightLeft);

				s_isRotated = true;
			}
		}

		// 레드 노드 연속으로 존재하는지 검사
		s_isRedRed = (pCurrent->isRed &&
					  pCurrent->pRight->isRed);

		if (s_isRedRed)
		{
			s_isRightChild = true;
		}

	}
	// 왼쪽 서브트리에 삽입
	else if (key < pCurrent->key)
	{
		pCurrent->pLeft = Insert(key, value, pCurrent->pLeft);

		// 회전이 한번이라도 발생했다면 레드 노드는 연속적으로 존재하지 않는다
		if (s_isRotated)
		{
			return pCurrent;
		}

		if (s_isRedRed)
		{
			// 오른쪽 자식 노드가 레드인지 확인
			if ((pCurrent->pRight != nullptr) &&
				pCurrent->pRight->isRed)
			{
				pCurrent = HandleRedRed(pCurrent,
										Rotation::None);
			}
			else
			{
				pCurrent = HandleRedRed(pCurrent,
										(s_isRightChild)
										? Rotation::LeftRight
										: Rotation::Right);

				s_isRotated = true;
			}
		}

		// 레드 노드 연속으로 존재하는지 검사
		s_isRedRed = (pCurrent->isRed &&
					  pCurrent->pLeft->isRed);

		if (s_isRedRed)
		{
			s_isRightChild = false;
		}
	}

	return pCurrent;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::RotateRight(Node* pRoot)
{
	Node* pNewRoot = pRoot->pLeft;
	pRoot->pLeft = pNewRoot->pRight;
	pNewRoot->pRight = pRoot;

	return pNewRoot;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::RotateLeft(Node* pRoot)
{
	Node* pNewRoot = pRoot->pRight;
	pRoot->pRight = pNewRoot->pLeft;
	pNewRoot->pLeft = pRoot;

	return pNewRoot;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::RotateRightLeft(Node* pRoot)
{
	pRoot->pRight = RotateRight(pRoot->pRight);

	return RotateLeft(pRoot);
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::RotateLeftRight(Node* pRoot)
{
	pRoot->pLeft = RotateLeft(pRoot->pLeft);

	return RotateRight(pRoot);
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::HandleRedRed(Node* pGrandParent, Rotation rotation)
{
	switch (rotation)
	{
	case Rotation::None:
		pGrandParent->isRed = true;
		pGrandParent->pLeft->isRed = false;
		pGrandParent->pRight->isRed = false;
		break;

	case Rotation::Left:
		pGrandParent = RotateLeft(pGrandParent);
		pGrandParent->isRed = false;
		pGrandParent->pLeft->isRed = true;
		break;

	case Rotation::LeftRight:
		pGrandParent = RotateLeftRight(pGrandParent);
		pGrandParent->isRed = false;
		pGrandParent->pRight->isRed = true;
		break;

	case Rotation::Right:
		pGrandParent = RotateRight(pGrandParent);
		pGrandParent->isRed = false;
		pGrandParent->pRight->isRed = true;
		break;

	case Rotation::RightLeft:
		pGrandParent = RotateRightLeft(pGrandParent);
		pGrandParent->isRed = false;
		pGrandParent->pLeft->isRed = true;
		break;

	default:
		break;
	}

	return pGrandParent;
}
