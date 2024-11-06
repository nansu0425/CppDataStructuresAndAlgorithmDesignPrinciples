#include "RedBlackTree.h"
#include "string"

int main()
{
	RedBlackTree<int, std::string> rbTree;
	rbTree.Insert(8, "8");
	rbTree.Insert(5, "5");
	rbTree.Insert(2, "2");
	rbTree.Insert(0, "0");
	rbTree.Insert(6, "6");
	rbTree.Insert(4, "4");
	rbTree.Insert(7, "7");
	rbTree.Insert(1, "1");
	rbTree.Insert(3, "3");
	rbTree.Insert(9, "9");

	rbTree.Remove(4);
	rbTree.Remove(3);
	rbTree.Remove(5);

	return 0;
}