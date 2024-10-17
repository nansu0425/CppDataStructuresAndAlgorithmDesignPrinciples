#include <array>
#include <iostream>
#include <type_traits>
#include <utility>

template<typename... Args>
auto buildArray(Args&&... args) -> std::array<typename std::common_type<Args...>::type, sizeof... (args)>
{
	using CommonType = typename std::common_type<Args...>::type;

	return {std::forward<CommonType>((Args&&)args)...};
}

int main()
{
	auto array = buildArray(1, 0u, 'a', 3.2f, false);
	// auto array = buildArray(1, "Packet", 2.0); // 하나의 공통 타입으로 변환할 수 없어 오류 발생

	for (const auto& e : array)
	{
		std::cout << e << " ";
	}

	return 0;
}
