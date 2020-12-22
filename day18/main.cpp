#include <iostream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <charconv>
#include <map>
#include <type_traits>
#include <stack>
#include <variant>
#include <string>


std::string replace_str(std::string& str, const std::string& from, const std::string& to)
{
	while (str.find(from) != std::string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

auto read()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<std::vector<std::string>> ret;
	while (!fcin.eof())
	{
		std::vector<std::string> vline;
		std::string line;
		std::getline(fcin, line);
		replace_str(line, " ", "");
		int prev = 0;
		auto pos = line.find_first_of("/*-+()");
		for (; pos != std::string::npos; pos = line.find_first_of("/*-+()", prev))
		{
			if (pos != prev)
			{
				vline.push_back(line.substr(prev, pos - prev));
				prev = pos;
			}
			else
			{
				vline.push_back(line.substr(prev, 1));
				prev = pos + 1;
			}
		}
		if (line[prev] != '\0')
			vline.push_back(line.substr(prev));
		ret.push_back(vline);
	}
	return ret;
}

//will try https://en.wikipedia.org/wiki/Shunting-yard_algorithm
auto eval(std::vector<std::string>& input, bool part2 = false)
{
	std::map<char, char> order;
	if (part2)
		order = { {'+',2},{'-',2},{'*',1},{'/',1},{'(',3} };
	else
		order = { {'+',2},{'-',2},{'*',2},{'/',2},{'(',3} };
	std::deque<std::variant<int, char>> output;
	std::stack<char> operation;
	for (auto& member : input)
	{
		char candidate = '\0';
		if (std::isdigit(member[0]))
		{
			output.push_back(view_to_int(member));
			continue;
		}
		else
		{
			candidate = member[0];
		}

		if (candidate == '(')
		{
			operation.push(candidate);
			continue;
		}
		if (candidate == ')')
		{
			while (operation.top() != '(')
			{
				output.push_back(operation.top());
				operation.pop();
			}
			operation.pop();
			continue;
		}
		if (operation.size())
		{
			if (order[operation.top()] < order[candidate])
			{
				operation.push(candidate);
				continue;
			}
			if (order[operation.top()] == order[candidate])
			{
				output.push_back(operation.top());
				operation.pop();
				operation.push(candidate);
				continue;
			}
			if (operation.top() != '(')
			{
				output.push_back(operation.top());
				operation.pop();
				operation.push(candidate);
				continue;
			}
		}
		operation.push(candidate);
	}
	while (operation.size())
	{
		output.push_back(operation.top());
		operation.pop();
	}

	// now we unpop
	std::stack<long long> buffer;
	while (output.size())
	{
		if (std::holds_alternative<int>(output.front()))
			buffer.push(get<int>(output.front()));
		else
		{
			long long prev = buffer.top();
			buffer.pop();
			switch (get<char>(output.front()))
			{
			case '+': prev = prev + buffer.top(); break;
			case '-': prev = prev - buffer.top(); break;
			case '*': prev = prev * buffer.top(); break;
			case '/': prev = prev / buffer.top(); break;
			default: break;
			}
			buffer.pop();
			buffer.push(prev);
		}
		output.pop_front();
	}
	return buffer.top();
}

void step1()
{
	long long total = 0;
	auto ret = read();
	for (auto& elem : ret)
		total += eval(elem);
	std::cout << "step 1:" << total << std::endl;
}


void step2()
{
	long long total = 0;
	auto ret = read();
	for (auto& elem : ret)
		total += eval(elem, true);
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();
	return 0;
}
