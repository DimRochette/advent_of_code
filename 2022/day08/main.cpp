#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>
#include <regex>
#include <deque>
#include <tuple>
#include <any>
#include <map>

template <int Tsize>
auto read_input()
{
	std::fstream file(advent_input().c_str());
	// assuming your file is open
	std::string line;
	int ret[Tsize][Tsize] = {};
	int y = 0;
	while (!file.eof())
	{
		getline(file, line);
		for (int x = 0; x < line.length(); x++)
			ret[y][x] = line[x] - '0';
		y++;
	}
	return ret;
}

template <int Tsize>
int check_tree(int forest[Tsize][Tsize], int x, int y)
{
	auto height = forest[y][x];
	bool all_of = true;
	for (int i = 0; (i < x) && (all_of); i++)
	{
		all_of = all_of && (forest[y][i] < height);
	}
	if (all_of)
		return 1;
	all_of = true;
	for (int i = x + 1; (i < Tsize) && (all_of); i++)
	{
		all_of = all_of && (forest[y][i] < height);
	}
	if (all_of)
		return 1;
	all_of = true;
	for (int j = 0; (j < y) && (all_of); j++)
	{
		all_of = all_of && (forest[j][x] < height);
	}
	if (all_of)
		return 1;
	all_of = true;
	for (int j = y + 1; (j < Tsize) && (all_of); j++)
	{
		all_of = all_of && (forest[j][x] < height);
	}
	if (all_of)
		return 1;
	return 0;
}

template <int Tsize>
int scenic(int forest[Tsize][Tsize], int x, int y)
{
	int full_total = 1;
	int total = 0;
	auto height = forest[y][x];
	for (int i = x - 1; i >= 0; i--)
	{
		if (forest[y][i] <= height)
			total++;
		if (forest[y][i] == height)
			break;
	}
	full_total = total * full_total;
	total = 0;
	for (int i = x + 1; i < Tsize; i++)
	{
		if (forest[y][i] <= height)
			total++;
		if (forest[y][i] == height)
			break;
	}
	full_total = total * full_total;
	total = 0;
	for (int j = y - 1; j >= 0; j--)
	{
		if (forest[j][x] <= height)
			total++;
		if (forest[j][x] == height)
			break;
	}
	full_total = total * full_total;
	total = 0;
	for (int j = y + 1; j < Tsize; j++)
	{
		if (forest[j][x] < height)
			total++;
		if (forest[j][x] == height)
			break;
	}
	full_total = total * full_total;
	return full_total;
}

template <int Tsize>
void step1()
{
	auto forest = read_input<Tsize>();
	auto total_visible = Tsize * 2 + (Tsize - 2) * 2;
	for (int y = 1; y < (Tsize - 1); y++)
		for (int x = 1; x < (Tsize - 1); x++)
		{
			total_visible += check_tree<Tsize>(forest, x, y);
		}
	std::cout << "step 1:" << total_visible << "\n";
}
template <int Tsize>
void step2()
{
	auto forest = read_input<Tsize>();
	auto scenic_score = 0;
	for (int y = 1; y < (Tsize - 1); y++)
		for (int x = 1; x < (Tsize - 1); x++)
		{
			scenic_score = std::max(scenic_score, scenic<Tsize>(forest, x, y));
		}

	std::cout << "step 2:" << scenic_score << "\n";

}

int main()
{
	step1<99>();
	step2<99>();
	return 0;
}
