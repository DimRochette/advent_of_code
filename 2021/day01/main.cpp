#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ranges>
#include <numeric>
#include "fileinput.h"

auto read_input()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<int> depth;
	while (!fcin.eof())
	{
		int value;
		fcin >> value;
		depth.push_back(value);
	}
	return depth;
}

auto compute_diff(std::vector<int>&& depth)
{
	std::adjacent_difference(depth.begin(), depth.end(), depth.begin());
	auto positive = [](int i) { return i > 0; };
	// ignore first
	return std::ranges::count_if(std::next(depth.begin()), depth.end(), positive);
}

void step1()
{
	std::cout << "total:" << compute_diff(read_input()) << std::endl;
}

void step2()
{
	auto depth = read_input();
	auto count = std::inner_product(std::next(depth.begin(), 3), depth.end(),
		depth.begin(), 0,
		std::plus<>{}, std::greater<>{});
	std::cout << "total:" << count << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
