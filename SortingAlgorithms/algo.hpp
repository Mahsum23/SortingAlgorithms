#pragma once

#include <atomic>

#include "util.hpp"

template <typename T>
void BubbleSort(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v.size() - i - 1; ++j)
		{
			if (stopped) return;
			if (v[j] > v[j + 1])
			{
				std::swap(v[j], v[j + 1]);
			}
		}
	}
}

template <typename T>
void BubbleSortOptimized(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	bool sorted = false;
	for (int i = 0; i < v.size() && !sorted; ++i)
	{
		sorted = true;
		for (int j = 1; j < v.size() - i; ++j)
		{
			if (stopped) return;
			if (v[j - 1] > v[j])
			{
				std::swap(v[j - 1], v[j]);
				sorted = false;
			}
		}
	}
}


template <typename T>
void InsertionSort(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	for (int i = 1; i < v.size(); ++i)
		for (int j = i; j > 0 && v[j - 1] > v[j]; --j)
		{
			if (stopped) return;
			std::swap(v[j - 1], v[j]);
		}
}


template <typename T>
void InsertionSortShift(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	for (int i = 1; i < v.size(); ++i)
	{
		int tmp = v[i];
		int j = i;
		while (j > 0 && v[j - 1] > tmp)
		{
			if (stopped) return;
			v[j] = v[j - 1];
			--j;
		}
		v[j] = tmp;
	}
}

template <typename T>
void InsertionSortBinary(std::vector<T>& v, const std::atomic_bool& stopped = false)
{

	for (int i = 1; i < v.size(); ++i)
	{
		int tmp = v[i];
		int j = i;
		int l = 0; int r = i;
		while (l <= r)
		{
			int mid = l + (r - l) / 2;
			if (v[mid] > tmp)
				r = mid - 1;
			else if (v[mid] < tmp)
				l = mid + 1;
			else
			{
				l = mid;
				break;
			}
		}
		for (int j = i; j > l; --j)
		{
			if (stopped) return;
			v[j] = v[j - 1];
		}
		v[l] = tmp;
	}
}


template <typename T>
void ShellSort(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	int n = v.size();
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; ++i)
		{
			for (int j = i; j - gap >= 0 && v[j - gap] > v[j]; --j)
			{
				if (stopped) return;
				std::swap(v[j - gap], v[j]);
			}
		}
	}
}

// Frank & Lazarus, 1960
template <typename T>
void ShellSortOptimized1(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	int n = v.size();
	int k = 2;
	for (int gap = n / k + 1; gap > 0; gap = n / k + (gap != 1))
	{
		for (int i = gap; i < n; ++i)
		{
			for (int j = i; j - gap >= 0 && v[j - gap] > v[j]; --j)
			{
				if (stopped) return;
				std::swap(v[j - gap], v[j]);
			}
		}
		k *= 2;
	}
}

// Ciura 2001 (loses to normal ShellSort, N < 100000)
// static std::vector<int> gaps{ 1, 4, 10, 23, 57, 132, 301, 701, 1750, 4375, 10937, 27343, 68359, 170898, INT_MAX };

// Sedgewick 1982 (loses to normal ShellSort, N < 100000)
//static std::vector<int> gaps{ 1, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913, 1050113, 4197377, 16783361, 67121153, 268460033, 1073790977, INT_MAX };

// Pratt 1971 (3-smooth)
static std::vector<int> gaps = GenerateSmooth(3, 100000);

template <typename T>
void ShellSortOptimized2(std::vector<T>& v, const std::atomic_bool& stopped = false)
{
	int n = v.size();

	auto it = gaps.end() - 1;
	for (int i = gaps.size() - 1; i >= 0; --i)
	{
		int gap = gaps[i];
		for (int i = gap; i < n; ++i)
		{
			for (int j = i; j - gap >= 0 && v[j - gap] > v[j]; --j)
			{
				if (stopped) return;
				std::swap(v[j - gap], v[j]);
			}
		}
	}
}

template <typename T>
void SelectionSort(std::vector<T>& arr, const std::atomic_bool& stopped = false)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		int imin = i;
		for (int j = i + 1; j < arr.size(); ++j)
		{
			if (stopped) return;
			if (arr[j] < arr[imin])
				imin = j;
		}
		std::swap(arr[i], arr[imin]);
	}
}

template<typename T>
void Heapify(std::vector<T>& arr, int node, int size)
{
	int l = 2 * node + 1;
	int r = 2 * node + 2;
	int x = node;
	if (l < size && arr[x] < arr[l]) x = l;
	if (r < size && arr[x] < arr[r]) x = r;
	if (x == node) return;
	std::swap(arr[x], arr[node]);
	Heapify(arr, x, size);
}

template <typename T>
void HeapSort(std::vector<T>& arr, const std::atomic_bool& stopped = false)
{
	for (int i = (arr.size() - 2) / 2; i >= 0; --i)
		Heapify(arr, i, arr.size());
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		if (stopped) return;
		std::swap(arr[0], arr[i]);
		Heapify(arr, 0, i);
	}
}

