#pragma once

/*------------*
 *    Node    *
 *------------*/

template<typename K, typename V>
struct Node
{
	enum class	Color
	{
		red,
		black,
		redBlack,
		blackBlack,
		nilBlack,
	};

	K			key;
	V			value;
	Node*		pRight = nullptr;
	Node*		pLeft = nullptr;
	Color		color = Color::red;

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
		none,
		right,
		rightLeft,
		left,
		leftRight,
	};

public:
					~RedBlackTree();

	void			Insert(K key, V value);
	void			Delete(K key);
	void			Clear();

private:
	Node*			Insert(K key, V value, Node* pCurrent);
	Node*			Delete(K key, Node* pCurrent);
	void			Clear(Node* pCurrent);

	static Node*	RotateRight(Node* pRoot);
	static Node*	RotateLeft(Node* pRoot);
	static Node*	RotateRightLeft(Node* pRoot);
	static Node*	RotateLeftRight(Node* pRoot);
	static Node*	HandleConsecutiveReds(Node* pGrandParent, Rotation rotation);
	static Node*	GetSuccessor(Node* pRoot);
	static Node*	AddExtraBlack(Node* pCurrent, Node* pChild, bool& isDoubleBlack);
	static Node*	HandleDoubleBlack(Node* pGrandParent, bool& isDoubleBlack);

private:
	Node*			m_pRoot = nullptr;
	bool			m_isConsecutiveReds = false;
	bool			m_isConsecutiveRedsRight = false;
	bool			m_isRotated = false;
	bool			m_isDoubleBlack = false;
};

template<typename K, typename V>
inline RedBlackTree<K, V>::~RedBlackTree()
{
	Clear();
}

template<typename K, typename V>
inline void RedBlackTree<K, V>::Insert(K key, V value)
{
	m_isRotated = false;

	m_pRoot = Insert(key, value, m_pRoot);
	
	// 루트 노드는 항상 블랙
	m_pRoot->color = Node::Color::black;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::Insert(K key, V value, Node* pCurrent)
{
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
		if (m_isRotated)
		{
			return pCurrent;
		}

		if (m_isConsecutiveReds)
		{
			// 왼쪽 자식 노드가 레드인지 확인
			if ((pCurrent->pLeft != nullptr) &&
				(pCurrent->color == Node::Color::red))
			{
				pCurrent = HandleConsecutiveReds(pCurrent, 
												 Rotation::none);
			}
			else
			{
				pCurrent = HandleConsecutiveReds(pCurrent,
												 (m_isConsecutiveRedsRight)
												 ? Rotation::left
												 : Rotation::rightLeft);

				m_isRotated = true;
			}
		}

		// 레드 노드 연속으로 존재하는지 검사
		m_isConsecutiveReds = ((pCurrent->color == Node::Color::red) &&
							   (pCurrent->pRight->color == Node::Color::red));

		if (m_isConsecutiveReds)
		{
			m_isConsecutiveRedsRight = true;
		}

	}
	// 왼쪽 서브트리에 삽입
	else if (key < pCurrent->key)
	{
		pCurrent->pLeft = Insert(key, value, pCurrent->pLeft);

		// 회전이 한번이라도 발생했다면 레드 노드는 연속적으로 존재하지 않는다
		if (m_isRotated)
		{
			return pCurrent;
		}

		if (m_isConsecutiveReds)
		{
			// 오른쪽 자식 노드가 레드인지 확인
			if ((pCurrent->pRight != nullptr) &&
				(pCurrent->pRight->color == Node::Color::red))
			{
				pCurrent = HandleConsecutiveReds(pCurrent,
												 Rotation::none);
			}
			else
			{
				pCurrent = HandleConsecutiveReds(pCurrent,
												 (m_isConsecutiveRedsRight)
												 ? Rotation::leftRight
												 : Rotation::right);

				m_isRotated = true;
			}
		}

		// 레드 노드 연속으로 존재하는지 검사
		m_isConsecutiveReds = ((pCurrent->color == Node::Color::red) &&
							   (pCurrent->pLeft->color == Node::Color::red));

		if (m_isConsecutiveReds)
		{
			m_isConsecutiveRedsRight = false;
		}
	}

	return pCurrent;
}

