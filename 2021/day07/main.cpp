#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <limits>
#include <map>

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::map<int,int> input;
	std::string tmp;
	while (std::getline(fcin, tmp, ',')) {
		input[view_to_int(tmp)]++;
	}
	return input;
}

auto compute1(std::map<int, int>& input, int position)
{
	auto consume = [position](auto acc, auto val)
	{
		return acc + (val.second * (std::abs(val.first - position)));
	};
	return std::accumulate(input.begin(), input.end(), 0, consume);
}

void step1()
{
	auto ret=read_values();
	auto fuel = std::numeric_limits<int>::max();
	for (int i = ret.begin()->first; i < ret.rbegin()->first; i++)
	{
		fuel = std::min(fuel, compute1(ret, i));
	}
	std::cout << "step 1:" << fuel << std::endl;
}

auto compute2(std::map<int, int>& input, int position, std::vector<int>& cost)
{
	auto consume = [position,&cost](auto acc, auto val)
	{
		return acc + (val.second * cost[(std::abs(val.first - position))]);
	};
	return std::accumulate(input.begin(), input.end(), 0, consume);
}

void step2()
{
	auto ret = read_values();
	auto fuel = std::numeric_limits<int>::max();
	auto fuelcost = std::vector<int>(ret.rbegin()->first+1);
	int old = 0;
	int pos = 0;
	for (auto& elem : fuelcost)
	{		
		elem = old + pos;
		old = elem;
		pos++;
	}
	for (int i = ret.begin()->first; i < ret.rbegin()->first; i++)
	{
		fuel = std::min(fuel, compute2(ret, i, fuelcost));
	}
	std::cout << "step 2:" << fuel << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
