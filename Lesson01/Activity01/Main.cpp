#include "MusicPlaylist.h"

int main()
{
	Playlist playlist =
	{
		Music{"Back In Black"},
		Music{"Roundabout"},
		Music{"Owner of a Lonely Heart"},
		Music{"Don't Stop Believin'"},
		Music{"Hold the Line"},
	};

	auto iter = playlist.begin();

	playlist.insert(iter, "Starman");
	
	++iter;
	++iter;

	playlist.remove(iter);

	std::cout << playlist << "\n";

	playlist.insert(iter, "White Room");
	playlist.insert(iter, "Thunderstruck");
	playlist.remove("Hold the Line");

	std::cout << playlist << "\n";

	std::cout << std::endl;
	std::cout << "Forward\n";
	for (int cntPlay = 0; cntPlay < 10; ++cntPlay)
	{
		std::cout << playlist.moveNext(iter) << "\n";
		
	}

	std::cout << std::endl;
	std::cout << "Reverse\n";
	for (int cntPlay = 0; cntPlay < 10; ++cntPlay)
	{
		std::cout << playlist.movePrev(iter) << "\n";
	}

	return 0;
}