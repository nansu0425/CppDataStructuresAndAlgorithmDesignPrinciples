#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree bst;
	
	bst.Insert(5);
	bst.Insert(6);
	bst.Insert(1);
	bst.Insert(3);
	bst.Insert(4);
	bst.Insert(9);
	bst.Insert(9);
	bst.Insert(10);
	bst.Insert(2);
	bst.Insert(8);
	bst.Insert(7);

	std::cout << bst << std::endl;

	bst.Remove(3);
	bst.Remove(5);
	bst.Remove(10);
	bst.Remove(1);
	bst.Remove(1);

	std::cout << bst << std::endl;

	return 0;
}
