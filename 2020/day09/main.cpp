#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <charconv>
#include <set>
#include <map>
#include "fileinput.h"
#include <numeric>

auto read_input()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<long long> ret;
	while (!fcin.eof())
	{
		long long val;
		fcin >> val;
		ret.push_back(val);
	}	
	return ret;
}

bool check_next(std::vector<long long>& value,std::pair<int,int> &window )
{
	auto goal = value[window.second];
	for (int from = window.first; from < window.second; from++)
	{
		for (int to = from + 1; to < window.second; to++)
		{
			if ((value[from] + value[to]) == goal)
				return true;
		}
	}
	return false;
}

auto step1()
{
	auto base = read_input();
	auto window = std::make_pair( 0, 25 );
	for (; check_next(base,window);)
	{
		window.first++;
		window.second++;
		if (window.second == base.size())
			break;
	}

	std::cout << "step 1:" << base[window.second] << std::endl;
	return base[window.second];
}

long long findrange()
{
	auto base = read_input();
	auto weak = step1();

	auto window = std::make_pair(0, 1);
	for (window.first = 0; window.first < base.size(); window.first++)
	{
		for (window.second = window.first + 1; window.second < base.size(); window.second++)
		{
			auto ret = std::accumulate(base.begin() + window.first, base.begin() + window.second, (long long)0);
			if (ret == weak)
			{
				const auto [min, max]= std::minmax_element(base.begin() + window.first, base.begin() + window.second);
				return *min + *max;
			}
			if (ret > weak)
				break;
		}
	}
	return 0;
}

void step2()
{
	auto magic = findrange();
	
	std::cout << "step 2:" << magic << std::endl;
}

int main()
{
	step2();
	return 0;
}
