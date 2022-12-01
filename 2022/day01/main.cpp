#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>

auto read_input()
{
	std::fstream file(advent_input().c_str());
	std::vector<std::vector<int>> cal{ {} };
	// assuming your file is open
	std::string line;
	while (!file.eof())
	{
		getline(file, line);
		if (line.length() == 0)
		{
			cal.push_back({});
		}
		else
		{
			int val = 0;
			val = std::stoi(line);
			cal.back().push_back(val);
		}

	}
	return cal;
}



void step1()
{
	auto cal = read_input();
	auto values = cal | std::views::as_rvalue;
	std::vector<int> sums;
	std::ranges::for_each(values, [&sums](auto elem) { sums.push_back(std::accumulate(elem.begin(), elem.end(), 0)); });
	std::cout << "maximum:" << std::ranges::max(sums) << std::endl;
}

void step2()
{
	auto cal = read_input();
	auto values = cal | std::views::as_rvalue;
	std::vector<int> sums;
	std::ranges::for_each(values, [&sums](auto elem) { sums.push_back(std::accumulate(elem.begin(), elem.end(), 0)); });
	std::ranges::partial_sort(sums.begin(), sums.begin() + 3, sums.end(), std::greater{});
	std::cout << "maximum 3:" << std::accumulate(sums.begin(), sums.begin() + 3, 0) << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
