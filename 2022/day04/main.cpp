#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>
#include <map>
#include <set>
#include <regex>

auto read_input()
{
	std::fstream file(advent_input().c_str());
	std::vector<std::vector<int>> assignement{};
	// assuming your file is open
	std::string line;
	std::regex helper{ "\\d+" };
	while (!file.eof())
	{
		getline(file, line);
		std::vector<int> value{};
		for (auto i = std::sregex_iterator(line.begin(), line.end(), helper); i != std::sregex_iterator(); i++)
		{
			std::smatch match = *i;
			value.push_back(std::stoi(match.str()));
		}
		assignement.push_back(value);
	}
	return assignement;
}

auto count_include = [](auto total, std::vector<int> from)
{
	if (from[0] == from[2])
		return total + 1;
	if (from[0] < from[2])
	{
		if (from[3] <= from[1])
			return total + 1;
		else
			return total;
	}
	if (from[1] <= from[3])
		return total + 1;
	else
		return total;
};

auto count_overlap = [](auto total, std::vector<int> from)
{
	if (from[0] == from[2])
		return total + 1;
	if (from[0] < from[2])
	{
		if (from[1] >= from[2])
			return total + 1;
		else
			return total;
	}
	if (from[3] >= from[0])
		return total + 1;
	else
		return total;
};

void step1()
{
	auto assignement = read_input();
	auto total = std::accumulate(assignement.begin(), assignement.end(), 0, count_include);
	std::cout << "score:" << total << std::endl;
}

void step2()
{
	auto assignement = read_input();
	auto total = std::accumulate(assignement.begin(), assignement.end(), 0, count_overlap);
	std::cout << "score:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
