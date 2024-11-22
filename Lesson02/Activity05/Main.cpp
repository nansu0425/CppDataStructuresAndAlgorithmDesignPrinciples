#include "Cluster.h"
#include "StreamEngine.h"

int main()
{
	const int numNodes = 10;
	const int capacityNode = 10;

	Cluster cluster = Cluster(numNodes, capacityNode);

	cluster.printInfoNodes();

	StreamEngine streamEng;

	streamEng.convertClusterData2StreamData(cluster);
	streamEng.printStreamData();

	std::cout << std::endl;

	cluster.printInfoNodes();

	return 0;
}
