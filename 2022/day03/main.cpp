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

auto read_input()
{
	std::fstream file(advent_input().c_str());
	std::vector<std::string> bags;
	// assuming your file is open
	std::string line;
	while (!file.eof())
	{
		getline(file, line);
		bags.push_back(line);
	}
	return bags;
}

char inter(std::string_view vleft, std::string_view vright)
{
	std::string left(vleft);
	std::string right(vright);
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	std::vector<char> out;
	std::ranges::set_intersection(left, right, std::back_inserter(out));
	return out[0];
}

int score(char letter)
{
	if ((letter >= 'a') && (letter <= 'z'))
		return (letter - 'a' + 1);
	else
		return (letter - 'A' + 27);
}

void step1()
{
	auto bags = read_input();
	std::vector<char> items;
	std::ranges::for_each(bags, [&items](auto& elem) { items.push_back(inter(std::string_view(elem.begin(), elem.begin() + elem.length() / 2), std::string_view(elem.begin() + elem.length() / 2, elem.end()))); });
	auto total = std::accumulate(items.begin(), items.end(), 0, [](auto total, auto elem) {	return (total + score(elem)); });

	std::cout << "score:" << total << std::endl;
}

auto intersect_subrange = [](auto total, std::ranges::viewable_range auto&& r)
{
	std::vector<std::string> bags;
	for (auto elem : r)
	{
		std::sort(elem.begin(), elem.end());
		bags.push_back(elem);
	}
	std::string inter01;
	std::string out;
	std::ranges::set_intersection(bags[0], bags[1], std::back_inserter(inter01));
	std::ranges::set_intersection(bags[2], inter01, std::back_inserter(out));
	return total + score(out[0]);
};

void step2()
{
	auto bags = read_input();
	auto groups = bags | std::views::chunk(3);
	auto total = std::accumulate(groups.begin(), groups.end(), 0, intersect_subrange);

	std::cout << "score:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
