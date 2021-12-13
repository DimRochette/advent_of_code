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

using t_point = std::tuple<int, int>;
using t_points = std::vector<t_point>;
using t_folds = std::vector<t_point>;

std::string replace_str(std::string& str, const std::string& from, const std::string& to)
{
	while (str.find(from) != std::string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::string tmp;
	t_points points;
	t_folds folds;
	while (!fcin.eof())
	{
		t_point pt;
		auto& [x, y] = pt;
		std::getline(fcin, tmp);
		if (auto subpos = tmp.find(','); std::string::npos != subpos)
		{
			x = view_to_int(std::string_view(tmp.begin(), tmp.begin() + subpos));
			y = view_to_int(std::string_view(tmp.begin() + subpos + 1, tmp.end()));
			points.push_back(pt);
		}
		else
		{
			if (tmp.size() > 0)
			{
				folds.push_back({ tmp[11],view_to_int(std::string_view(tmp.begin() + 13,tmp.end())) });
			}
		}
	}
	return std::make_tuple(points, folds);
}
auto folding(t_points& points, t_point& fold)
{
	auto pos = std::get<1>(fold);
	bool fold_on_x = std::get<0>(fold) == 'x';
	auto foldit = [pos, fold_on_x](auto pt)
	{
		auto& [x, y] = pt;
		if (fold_on_x)
		{
			if (x > pos)
				x = pos - (x - pos);
		}
		else
		{
			if (y > pos)
				y = pos - (y - pos);
		}
		return std::make_tuple(x, y);
	};
	std::transform(points.begin(), points.end(), points.begin(), foldit);
	std::sort(points.begin(), points.end());
	auto newend = std::unique(points.begin(), points.end());
	points.resize(std::distance(points.begin(), newend));
	return 0;
}

void step1()
{
	auto [points, folds] = read_values();
	folding(points, folds[0]);
	std::cout << "step 1:" << points.size() << std::endl;
}


void step2()
{
	auto [points, folds] = read_values();
	for (auto& elem : folds)
		folding(points, elem);
	std::vector<std::string> bigletter(6);
	for (auto& elem : bigletter)
		elem.resize(70, ' ');
	for (auto& elem : points)
	{
		auto& [x, y] = elem;
		bigletter[y][x] = '#';
	}
	std::cout << "step 2:" << std::endl;
	for (auto& elem : bigletter)
	{
		std::cout << elem << '\n';
	}
}

int main()
{
	step1();
	step2();

	return 0;
}
