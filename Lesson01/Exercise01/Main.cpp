#include "DynamicArray.h"
#include "Student.h"

int main()
{
	int numStudents;
	std::cout << "1반 학생 수를 입력하세요: ";
	std::cin >> numStudents;

	DynamicArray<Student> class1(numStudents);

	for (int studentNum = 0; studentNum < numStudents; ++studentNum)
	{
		Student student;
		
		std::cout << studentNum + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		std::cin >> student.name >> student.standard;

		class1[studentNum] = student;
	}

	try
	{
		// class1[numStudents] = Student{ "John", 8 }; // 예외 처리 없다
		class1.access(numStudents) = Student{ "John", 8 }; // 예외 처리 존재
	}
	catch (...)
	{
		std::cout << "예외 발생!" << std::endl;
	}

	DynamicArray<Student> class2 = class1;
	std::cout << "1반을 복사하여 2반 생성: " << class2.convertToString() << std::endl;

	DynamicArray<Student> class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성: " << class3.convertToString() << std::endl;

	return 0;
}
