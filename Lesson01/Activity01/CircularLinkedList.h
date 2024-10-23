#pragma once

#include <iostream>
#include <initializer_list>

template<typename T>
struct Node
{
	T		data;
	Node*	pPrev = nullptr;
	Node*	pNext = nullptr;
};

template<typename T>
class CircularLinkedList
{
private:
	using NodePtr = Node<T>*;

public:
	class Iterator
	{
	public:
		Iterator(NodePtr pHead, NodePtr pIter)
			: m_pHead(pHead)
			, m_pIter(pIter)
		{}

		T& operator*() { return m_pIter->data; }
		const T& operator*() const { return m_pIter->data; }

		Iterator& operator++() 
		{
			if (m_pIter->pNext == m_pHead)
			{
				m_pIter = nullptr;
			}
			else
			{
				m_pIter = m_pIter->pNext;
			}

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator prev = *this;

			if (m_pIter->pNext == m_pHead)
			{
				m_pIter = nullptr;
			}
			else
			{
				m_pIter = m_pIter->pNext;
			}			
			
			return prev;
		}

		bool operator==(const Iterator& other) { return (m_pIter == other.m_pIter); }
		bool operator!=(const Iterator& other) { return (m_pIter != other.m_pIter); }

		bool isHead() const { return (m_pHead == m_pIter); }
		NodePtr getPtr() const { return m_pIter; }

	private:
		NodePtr		m_pHead = nullptr;
		NodePtr		m_pIter = nullptr;
	};

	CircularLinkedList() = default;

	CircularLinkedList(const std::initializer_list<T>& list)
	{
		for (auto iter = std::rbegin(list); iter != std::rend(list); ++iter)
		{
			pushFront(*iter);
		}
	}

	~CircularLinkedList()
	{
		while (!isEmpty())
		{
			popFront();
		}
	}

	void pushFront(const T& data)
	{
		NodePtr pNode = new Node<T>{data};

		if (isEmpty())
		{
			pNode->pNext = pNode;
			pNode->pPrev = pNode;
			m_pHead = pNode;

			return;
		}

		pNode->pNext = m_pHead;
		pNode->pPrev = m_pHead->pPrev;

		m_pHead->pPrev = pNode;
		pNode->pPrev->pNext = pNode;

		m_pHead = pNode;
	}

	void insert(const Iterator& iter, const T& data)
	{
		if (iter.isHead())
		{
			pushFront(data);
			return;
		}

		NodePtr pNextInsert = iter.getPtr();
		NodePtr pInsert = new Node<T>{data, pNextInsert->pPrev, pNextInsert};

		pNextInsert->pPrev = pInsert;
		pInsert->pPrev->pNext = pInsert;
	}

	void remove(const Iterator& iter)
	{
		if (iter.isHead())
		{
			popFront();
			return;
		}

		NodePtr pRemove = iter.getPtr();
		pRemove->pPrev->pNext = pRemove->pNext;
		pRemove->pNext->pPrev = pRemove->pPrev;

		delete pRemove;
	}

	void popFront()
	{
		if (isEmpty())
		{
			return;
		}

		if (m_pHead->pNext == m_pHead)
		{
			delete m_pHead;
			m_pHead = nullptr;
			return;
		}

		m_pHead->pNext->pPrev = m_pHead->pPrev;
		m_pHead->pPrev->pNext = m_pHead->pNext;

		NodePtr pDelete = m_pHead;
		m_pHead = m_pHead->pNext;
		delete pDelete;
	}

	bool isEmpty() const { return (m_pHead == nullptr); }
	NodePtr getPtrHead() const { return m_pHead; }

	Iterator begin() const { return Iterator(m_pHead, m_pHead); }
	Iterator end() const { return Iterator(m_pHead, nullptr); }

	Iterator find(const T& data) const
	{
		Iterator iter = begin();

		while (iter != end())
		{
			if (*iter == data)
			{
				break;
			}

			++iter;
		}

		return iter;
	}

	friend std::ostream& operator<<(std::ostream& os, const CircularLinkedList& list)
	{
		for (const T& data : list)
		{
			os << data << ' ';
		}

		return os;
	}

private:
	NodePtr		m_pHead = nullptr;
};
