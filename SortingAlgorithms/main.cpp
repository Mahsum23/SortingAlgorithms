#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <thread>
#include <future>


#include "algo.hpp"
#include "util.hpp"
#include "LogDuration.hpp"

using namespace std;
using namespace chrono_literals;

static size_t MAX_ELEM = 1000;
static auto TIME_LIMIT = 2min;

template <typename T = int>
bool SortTimeLimiter(void (*sort)(vector<T>&, const atomic_bool&), vector<T>& arg)
{
	atomic_bool stop_token{ false };
	auto fut = async(sort, ref(arg), cref(stop_token));
	if (fut.wait_for(TIME_LIMIT) != future_status::ready)
	{
		stop_token = true;
		fut.get();
		return false;
	}
	return true;
}

void TestSort(size_t array_size)
{
	size_t seed = time(0);

	{
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);

		LOG_DURATION("", cout);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		cout << "STDSort (size = " << array_size << ")";
	}

	{
		const string& algo_name = "BubbleSort";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(BubbleSort, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "BubbleSortOptimized";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(BubbleSortOptimized, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "SelectionSort";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(SelectionSort, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "InsertionSort";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(InsertionSort, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "InsertionSortShift";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(InsertionSortShift, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "InsertionSortBinary";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(InsertionSortBinary, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "ShellSort";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(ShellSort, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "ShellSortOptimized1";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(ShellSortOptimized1, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "ShellSortOptimized2";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(ShellSortOptimized2, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

	{
		const string& algo_name = "HeapSort";
		auto arr = GetRandomVector(array_size, MAX_ELEM, seed);
		auto arr_sorted = [arr]() mutable { sort(arr.begin(), arr.end()); return arr; }();
		bool finished = false;
		stringstream ss;
		{
			LOG_DURATION("", ss);
			finished = SortTimeLimiter(HeapSort, arr);
		}
		if (finished && (arr == arr_sorted))
			cout << algo_name << " (size = " << array_size << "): PASSED" << ss.str();
		else if (!finished)
			cout << algo_name << " (size = " << array_size << "): TIMEOUT" << endl;
		else
			cout << algo_name << " (size = " << array_size << "): FAILED" << endl;
	}

}

int main()
{
	for (int i = 0, size = 100; i < 5; ++i)
	{
		TestSort(size);
		size *= 10;
		cout << string(50, '-') << endl;
	}

	cin.get();
}