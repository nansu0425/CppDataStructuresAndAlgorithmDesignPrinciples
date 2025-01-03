﻿#include "RedBlackTree.h"
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

	rbTree.Delete(4);
	rbTree.Delete(3);
	rbTree.Delete(5);
	rbTree.Delete(2);
	rbTree.Delete(1);
	rbTree.Delete(9);
	rbTree.Delete(6);
	rbTree.Delete(8);
	rbTree.Delete(0);
	rbTree.Delete(7);

	return 0;
}