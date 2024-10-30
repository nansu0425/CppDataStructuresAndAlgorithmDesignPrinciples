#pragma once

struct Node
{
	Node*	pLeft;
	Node*	pRight;
	int		data;
};

class BinarySearchTree
{
public:
	Node*	Find(int value) const;
	void	Insert(int value);
	void	DoInorderTraversal() const;
	void	Remove(int value);
	Node*	GetInorderSuccessor(Node* pPredecessor) const;
	bool	IsEmpty() const;

private:
	Node*	Find(Node* pCurrent, int value) const;
	Node*	Insert(Node* pCurrent, int value);
	void	DoInorderTraversal(Node* pRoot) const;
	Node*	Remove(Node* pRoot, int value);

private:
	Node*	m_pRoot = nullptr;
};
