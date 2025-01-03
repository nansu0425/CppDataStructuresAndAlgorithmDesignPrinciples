﻿#pragma once

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
	~BinarySearchTree();

	Node*		Find(int value) const;
	void		Insert(int value);
	void		DoInorderTraversal(std::ostream& os) const;
	void		Remove(int value);
	bool		IsEmpty() const;
	void		Clear();

	static Node*	GetSuccessor(const Node* pRoot);

private:
	Node*		Find(int value, Node* pCurrent) const;
	Node*		Insert(int value, Node* pCurrent);
	void		DoInorderTraversal(std::ostream& os, const Node* pCurrent, int& numberVisits) const;
	Node*		Remove(int value, Node* pCurrent);
	Node*		Clear(Node* pCurrent);

private:
	Node*		m_pRoot = nullptr;
	int			m_numberNodes = 0;
};

std::ostream&	operator<<(std::ostream& os, const Node* pNode);
std::ostream&	operator<<(std::ostream& os, const BinarySearchTree& bst);