template<typename K, typename V>
inline void RedBlackTree<K, V>::Delete(K key)
{
	if (m_pRoot == nullptr)
	{
		return;
	}
	
	m_pRoot = Delete(key, m_pRoot);
	
	// 루트 노드는 항상 블랙
	m_pRoot->color = Node::Color::black;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::Delete(K key, Node* pCurrent)
{
	// 삭제하려는 키가 트리에 없는 경우
	if (pCurrent == nullptr)
	{
		return pCurrent;
	}

	// 오른쪽 서브트리에서 삭제 키 탐색
	if (pCurrent->key < key)
	{
		pCurrent->pRight = Delete(key, pCurrent->pRight);
		pCurrent = HandleDoubleBlack(pCurrent, m_isDoubleBlack);

		return pCurrent;
	}
	// 왼쪽 서브트리에서 삭제 키 탐색
	else if (key < pCurrent->key)
	{
		pCurrent->pLeft = Delete(key, pCurrent->pLeft);
		pCurrent = HandleDoubleBlack(pCurrent, m_isDoubleBlack);

		return pCurrent;
	}

	const bool isLeftChild = (pCurrent->pLeft != nullptr);
	const bool isRightChild = (pCurrent->pRight != nullptr);

	// 삭제하려는 노드의 자식이 두 개인 경우
	if (isLeftChild && isRightChild)
	{
		Node* pSuccessor = GetSuccessor(pCurrent);

		pCurrent->key = pSuccessor->key;
		pCurrent->value = pSuccessor->value;
		pCurrent->pRight = Delete(pSuccessor->key, pCurrent->pRight);
		pCurrent = HandleDoubleBlack(pCurrent, m_isDoubleBlack);
	}
	else
	{
		Node* pChild = (isLeftChild)
						? pCurrent->pLeft
						: pCurrent->pRight;

		switch (pCurrent->color)
		{
		// 삭제할 노드가 red면 바로 삭제
		case Node::Color::red:
			delete pCurrent;
			pCurrent = pChild;
			break;

		// 삭제할 노드가 black이면 extra black을 붙인다
		case Node::Color::black:
			pCurrent = AddExtraBlack(pCurrent, pChild, m_isDoubleBlack);
			break;

		default:
			break;
		}
	}

	return pCurrent;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::AddExtraBlack(Node* pCurrent, Node* pChild, bool& isDoubleBlack)
{
	// leaf 노드인 경우 nil노드가 되면서 black이 붙는다
	if (pChild == nullptr)
	{
		pCurrent->color = Node::Color::nilBlack;
		isDoubleBlack = true;

		return pCurrent;
	}

	// 현재 노드 삭제 후 자식 노드로 대체
	delete pCurrent;
	pCurrent = pChild;

	switch (pCurrent->color)
	{
	// red에 extra blakc이 붙는 경우 black으로 바꿔주면 RB 트리 속성이 유지된다
	case Node::Color::red:
		pCurrent->color = Node::Color::black;
		isDoubleBlack = false;
		break;

	case Node::Color::black:
		pCurrent->color = Node::Color::blackBlack;
		isDoubleBlack = true;
		break;

	default:
		break;
	}

	return pCurrent;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::HandleDoubleBlack(Node* pGrandParent, bool& isDoubleBlack)
{
	if (!isDoubleBlack)
	{
		return pGrandParent;
	}

	// TODO: Double Black 처리 로직 구현

	isDoubleBlack = false;

	return pGrandParent;
}

template<typename K, typename V>
inline void RedBlackTree<K, V>::Clear()
{
	Clear(m_pRoot);

	m_pRoot = nullptr;
}

template<typename K, typename V>
inline void RedBlackTree<K, V>::Clear(Node* pCurrent)
{
	if (pCurrent == nullptr)
	{
		return;
	}

	Clear(pCurrent->pRight);
	Clear(pCurrent->pLeft);

	delete pCurrent;
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
inline Node<K, V>* RedBlackTree<K, V>::HandleConsecutiveReds(Node* pGrandParent, Rotation rotation)
{
	switch (rotation)
	{
	case Rotation::none:
		pGrandParent->color = Node::Color::red;
		pGrandParent->pLeft->color = Node::Color::black;
		pGrandParent->pRight->color = Node::Color::black;
		break;

	case Rotation::left:
		pGrandParent = RotateLeft(pGrandParent);
		pGrandParent->color = Node::Color::black;
		pGrandParent->pLeft->color = Node::Color::red;
		break;

	case Rotation::leftRight:
		pGrandParent = RotateLeftRight(pGrandParent);
		pGrandParent->color = Node::Color::black;
		pGrandParent->pRight->color = Node::Color::red;
		break;

	case Rotation::right:
		pGrandParent = RotateRight(pGrandParent);
		pGrandParent->color = Node::Color::black;
		pGrandParent->pRight->color = Node::Color::red;
		break;

	case Rotation::rightLeft:
		pGrandParent = RotateRightLeft(pGrandParent);
		pGrandParent->color = Node::Color::black;
		pGrandParent->pLeft->color = Node::Color::red;
		break;

	default:
		break;
	}

	return pGrandParent;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::GetSuccessor(Node* pRoot)
{
	Node* pSuccessor = pRoot->pRight;

	if (pSuccessor == nullptr)
	{
		return pSuccessor;
	}

	while (pSuccessor->pLeft != nullptr)
	{
		pSuccessor = pSuccessor->pLeft;
	}

	return pSuccessor;
}
