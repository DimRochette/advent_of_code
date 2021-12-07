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

using line_t = std::tuple<std::tuple<int, int>, std::tuple<int, int>>;

auto split_to_int(std::string src)
{
	src = replace_str(src, ",", " ");
	src = replace_str(src, " -> ", " ");

	std::istringstream is{ src };
	std::vector<std::string> tokens{ std::istream_iterator<std::string>(is), std::istream_iterator<std::string>() };
	line_t out{ { view_to_int(tokens[0]), view_to_int(tokens[1])},
		{view_to_int(tokens[2]), view_to_int(tokens[3])} };
	return out;
}

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::string tmp;
	std::vector<line_t> lines;

	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		lines.push_back(split_to_int(tmp));
	}
	return lines;
}

auto draw(std::vector<line_t>& lines)
{
	std::vector<std::vector<int>> grid;
	for (auto line : lines)
	{
		auto& [p1, p2] = line;
		auto& [x1, y1] = p1;
		auto& [x2, y2] = p2;

		auto fromy = std::minmax(y1, y2);
		auto fromx = std::minmax(x1, x2);
		if (grid.size() < (fromy.second + 1))
			grid.resize(fromy.second + 1);
		if (grid[y1].size() < (fromx.second + 1))
			grid[y1].resize(fromx.second + 1);
		if (x1 == x2)
		{
			for (int i = fromy.first; i <= fromy.second; i++)
			{
				if (grid[i].size() < (x1 + 1))
					grid[i].resize(x1 + 1);
				grid[i][x1]++;
			}
		}
		else if (y1 == y2)
		{
			for (int i = fromx.first; i <= fromx.second; i++)
			{
				grid[y1][i]++;
			}
		}
		else
		{
			auto xi = (x2 > x1) ? 1 : -1;
			auto yi = (y2 > y1) ? 1 : -1;
			// diagonal
			for (int i = x1, j = y1; ; i += xi, j += yi)
			{
				if (grid[j].size() < (i + 1))
					grid[j].resize(i + 1);
				grid[j][i]++;
				if (i == x2)
					break;
			}
		}
	}
	auto cpt = 0;
	for (auto& line : grid)
	{
		for (auto val : line)
		{
			if (val > 1)
				cpt++;
		}
	}
	return cpt;
}

void step1()
{
	auto data = read_values();
	auto filter_straight = [](auto line)
	{
		auto& [p1, p2] = line;
		auto& [x1, y1] = p1;
		auto& [x2, y2] = p2;
		return (x1 != x2) && (y1 != y2);
	};
	data.erase(std::remove_if(data.begin(), data.end(), filter_straight), data.end());
	auto matrix = draw(data);
	std::cout << "step 1:" << matrix << std::endl;
}

void step2()
{
	auto data = read_values();
	auto matrix = draw(data);
	std::cout << "step 2:" << matrix << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
