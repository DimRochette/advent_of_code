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
#include <stack>

using t_lines = std::vector<std::string>;
using t_hot = std::vector<std::tuple<int, int>>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string tmp;
	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		lines.push_back(tmp);
	}
	return lines;
}

auto check_parenthesis(std::string line)
{
	std::stack<char> opens;
	for (auto symbol : line)
	{
		switch (symbol)
		{
		case '(': opens.push(symbol); break;
		case '[': opens.push(symbol); break;
		case '{': opens.push(symbol); break;
		case '<': opens.push(symbol); break;
		case ')':
		{
			if (opens.top() == '(') opens.pop();
			else return symbol;

		} break;
		case ']':
		{
			if (opens.top() == '[') opens.pop();
			else return symbol;

		} break;
		case '}':
		{
			if (opens.top() == '{') opens.pop();
			else return symbol;

		} break;
		case '>':
		{
			if (opens.top() == '<') opens.pop();
			else return symbol;

		} break;
		}
	}
	return '\0';
}

auto count_missing(std::string line)
{
	std::stack<char> opens;
	for (auto symbol : line)
	{
		switch (symbol)
		{
		case '(':
		case '[':
		case '{':
		case '<': opens.push(symbol); break;
		case ')':
		case ']':
		case '}':
		case '>': opens.pop(); break;
		}
	}
	long long total = 0;
	while (!opens.empty())
	{
		auto val = 0;
		switch (opens.top())
		{
		case '(': val = 1; break;
		case '[': val = 2; break;
		case '{': val = 3; break;
		case '<': val = 4; break;
		}
		opens.pop();
		total = total * 5 + val;
	}

	return total;
}

void step1()
{
	auto data = read_values();
	auto total = 0;
	for (auto& lines : data)
	{
		auto ret = check_parenthesis(lines);
		switch (ret)
		{
		case ')': total += 3; break;
		case ']': total += 57; break;
		case '}': total += 1197; break;
		case '>': total += 25137; break;
		}
	}

	std::cout << "step 1:" << total << std::endl;
}

void step2()
{
	auto data = read_values();
	data.erase(std::remove_if(data.begin(), data.end(), [](auto& line) {return (check_parenthesis(line) != '\0'); }), data.end());
	std::vector<long long> res;
	for (auto& line : data)
	{
		res.push_back(count_missing(line));
	}
	std::sort(res.begin(), res.end());
	std::cout << "step 2:" << res[res.size() / 2] << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
