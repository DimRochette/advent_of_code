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
#include <bitset>

struct code {
	char code;
	int counter;
	bool visited = false;
};

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
	while (!fcin.eof())
	{
		int val;
		fcin >> val;
		input.push_back(val);
	}
	std::sort(input.begin(), input.end());
	return input;
}

void step1()
{
	auto input = read_values();
	std::adjacent_difference(input.begin(), input.end(), input.begin());
	std::sort(input.begin(), input.end());
	// always 3 higher
	input.push_back(3);
	auto p = std::lower_bound(input.begin(), input.end(), 3);
	auto smalldiff = std::distance(input.begin(), p);
	auto bigdiff = std::distance(p, input.end());
	std::cout << "step 1:" << smalldiff * bigdiff << std::endl;
}


// convert a line on numbers
// ab   = 11, 01
// abc  = 111, 101, 011, 001
// abcd = 1111, 1101, 1011, 1001, 0111, 0101, 0011
int compute_combinatory(int length)
{
	// the rightmost number should always be selected to be able to have next plug
	length--;
	if (length == 0)
		return 1;
	// we compute binary number with never more than 2 consecutive zero 
	// because 3 consecutive zero forbid to plug left plug to the right one
	int count = 0;
	int max = 1 << length;
	for (int i = 0; i < max; i++)
	{
		int consecutive = 0;
		for (int b = 0; ;)
		{
			auto mask = (i & (1 << b));
			if (0 == mask)
			{
				consecutive++;
				if (consecutive > 2) break;
			}
			else
				consecutive = 0;
			b++;
			if (b == length)
			{
				count++;
				break;
			}
		}
	}
	return count;
}

void step2()
{
	auto input = read_values();
	std::adjacent_difference(input.begin(), input.end(), input.begin());
	// always 3 higher
	input.push_back(3);

	// search number of consecutive 1
	long long permut = 1;
	int prev = 0;
	for (auto elem : input)
	{
		if (elem == 3)
		{
			if (prev)
			{
				permut = permut * compute_combinatory(prev);
			}
			prev = 0;
			continue;
		}
		prev++;
	}
	std::cout << "step 2:" << permut << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
