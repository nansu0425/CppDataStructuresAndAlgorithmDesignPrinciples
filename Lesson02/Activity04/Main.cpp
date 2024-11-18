#include "FileSystem.h"

#include <iostream>

int main()
{
	FileSystem fs;

	// current directory
	std::cout << fs;

	// true
	std::cout << fs.isPath(std::string("\\world\\today"));
	std::cout << fs.isPath(std::string("\\world\\is"));
	std::cout << fs.isPath(std::string("\\world\\is\\good"));
	
	// false
	std::cout << fs.isPath(std::string("\\world\\today\\good"));
	std::cout << fs.isPath(std::string("\\good\\today\\good"));
	std::cout << fs.isPath(std::string("\\world\\is\\bye"));

	// true
	std::cout << fs.isPath(std::string("bye"));
	std::cout << fs.isPath(std::string("is\\good"));

	// false
	std::cout << fs.isPath(std::string("good"));
	std::cout << fs.isPath(std::string("is\\world"));

	return 0;
}
