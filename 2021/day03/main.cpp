#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <ranges>

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

auto countbit(std::vector<std::string>& from,bool majority)
{
	std::vector<int> out(from[0].length());
	for (auto& elem : from)
	{
		for (int i = 0; i < out.size(); i++)
			if (elem[i] == '1') out[i]++;
	}
	std::string outstring;
	for (auto& elem : out)
	{
		bool mostly_one = (elem * 2) >= from.size();
		if (mostly_one == majority)
			outstring += "1";
		else
			outstring += "0";
	}
	return outstring;
}

auto filter(std::vector<std::string>& from,bool majority)
{
	auto filtered = from;
	std::string keep = countbit(filtered, majority);
	auto check = [&keep](int pos,std::string& src)
			{
				return src[pos] == keep[pos];
			};		
	for (int i = 0; i < keep.length(); i++)
	{
		auto checkbit = std::bind_front(check, i);
		std::vector<std::string> out;
		for (auto& elem : filtered | std::views::filter(checkbit))
		{
			out.push_back(elem);
		}
		
		if (out.size() == 1)
			return out[0];
		filtered = out;
		keep = countbit(filtered, majority);
	}
	
	return std::string("");
}

void step1()
{
	auto input = read_values();
	auto major = countbit(input, true);
	auto gamma = std::stoul(major, nullptr, 2);
	auto epsilon = gamma ^ (~0U >> (32- major.length()));
	std::cout << "step 1:" << gamma*epsilon << std::endl;
}

void step2()
{
	auto input = read_values();	
	auto oxygen = filter(input, true);
	auto str_co2 = filter(input, false);	
	auto o2 = std::stoul(oxygen, nullptr, 2);
	auto co2 = std::stoul(str_co2, nullptr, 2);
	std::cout << "step 2:" <<o2*co2<< std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
