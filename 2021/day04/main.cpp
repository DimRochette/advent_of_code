#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <ranges>
#include <map>

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

std::string replace_str(std::string& str, const std::string& from, const std::string& to)
{
	while (str.find(from) != std::string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

auto split_to_int(std::string src)
{
	if (src.find(',') != std::string::npos)
		src = replace_str(src, ",", " ");

	std::istringstream is{ src };
	std::vector<std::string> tokens{ std::istream_iterator<std::string>(is), std::istream_iterator<std::string>() };
	std::vector<int> out;
	for (auto& elem : tokens)
	{
		out.push_back(view_to_int(elem));
	}
	return out;
}

using grid_t = std::vector<std::vector<int>>;
using grids_t = std::vector<grid_t>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<std::string> input;
	std::string tmp;
	std::getline(fcin, tmp);
	auto bingo = split_to_int(tmp);
	grid_t grid;
	grids_t out;
	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		if (tmp.length() == 0)
		{
			if (grid.size() > 0)
			{
				out.push_back(grid);
				grid.resize(0);
			}
			continue;
		}
		grid.push_back(split_to_int(tmp));
	}
	out.push_back(grid);

	return std::tuple{ bingo,out };
}

auto mark(int number, grids_t& grids)
{
	for (auto& grid : grids)
	{
		for (auto& line : grid)
		{
			std::transform(line.begin(), line.end(), line.begin(), [number](int val) {if (val == number) return (-1 - val); return val; });
		}
	}
	return grids;
}

// return winning grid
auto check(grids_t& grids, std::vector<bool> ignore)
{
	int gridcpt = 0;
	for (auto& grid : grids)
	{
		if ((ignore.size() > 0) && ignore[gridcpt] == true)
		{
			gridcpt++;
			continue;
		}
		for (auto& line : grid)
		{
			if (std::all_of(line.begin(), line.end(), [](int val) {return val < 0; }))
			{
				//line won
				return gridcpt;
			}
		}
		for (auto colid = 0; colid < grid[0].size(); colid++)
		{
			if (std::all_of(grid.begin(), grid.end(), [colid](auto& val) {return(val[colid] < 0); }))
			{
				//col won
				return gridcpt;
			}
		}
		gridcpt++;
	}
	return -1;
}

auto calc(grid_t& grid)
{
	int total = 0;
	for (auto& line : grid)
	{
		total += std::accumulate(line.begin(), line.end(), 0, [](int acc, int val) {if (val > 0) return (val + acc); else return acc; });
	}
	return total;
}

void step1()
{
	auto data = read_values();
	auto grids = std::get<1>(data);
	int winning = 0;
	for (auto elem : std::get<0>(data))
	{
		mark(elem, grids);
		auto won = check(grids, std::vector<bool>());
		if (won >= 0)
		{
			winning = calc(grids[won]) * elem;
			break;
		}
	}
	std::cout << "step 1:" << winning << std::endl;
}

void step2()
{
	auto data = read_values();
	auto grids = std::get<1>(data);
	std::vector<bool> gridwin(grids.size());
	int winning = 0;
	for (auto elem : std::get<0>(data))
	{
		mark(elem, grids);
		for (auto won = check(grids, gridwin); won >= 0; won = check(grids, gridwin))
		{
			if (gridwin[won] == false)
			{
				gridwin[won] = true;
				winning = calc(grids[won]) * elem;
			}
		}
	}
	std::cout << "step 2:" << winning << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
