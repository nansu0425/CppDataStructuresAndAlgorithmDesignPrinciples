#include <iostream>
#include <vector>
#include <forward_list>
#include <string>

int main()
{
	std::vector<std::string> vecWinners =
	{
		"Lewis Hamilton",
		"Lewis Hamilton",
		"Nico Roseberg",
		"Sebastian Vettel",
		"Lewis Hamilton",
		"Sebastian Vettel",
		"Sebastian Vettel",
		"Sebastian Vettel",
		"Fernando Alonso",
	};

	auto iterVec = vecWinners.begin();
	std::cout << "가장 최근 우승자: " << *iterVec << "\n";

	iterVec += 8; // 상수 시간
	std::cout << "8년 전 우승자: " << *iterVec << "\n";

	std::advance(iterVec, -3); // 상수 시간
	std::cout << "그 후 3년 뒤 우승자: " << *iterVec << "\n";

	std::forward_list<std::string> liWinners(vecWinners.begin(), vecWinners.end());

	auto iterLi = liWinners.begin();
	std::cout << "가장 최근 우승자: " << *iterLi << "\n";

	std::advance(iterLi, 5); // 선형 시간
	std::cout << "5년 전 우승자: " << *iterLi << "\n";

	// std::advance(iterLi, -2); // forward_list는 singly linked list이므로 이전 노드로 이동 불가능

	return 0;
}