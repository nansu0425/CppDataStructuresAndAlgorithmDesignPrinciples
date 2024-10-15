#pragma once

#include <string>
#include <iostream>

struct Student
{
	std::string		name;
	int				standard;
};

std::ostream& operator<<(std::ostream& os, const Student& student);
