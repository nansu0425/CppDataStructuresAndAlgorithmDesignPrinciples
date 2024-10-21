#include "SinglyLinkedList.h"

#include <initializer_list>
#include <algorithm>

SinglyLinkedList::Iterator& SinglyLinkedList::Iterator::operator++()
{
	m_ptr = m_ptr->next;
	return *this;
}

SinglyLinkedList::Iterator SinglyLinkedList::Iterator::operator++(int)
{
	Iterator cur = *this;
	m_ptr = m_ptr->next;
	return cur;
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other)
{
	if (other.m_pHead == nullptr)
	{
		return;
	}

	m_pHead = new Node{other.m_pHead->data, nullptr};
	
	Iterator iterThis = begin();
	Iterator iterOther = other.begin();

	++iterOther;

	while (iterOther != other.end())
	{
		iterThis.get()->next = new Node{*iterOther, nullptr};

		++iterThis;
		++iterOther;
	}
}

SinglyLinkedList::SinglyLinkedList(const std::initializer_list<int>& list)
{
	for (auto revIter = std::rbegin(list); revIter != std::rend(list); ++revIter)
	{
		pushFront(*revIter);
	}
}

SinglyLinkedList::~SinglyLinkedList()
{
	while (m_pHead != nullptr)
	{
		popFront();
	}
}

void SinglyLinkedList::pushFront(int data)
{
	NodePtr pNode = new Node{data, m_pHead};
	m_pHead = pNode;
}

void SinglyLinkedList::popFront()
{
	if (m_pHead == nullptr)
	{
		return;
	}

	NodePtr pDelete = m_pHead;
	m_pHead = m_pHead->next;
	delete pDelete;
}
