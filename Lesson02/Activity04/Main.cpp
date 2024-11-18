#include "FileSystem.h"

#include <iostream>

int main()
{
	FileSystem fs;

	// insert test code
	fs.insert("hello", "", false);
	fs.insert("world", "\\", true);
	fs.insert("good", "", false);

	fs.moveCurDir("world");

	fs.insert("bye", "", false);
	fs.insert("today", "\\world", false);
	fs.insert("is", "", true);

	fs.insert("good", "is", true);
	fs.insert("super", "\\world\\is", false);
	fs.insert("exciting", "is", false);

	fs.moveCurDir("\\");
	fs.moveCurDir("world");

	// print test code
	fs.printListPath(std::string("\\world"));
	fs.printListPath(std::string("is"));
	fs.printListPath(std::string("is\\good"));

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
