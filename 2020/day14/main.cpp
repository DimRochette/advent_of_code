#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <charconv>
#include <bitset>
#include <type_traits>
#include <map>

auto view_to_int(std::string_view field)
{
	long long output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

std::pair<std::bitset<36>, std::bitset<36>> convert_mask(std::string_view maskstring)
{
	std::bitset<36> mask;
	std::bitset<36> value;
	for (int idx=0;idx< maskstring.length();idx++)
	{
		int pos = 35 - idx;
		switch (maskstring[pos])
		{
			case '0':
			{
				mask[idx] = 1;
				value[idx] = 0;
			}
			break;
			case '1':
			{
				mask[idx] = 1;
				value[idx] = 1;
			}
			break;
			case 'X':
			{
			}
			break;
		}

	}
	return std::make_pair(mask, value);
}

std::vector<long long> op_step2(long long addr,long long mask, long long maskvalue)
{
	std::vector<long long> ret;
	
	long long mask_to_keep_zero = mask & (~maskvalue);
	long long mask_of_one = mask & maskvalue;
	long long fixedpart = (addr & mask_to_keep_zero) | mask_of_one;
	std::bitset<36> mask_floating(~mask);
	std::vector<char> flipbit;
	for (int idx = 0; idx < 36; idx++)
	{ 
		if (mask_floating[idx])
		{
			flipbit.push_back(idx);
		}
	}
 	int combinatory = 1 << flipbit.size();
	for (int iteration = 0; iteration < combinatory; iteration++)
	{
		std::bitset<36> candidate(fixedpart);
		for (auto idx = 0; idx < flipbit.size(); idx++)
		{
			if (0 != ((1 << idx) & iteration))
			{
				candidate[flipbit[idx]] = 1;
			}
		}
		ret.push_back(candidate.to_ullong());
	}
	return ret;
}

auto read_mask_1()
{
	std::fstream fcin(advent_input().c_str());
	std::map<long long, long long> memory;
	std::invoke_result_t<decltype(convert_mask), std::string_view>  mask;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);				
		if (line[1] == 'a')
		{
			//mask
			mask = convert_mask(line.substr(7));
		}
		else
		{
			// memory
			auto memaddr = view_to_int(line.substr(4));
			auto pos = line.find('=')+2;
			auto value = view_to_int(line.substr(pos));			
			memory[memaddr] = ((mask.first.to_ullong() & mask.second.to_ullong()) | (value & (~mask.first.to_ullong())));
		}
	}
	auto ret=std::accumulate(memory.begin(), memory.end(), (long long)0, [](auto ref, auto elem) {return ref + elem.second; });
	return ret;
}

auto read_mask_2()
{
	std::fstream fcin(advent_input().c_str());
	std::map<long long, long long> memory;
	std::invoke_result_t<decltype(convert_mask), std::string_view>  mask;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		if (line[1] == 'a')
		{
			//mask
			mask = convert_mask(line.substr(7));
		}
		else
		{
			// memory
			auto memaddr = view_to_int(line.substr(4));
			auto pos = line.find('=') + 2;
			auto value = view_to_int(line.substr(pos));
			auto vec=op_step2(memaddr, mask.first.to_ullong(), mask.second.to_ullong());
			for (auto elem : vec)
				memory[elem] = value;
		}
	}
	auto ret = std::accumulate(memory.begin(), memory.end(), (long long)0, [](auto ref, auto elem) {return ref + elem.second; });
	return ret;
}

void step1()
{
	auto total = read_mask_1();
	std::cout << "step 1:" << total << std::endl;
}

void step2()
{
	auto total = read_mask_2();
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();	
	step2();
	return 0;
}
