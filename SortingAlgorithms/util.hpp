#pragma once

#include <iostream>
#include <vector>

std::vector<int> GetRandomVector(size_t size, int max_el, size_t seed);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
	for (T el : v)
	{
		out << el << " ";
	}
	out << '\n';
	return out;
}

int FindMaxPrimeDiv(int n);
std::vector<int> GenerateSmooth(int p, int end);