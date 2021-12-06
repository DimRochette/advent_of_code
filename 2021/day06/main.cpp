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

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<int> input;	
	std::string tmp;
	while (std::getline(fcin, tmp, ',')) {
		input.push_back(view_to_int(tmp));
	}
	return input;
}

auto oneday(std::map<int, long long> gen)
{
	decltype(gen) out;
	for (int i = 0; i < 8; i++)
	{
		out[i] = gen[i+1];
	}
	out[6] += gen[0];
	out[8] += gen[0];
	return out;
}

long long totalfish(int nbdays)
{
	auto input = read_values();
	std::map<int, long long> gen;
	for (auto elem : input)
		gen[elem]++;
	for (int i = 0; i < nbdays; i++)
		gen = oneday(gen);
	return std::accumulate(gen.begin(), gen.end(), static_cast<long long>(0), [](long long acc, std::pair<int, long long> p) { return (acc + p.second); });
}
void step1()
{
	std::cout << "step 1:" << totalfish(80) << std::endl;
}

void step2()
{
	std::cout << "step 2:" << totalfish(256) << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
