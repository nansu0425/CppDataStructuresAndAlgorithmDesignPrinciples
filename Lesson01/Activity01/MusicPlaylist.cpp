#include "MusicPlaylist.h"

std::ostream& operator<<(std::ostream& os, const Music& music)
{
	os << "[" << music.name << "]";

	return os;
}

Music Playlist::moveNext(IteratorListMusic& cur) const
{
	cur = IteratorListMusic(m_list.getPtrHead(), cur.getPtr()->pNext);
	return cur.getPtr()->data;
}

Music Playlist::movePrev(IteratorListMusic& cur) const
{
	cur = IteratorListMusic(m_list.getPtrHead(), cur.getPtr()->pPrev);
	return cur.getPtr()->data;
}

void Playlist::insert(const IteratorListMusic& iter, const std::string& name)
{
	m_list.insert(iter, Music{name});
}

void Playlist::remove(IteratorListMusic& iter)
{
	IteratorListMusic iterRemove = iter;
	++iter;

	m_list.remove(iterRemove);
}

void Playlist::remove(const std::string& name)
{
	m_list.remove(find(name));
}

std::ostream& operator<<(std::ostream& os, const Playlist& list)
{
	for (const Music& music : list)
	{
		os << music << " ";
	}

	return os;
}
