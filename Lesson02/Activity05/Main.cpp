#include "Cluster.h"

int main()
{
	const int numNodes = 10;
	const int capacityNode = 10;

	Cluster cluster = Cluster(numNodes, capacityNode);

	cluster.printInfoNodes();

	while (cluster[4].isNextData())
	{
		cluster[4].popNextData();
	}

	cluster.printInfoNodes();

	return 0;
}
