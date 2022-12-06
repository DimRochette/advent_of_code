#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>
#include <span>
#include <set>

auto read_input()
{
	std::fstream file(advent_input().c_str());
	std::string line;
	getline(file, line);
	return line;
}

auto unique_letter_set = [](std::ranges::viewable_range auto&& r)
{
	std::set<char> buffer;
	for (auto l : r)
	{
		if (buffer.contains(l))
			return false;
		buffer.insert(l);
	}
	return true;
};

void solve(int taille)
{
	auto line = read_input();
	auto const windows = line | std::views::slide(taille);
	auto result = std::ranges::find_if(windows.begin(), windows.end(), unique_letter_set);
	auto distance = &*((*result).begin()) - line.c_str() + taille;
	std::cout << "letter position " << distance << "\n";
}

void step1()
{
	solve(4);
}

void step2()
{
	solve(14);
}

int main()
{
	step1();
	step2();

	return 0;
}
