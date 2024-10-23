#pragma once

#include "CircularLinkedList.h"

#include <string>
#include <initializer_list>

struct Music
{
	std::string name;

	bool operator==(const Music& other) { return (name == other.name); }

	friend std::ostream& operator<<(std::ostream& os, const Music& music);
};

class Playlist
{
public:
	using ListMusic				= CircularLinkedList<Music>;
	using IteratorListMusic		= ListMusic::Iterator;

	Playlist() = default;
	Playlist(const std::initializer_list<Music>& list)
		: m_list(list)
	{}

	Music	moveNext(IteratorListMusic& cur) const;
	Music	movePrev(IteratorListMusic& cur) const;

	void	insert(const IteratorListMusic& iter, const std::string& name);
	void	remove(IteratorListMusic& iter);
	void	remove(const std::string& name);
	
	IteratorListMusic		find(const std::string& name) const { return m_list.find(Music{name}); }
	IteratorListMusic		begin() const { return m_list.begin(); }
	IteratorListMusic		end() const { return m_list.end(); }

	friend std::ostream&	operator<<(std::ostream& os, const Playlist& list);

private:
	ListMusic	m_list;
};
