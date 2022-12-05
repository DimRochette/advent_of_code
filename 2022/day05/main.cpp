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

void step1()
{
	auto assignement = read_input();
	auto total = 1;
	std::cout << "score:" << total << std::endl;
}

void step2()
{
	auto assignement = read_input();
	auto total = 2;
	//543 too low
	std::cout << "score:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
