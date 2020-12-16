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
#include <list>
#include <stack>
#include <set>

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

std::vector<int> split(std::string phrase, std::string delimiter) {
	std::vector<int> list;
	std::size_t pos = 0;
	std::string token;
	while ((pos = phrase.find(delimiter)) != std::string::npos) {
		token = phrase.substr(0, pos);
		list.push_back(view_to_int(token));
		phrase.erase(0, pos + delimiter.length());
	}
	list.push_back(view_to_int(phrase));
	return list;
}

auto read_recitation()
{
	std::fstream fcin(advent_input().c_str());
	std::string line;
	fcin >> line;
	return split(line, ",");
}

void step1()
{
	auto total = 0;
	auto input = read_recitation();
	for (; input.size() < 2020;)
	{
		auto last = input.back();
		if (auto found = std::find(input.rbegin() + 1, input.rend(), last); found == input.rend())
		{
			input.push_back(0);
		}
		else
		{
			auto foundpos=std::distance(found, input.rend());
			input.push_back(static_cast<int>(input.size()-foundpos));
		}
		
	}
	std::cout << "step 1:" << input.back() << std::endl;
}

void step2()
{
	auto total = 0;
	auto recit = read_recitation();
	std::unordered_map<int, int> input;
	for (auto pos=recit.begin();pos<(recit.end()-1);pos++)
	{
		input[*pos]=static_cast<int>(input.size());
	}
	auto todo = recit.back();
	for (int turn=static_cast<int>(input.size())+1; turn < 30000000; turn++)
	{
		if (input.find(todo) == input.end())
		{
			// value not present
			input[todo] = turn-1;
			todo = 0;			
		}
		else
		{
			auto found = input.find(todo);
			auto prev = found->second;
			todo = turn-1 - prev;
			found->second = turn-1;			
		}
	}
	std::cout << "step 2:" << todo << std::endl;
}

int main()
{
	step1();	
	step2();
	return 0;
}
