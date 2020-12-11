#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<std::string> input;
	while (!fcin.eof())
	{
		std::string line;
		fcin >> line;
		input.push_back(line);
	}
	return input;
}

// count number of # around pos

auto adjacent(std::vector<std::string>& from, int x, int y)
{
	int count = 0;
	bool left = ((x - 1) >= 0);
	bool right = ((x + 1) < from[0].size());
	bool top = ((y - 1) >= 0);
	bool bottom = ((y + 1) < from.size());
	if ((left) && (from[y][x - 1] == '#'))
		count++;
	if ((top && left) && (from[y - 1][x - 1] == '#'))
		count++;
	if ((top) && (from[y - 1][x] == '#'))
		count++;
	if ((top && right) && (from[y - 1][x + 1] == '#'))
		count++;
	if ((right) && (from[y][x + 1] == '#'))
		count++;
	if ((right && bottom) && (from[y + 1][x + 1] == '#'))
		count++;
	if ((bottom) && (from[y + 1][x] == '#'))
		count++;
	if ((bottom && left) && (from[y + 1][x - 1] == '#'))
		count++;
	return count;
};

// increment in one direction until found or outside of range
bool seat(std::vector<std::string>& from, int x, int y, int xx, int yy)
{
	int horizontal = x + xx;
	int vertical = y + yy;
	for (; (horizontal >= 0) && (horizontal < from[0].size()) && ((vertical >= 0) && (vertical < from.size())); horizontal += xx, vertical += yy)
	{
		auto view = from[vertical][horizontal];
		if (view == 'L')
			return false;
		if (view == '#')
			return true;
	}
	return false;
}

// count number of # around multiple distances 
auto visibleadjacent(std::vector<std::string>& from, int x, int y)
{
	int count = 0;
	std::vector<std::pair<int, int>> direction{ {-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1} };
	for (auto elem : direction)
	{
		if (seat(from, x, y, elem.first, elem.second))
			count++;
	}
	return count;
};

bool generate(std::vector<std::string>& from, int maxoccupency, std::function<int(std::vector<std::string>& from, int x, int y)> fnct)
{
	bool change = false;
	std::vector<std::string> to;
	for (auto& elem : from)
		to.push_back(elem);
	for (int y = 0; y < from.size(); ++y)
	{
		for (int x = 0; x < from[0].size(); ++x)
		{
			if (from[y][x] != '.')
			{
				auto occupied = fnct(from, x, y);
				if ((occupied == 0) && (from[y][x] == 'L'))
				{
					// => #
					to[y][x] = '#';
					change = true;
				}
				if ((occupied >= maxoccupency) && (from[y][x] == '#'))
				{
					// => L
					to[y][x] = 'L';
					change = true;
				}
			}
		}
	}
	from.clear();
	for (auto& elem : to)
		from.push_back(elem);
	return change;
}

int count_occupied(std::vector<std::string>& from)
{
	int count = 0;
	for (auto& elem : from)
	{
		for (auto c : elem)
		{
			if (c == '#')
				count++;
		}
	}
	return count;
}

void step1()
{
	auto input = read_values();
	for (; generate(input, 4, adjacent););

	std::cout << "step 1:" << count_occupied(input) << std::endl;
}

void step2()
{
	auto input = read_values();
	for (; generate(input, 5, visibleadjacent););
	std::cout << "step 2:" << count_occupied(input) << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
