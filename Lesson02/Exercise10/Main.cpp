#include <iostream>
#include <queue>
#include <vector>

struct Median
{
	std::priority_queue<int> maxHeap;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

	float get()
	{
		// 원소 개수가 짝수일 경우 가운데 두 원소의 평균값을 계산
		if (maxHeap.size() == minHeap.size())
		{
			return (maxHeap.top() + minHeap.top()) / 2.0f;
		}

		// 개수가 더 많은 힙의 루트가 중앙값
		if (maxHeap.size() < minHeap.size())
		{
			return static_cast<float>(minHeap.top());
		}
		else
		{
			return static_cast<float>(maxHeap.top());
		}
	}

	void insert(int data)
	{
		if (maxHeap.empty())
		{
			maxHeap.push(data);
		
			return;
		}

		// maxHeap과 minHeap의 개수가 같다
		if (maxHeap.size() == minHeap.size())
		{
			// data가 중앙값보다 작거나 같으면 maxHeap에 넣는다
			if (data <= get())
			{
				maxHeap.push(data);
			}
			// data가 중앙값보다 크면 minHeap에 넣는다
			else
			{
				minHeap.push(data);
			}
		}
		// maxHeap의 개수보다 minHeap의 개수가 많다
		else if (maxHeap.size() < minHeap.size())
		{
			if (get() < data)
			{
				// minHeap 루트를 maxHeap으로 옮긴다
				maxHeap.push(minHeap.top());
				minHeap.pop();

				minHeap.push(data);
			}
			else
			{
				maxHeap.push(data);
			}
		}
		// minHeap의 개수보다 maxHeap의 개수가 같거나 많다
		else
		{
			if (data < get())
			{
				// maxHeap 루트를 minHeap으로 옮긴다
				minHeap.push(maxHeap.top());
				maxHeap.pop();

				maxHeap.push(data);
			}
			else
			{
				minHeap.push(data);
			}
		}
	}
};

int main()
{
	Median med;

	float result = 0.0f;

	med.insert(1);
	result = med.get();

	med.insert(3);
	result = med.get();

	med.insert(2);
	result = med.get();

	med.insert(8);
	result = med.get();

	med.insert(9);
	result = med.get();

	med.insert(10);
	result = med.get();

	med.insert(-1);
	result = med.get();

	med.insert(-3);
	result = med.get();

	med.insert(6);
	result = med.get();
	return 0;
}
