#pragma once

namespace std
{
	template<class T>
	class initializer_list;
}

struct Node
{
	int		data = 0;
	Node*	next = nullptr;
};

class SinglyLinkedList
{
public:
	using NodePtr = Node*;

	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(NodePtr ptr)
			: m_ptr(ptr)
		{}

		int&		operator*() { return m_ptr->data; }
		bool		operator==(const Iterator& other) { return (m_ptr == other.m_ptr); }
		bool		operator!=(const Iterator& other) { return (m_ptr != other.m_ptr); }
		Iterator&	operator++(); // 선행 증가
		Iterator	operator++(int); // 후행 증가
		
		NodePtr		get() { return m_ptr; }

	private:
		NodePtr		m_ptr = nullptr;
	};

public:
	SinglyLinkedList() = default;
	SinglyLinkedList(const SinglyLinkedList& other);
	SinglyLinkedList(const std::initializer_list<int>& list);
	~SinglyLinkedList();

	void		pushFront(int data);
	void		popFront();

	Iterator	begin() { return Iterator(m_pHead); }
	Iterator	end() { return Iterator(); }
	Iterator	begin() const { return Iterator(m_pHead); }
	Iterator	end() const { return Iterator(); }

private:
	NodePtr		m_pHead = nullptr;
};
