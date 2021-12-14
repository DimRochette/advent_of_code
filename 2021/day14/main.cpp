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
#include <ranges>
#include <chrono>

using t_lines = std::map<std::string, std::string>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string input;
	std::getline(fcin, input);
	std::string tmp;

	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		if (tmp.size())
		{
			std::string key(tmp.begin(), tmp.begin() + 2);
			std::string value(tmp.begin() + 6, tmp.begin() + 7);
			lines[key] = value;
		}
	}
	return std::make_tuple(input, lines);
}

auto mutate(std::string input, t_lines mutations)
{
	decltype(input) output;
	for (auto it = input.begin(); it < (input.end() - 1); ++it)
	{
		auto key = std::string(it, it + 2);
		output.push_back(key[0]);
		auto pos = mutations.find(key);
		if (pos != mutations.end())
			output.push_back(pos->second[0]);
	}
	output.push_back(*input.rbegin());
	return output;
}

void step1()
{
	auto [input, mutations] = read_values();
	for (int i = 0; i < 10; i++)
	{
		input = mutate(input, mutations);
	}
	std::vector<int> frequency(255);
	for (auto elem : input)
	{
		frequency[elem]++;
	}
	auto filtered = frequency | std::views::filter([](auto elem) {return elem != 0; });
	auto res = std::ranges::minmax_element(filtered);

	std::cout << "step 1:" << (*res.max - *res.min) << "\n";
}

auto mutate2(std::string input, t_lines mutations)
{
	using combi_t = std::map<std::string, long long>;
	combi_t combination;
	for (auto it = input.begin(); it < (input.end() - 1); ++it)
	{
		auto key = std::string(it, it + 2);
		combination[key]++;
	}

	auto comb_current = combination;
	for (int i = 0; i < 40; i++)
	{
		combination = {};
		for (auto& elem : comb_current)
		{
			auto pos = mutations.find(elem.first);
			if (pos != mutations.end())
			{

				combination[elem.first[0] + pos->second] += elem.second;
				combination[pos->second + elem.first[1]] += elem.second;
			}
		}
		comb_current = combination;
	}
	std::vector<long long> frequency(255);
	// all letter are  counted twice but last letter is counted only once
	frequency[*input.rbegin()]++;
	for (auto& elem : comb_current)
	{
		frequency[elem.first[0]] += elem.second;
		frequency[elem.first[1]] += elem.second;
	}
	//NN x 3 = NBBBCNCCN
	//
	// NN
	// NC CN
	// NB BC CC CN
	// NB BB BB BC CN NC CC CN

	return frequency;
}

void step2()
{
	auto [input, mutations] = read_values();
	auto frequency = mutate2(input, mutations);

	auto filtered = frequency | std::views::filter([](auto elem) {return elem != 0; });
	auto res = std::ranges::minmax_element(filtered);

	std::cout << "step 2:" << (*res.max - *res.min) / 2 << "\n";
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
