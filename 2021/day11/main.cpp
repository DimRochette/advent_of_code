#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <tuple>
#include <vector>
#include <map>
#include <set>
#include <stack>

using t_lines = std::vector<std::vector<int>>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string tmp;
	while (!fcin.eof())
	{
		std::vector<int> single;
		std::getline(fcin, tmp);
		for (auto val : tmp)
		{
			single.push_back(val - '0');
		}
		lines.push_back(single);
	}
	return lines;
}

auto flash_one(t_lines& data, t_lines& mask, int i, int j)
{
	std::vector<std::tuple<int, int>> coordinates{ {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
	for (auto [x, y] : coordinates)
	{
		x += i;
		y += j;
		if ((x >= 0) && (x < data[0].size()) && (y >= 0) && (y < data.size()))
		{
			if (mask[y][x] == 0)
				data[y][x]++;
		}
	}
	return 0;
}

auto flash_day(t_lines& data, t_lines mask)
{
	// increment all 1
	for (int j = 0; j < data.size(); j++)
	{
		std::transform(data[j].begin(), data[j].end(), data[j].begin(), [](auto val) {return val + 1; });
	}
	auto newflash = 0;
	auto total = 0;
	do {
		newflash = 0;
		for (int j = 0; j < data.size(); j++)
		{
			for (int i = 0; i < data[0].size(); i++)
			{
				if (mask[j][i] == 0)
				{
					if (data[j][i] > 9)
					{
						mask[j][i] = 1;
						flash_one(data, mask, i, j);
						data[j][i] = 0;
						newflash++;
						total++;
					}
				}
			}
		}
	} while (newflash > 0);
	return total;
}

void display(t_lines& data, t_lines mask)
{
	for (auto& line : data)
	{
		for (auto val : line)
		{
			std::cout << static_cast<char>('0' + val);
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void step1()
{
	auto data = read_values();
	decltype(data) mask;
	auto total = 0;
	mask.resize(data.size());
	for (auto& elem : mask)
	{
		elem.resize(data[0].size());
	}

	for (int i = 0; i < 100; i++)
	{
		total += flash_day(data, mask);
	}
	std::cout << "step 1:" << total << std::endl;
}

void step2()
{
	auto data = read_values();
	decltype(data) mask;
	auto step = 1;
	mask.resize(data.size());
	for (auto& elem : mask)
	{
		elem.resize(data[0].size());
	}

	for (int all_flash = data.size() * data[0].size(); ; step++)
	{
		if (all_flash == flash_day(data, mask))
			break;
	}

	std::cout << "step 2:" << step << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
