#include <string>
#include <iostream>
#include <forward_list>

struct Citizen
{
	std::string		name;
	int				age;
};

std::ostream& operator<<(std::ostream& os, const Citizen& citizen)
{
	os << "[" << citizen.name << ", " << citizen.age << "]";

	return os;
}

int main()
{
	std::forward_list<Citizen> citizens =
	{
		{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
	};

	auto copyCitizens = citizens;

	std::cout << "전체 시민들: ";
	for (const Citizen& c : citizens)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	citizens.remove_if([](const Citizen& c)
					   {
						   return (c.age < 19);
					   });

	std::cout << "투표권이 있는 시민들: ";
	for (const Citizen& c : citizens)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	copyCitizens.remove_if([](const Citizen& c)
						   {
							   return (c.age != 18);
						   });

	std::cout << "내년에 투표권이 생기는 시민들: ";
	for (const Citizen& c : copyCitizens)
	{
		std::cout << c << " ";
	}
	std::cout << std::endl;

	return 0;
}