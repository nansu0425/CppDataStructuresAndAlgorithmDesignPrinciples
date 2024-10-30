#pragma once

#include <iostream>

struct Node
{
	Node*		pLeft;
	Node*		pRight;
	int			data;
};

class BinarySearchTree
{
public:
	Node*		Find(int value) const;
	void		Insert(int value);
	void		DoInorderTraversal(std::ostream& os) const;
	void		Remove(int value);
	Node*		GetInorderSuccessor(Node* pPredecessor) const;
	bool		IsEmpty() const;

private:
	Node*		Find(int value, Node* pCurrent) const;
	Node*		Insert(int value, Node* pCurrent);
	void		DoInorderTraversal(std::ostream& os, Node* pCurrent, int& numberVisits) const;
	Node*		Remove(int value, Node* pRoot);

private:
	Node*		m_pRoot = nullptr;
	int			m_numberNodes = 0;
};

std::ostream&	operator<<(std::ostream& os, const Node* pNode);
std::ostream&	operator<<(std::ostream& os, const BinarySearchTree& bst);