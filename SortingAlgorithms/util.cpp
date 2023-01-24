#include <random>
#include <functional>

#include "util.hpp"

std::vector<int> GetRandomVector(size_t size, int max_el, size_t seed)
{
	std::vector<int> res(size);
	auto randint = std::bind(std::uniform_int_distribution<int>(1, max_el), std::mt19937(seed));
	for (size_t i = 0; i < size; ++i)
	{
		res[i] = randint();
	}
	return res;
}

int FindMaxPrimeDiv(int n)
{
	if (n == 1) return 1;
	int res = -1;
	while (n % 2 == 0)
	{
		n /= 2;
		res = 2;
	}
	int r = int(std::pow(n, 0.5)) + 1;
	for (int i = 3; i < r; i += 2)
	{
		while (n % i == 0)
		{
			res = i;
			n /= i;
		}
	}
	res = std::max(n, res);
	return res;
}

std::vector<int> GenerateSmooth(int p, int end)
{
	std::vector<int> res{ 1 };
	for (int i = 2; i < end + 1; ++i)
	{
		if (FindMaxPrimeDiv(i) <= p)
			res.push_back(i);
	}
	return res;
}



