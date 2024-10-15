#include "Student.h"

std::ostream& operator<<(std::ostream& os, const Student& student)
{
	os << "[" << student.name << ", " << student.standard << "]";

	return os;
}
