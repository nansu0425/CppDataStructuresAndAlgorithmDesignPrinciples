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

public:
	void			Insert(K key, V value);

private:
	static Node*	Insert(K key, V value, Node* pParent, Node* pChild);
	static Node*	RotateRight(Node* pRoot);
	static Node*	RotateLeft(Node* pRoot);
	static Node*	RotateRightLeft(Node* pRoot);
	static Node*	RotateLeftRight(Node* pRoot);
	static Node*	Balance(Node* pGrandParent, Node* pParent, Node* pChild);

private:
	Node*			pRoot = nullptr;
};

template<typename K, typename V>
inline void RedBlackTree<K, V>::Insert(K key, V value)
{
	if (pRoot == nullptr)
	{
		pRoot = new Node(key, value);
	}
	else if (pRoot->key < key)
	{
		pRoot = Insert(key, value, pRoot, pRoot->pRight);
	}
	else if (key < pRoot->key)
	{
		pRoot = Insert(key, value, pRoot, pRoot->pLeft);
	}
	
	// 루트 노드는 항상 블랙
	pRoot->isRed = false;
}

template<typename K, typename V>
inline Node<K, V>* RedBlackTree<K, V>::Insert(K key, V value, Node* pParent, Node* pChild)
{
	// 자식 노드로 삽입해야 하는 경우
	if (pChild == nullptr)
	{
		if (pParent->key < key)
		{
			pParent->pRight = new Node(key, value);
		}
		else if (key < pParent->key)
		{
			pParent->pLeft = new Node(key, value);
		}

		return pParent;
	}

	bool isRightChild = (pParent->key < pChild->key);
	bool isLeftChild = (pChild->key < pParent->key);

	// 자식보다 삽입하려는 키가 큰 경우
	if (pChild->key < key)
	{
		if (isRightChild)
		{
			pParent->pRight = Insert(key, value, pChild, pChild->pRight);
			pParent = Balance(pParent, pParent->pRight, pParent->pRight->pRight);
		}
		else if (isLeftChild)
		{
			pParent->pLeft = Insert(key, value, pChild, pChild->pRight);
			pParent = Balance(pParent, pParent->pLeft, pParent->pLeft->pRight);
		}
	}
	// 자식보다 삽입하려는 키가 작은 경우
	else if (key < pChild->key)
	{
		if (isRightChild)
		{
			pParent->pRight = Insert(key, value, pChild, pChild->pLeft);
			pParent = Balance(pParent, pParent->pRight, pParent->pRight->pLeft);
		}
		else if (isLeftChild)
		{
			pParent->pLeft = Insert(key, value, pChild, pChild->pLeft);
			pParent = Balance(pParent, pParent->pLeft, pParent->pLeft->pLeft);
		}
	}

	return pParent;
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
inline Node<K, V>* RedBlackTree<K, V>::Balance(Node* pGrandParent, Node* pParent, Node* pChild)
{
	if (!(pParent->isRed && pChild->isRed))
	{
		return pGrandParent;
	}

	Node* pUncle = (pGrandParent->pLeft == pParent) 
				   ? pGrandParent->pRight 
				   : pGrandParent->pLeft;

	// Recoloring
	if ((pUncle != nullptr) && 
		(pUncle->isRed))
	{
		pParent->isRed = false;
		pUncle->isRed = false;
		pGrandParent->isRed = true;
	}
	// Rotation
	else
	{
		bool isRightParent = (pGrandParent->pRight == pParent);
		bool isRightChild = (pParent->pRight == pChild);

		if (isRightParent)
		{
			if (isRightChild)
			{
				pGrandParent = RotateLeft(pGrandParent);
			}
			else
			{
				pGrandParent = RotateRightLeft(pGrandParent);
			}

			pGrandParent->isRed = false;
			pGrandParent->pLeft->isRed = true;
		}
		else
		{
			if (isRightChild)
			{
				pGrandParent = RotateLeftRight(pGrandParent);
			}
			else
			{
				pGrandParent = RotateRight(pGrandParent);
			}

			pGrandParent->isRed = false;
			pGrandParent->pRight->isRed = true;
		}
	}

	return pGrandParent;
}
