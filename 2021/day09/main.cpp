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

using t_lines = std::vector<std::string>;
using t_hot = std::vector<std::tuple<int, int>>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string tmp;
	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		lines.push_back(tmp);
	}
	return lines;
}

auto count_min(t_lines data)
{
	t_hot hotpoints;
	auto count = 0;
	for (int j = 0; j < data.size(); j++)
	{
		for (int i = 0; i < data[0].size(); i++)
		{
			if (i > 0)
			{
				if (data[j][i - 1] <= data[j][i]) continue;
			}
			if ((i + 1) < data[0].size())
			{
				if (data[j][i + 1] <= data[j][i]) continue;
			}
			if (j > 0)
			{
				if (data[j - 1][i] <= data[j][i]) continue;
			}
			if ((j + 1) < data.size())
			{
				if (data[j + 1][i] <= data[j][i]) continue;
			}
			count += (data[j][i] - '0') + 1;
			hotpoints.push_back({ i,j });
		}
	}
	return std::tuple<int, t_hot>{count, hotpoints};
}

auto check_one(t_lines& data, t_lines& mask, int i, int j)
{
	if (mask[j][i] != '\0')
		return 0;
	mask[j][i] = 1;
	auto count = 0;
	if (i > 0)
	{
		if (data[j][i - 1] < '9')
		{
			count += check_one(data, mask, i - 1, j);
		}

	}
	if ((i + 1) < data[0].size())
	{
		if (data[j][i + 1] < '9')
		{
			count += check_one(data, mask, i + 1, j);
		}
	}
	if (j > 0)
	{
		if (data[j - 1][i] < '9')
		{
			count += check_one(data, mask, i, j - 1);
		}

	}
	if ((j + 1) < data.size())
	{
		if (data[j + 1][i] < '9')
		{
			count += check_one(data, mask, i, j + 1);
		}
	}
	return count + 1;
}

auto groups(t_lines& data, t_hot hotpoints)
{
	t_lines mask(data.size());
	std::vector<int> clouds;
	for (auto& elem : mask)
	{
		elem.resize(data[0].size());
	}
	for (auto& elem : hotpoints)
	{
		auto& [i, j] = elem;
		if (mask[j][i] != '\0') continue;
		auto total = check_one(data, mask, i, j);
		clouds.push_back(total);
	}
	return clouds;
}

void step1()
{
	auto data = read_values();
	auto [count, hot] = count_min(data);

	std::cout << "step 1:" << count << std::endl;
}

void step2()
{
	auto data = read_values();
	auto [count, hot] = count_min(data);
	auto res = groups(data, hot);
	std::partial_sort(res.begin(), res.begin() + 3, res.end(), [](auto a, auto b) {return b < a; });
	std::cout << "step 2:" << res[0] * res[1] * res[2] << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
