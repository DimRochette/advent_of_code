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

void display(t_lines& data)
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

int computepath(const t_lines& grid)
{
	t_lines weight = {};
	weight.resize(grid.size());
	for (auto& elem : weight)
	{
		elem.resize(grid[0].size(), std::numeric_limits<int>::max());
	}

	std::vector<std::tuple<int, int>> next = { {-1,0},{1,0},{0,-1},{0,1} };
	std::deque<std::tuple<int, int>> list;
	list.push_back({ 0,0 });
	weight[0][0] = 0;
	for (; !list.empty();)
	{
		auto [x, y] = list.front();
		list.pop_front();
		for (auto [i, j] : next)
		{
			i += x;
			j += y;
			if (i < 0) continue;
			if (i >= grid[0].size()) continue;
			if (j < 0) continue;
			if (j >= grid.size()) continue;
			auto cost = weight[y][x] + grid[j][i];
			if (cost >= weight[j][i]) continue;
			weight[j][i] = cost;
			list.push_back({ i, j });
		}
	}
	return weight[grid.size() - 1][grid[0].size() - 1];
}

void copy_to(t_lines& dest, int x, int y, const t_lines& stamp)
{
	x = x * stamp[0].size();
	y = y * stamp.size();
	for (auto& elem : stamp)
	{
		std::copy(elem.begin(), elem.end(), (dest[y].begin() + x));
		y++;
	}
}

auto enlarge(const t_lines& grid)
{
	t_lines output;
	output.resize(grid.size() * 5);
	for (auto& elem : output)
	{
		elem.resize(grid[0].size() * 5);
	}
	auto stamp = grid;
	copy_to(output, 0, 0, stamp);
	for (int iter = 1; iter < 10; iter++)
	{
		std::for_each(stamp.begin(), stamp.end(), [](auto& v) {
			std::transform(v.begin(), v.end(), v.begin(), [](auto val) { return ((val + 1) <= 9) ? (val + 1) : 1; });
			});
		// diagonal copy
		for (auto x = iter, y = 0; x >= 0; x--, y++)
		{
			if ((y < 5) && (x < 5))
				copy_to(output, x, y, stamp);
		}
	}
	return output;
}

void step1()
{
	auto data = read_values();
	auto total = computepath(data);
	std::cout << "step 1:" << total << std::endl;
}

void step2()
{
	auto data = read_values();
	auto big = enlarge(data);
	auto total = computepath(big);
	std::cout << "step 2:" << total << std::endl;
}

void SmallBench(auto fnct)
{
	auto start = std::chrono::steady_clock::now();
	fnct();
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << duration << " microseconds\n";
}

int main()
{
	SmallBench(step1);
	SmallBench(step2);
	return 0;
}