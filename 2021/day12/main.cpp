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

using t_lines = std::multimap<std::string, std::string>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string tmp;

	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		auto pos = std::find(tmp.begin(), tmp.end(), '-');
		auto distance = std::distance(tmp.begin(), pos);
		std::string first(tmp.begin(), pos++);
		std::string second(pos, tmp.end());
		lines.insert({ first,second });
		lines.insert({ second,first });
	}
	return lines;
}

bool allow(const std::string& src, std::string_view node, bool& two_visit_done)
{
	if (two_visit_done)
		return !src.contains(node);
	if (node == ",start") return false;
	auto found = src.find(node);
	if (found != std::string::npos)
	{
		two_visit_done = true;
	}
	return true;
}

std::vector<std::string> advance_step(t_lines& data, const std::string& currentpos, std::vector<std::string> paths, bool two_visit_done)
{
	auto range = data.equal_range(currentpos);
	std::vector<std::string> output;
	for (auto& singlepath : paths)
	{
		for (auto it = range.first; it != range.second; ++it)
		{
			bool blocal = two_visit_done;
			if (isupper(it->second[0]) || (allow(singlepath, (std::string(",") + it->second), blocal)))
			{
				// uppercase or not already present
				auto strpath = singlepath + "," + it->second;
				if (it->second == "end")
				{
					output.push_back(strpath);
					continue;
				}
				auto newpath = advance_step(data, it->second, { strpath }, blocal);
				std::copy(std::begin(newpath), std::end(newpath), std::back_inserter(output));
			}
		}
	}
	return output;
}

auto init(bool single_only)
{
	auto data = read_values();
	auto startrange = data.equal_range("start");
	std::vector<std::string> path{ ",start" };
	return advance_step(data, "start", path, single_only);
}

void step1()
{
	auto all = init(true);
	std::cout << "step 1:" << all.size() << std::endl;
}


void step2()
{
	auto all = init(false);
	std::cout << "step 2:" << all.size() << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
