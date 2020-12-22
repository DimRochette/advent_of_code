#include <iostream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <charconv>

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

std::vector<std::string> splitstring(std::string phrase, std::string delimiter) {
	std::vector<std::string> list;
	std::size_t pos = 0;
	std::string token;
	while ((pos = phrase.find(delimiter)) != std::string::npos) {
		list.push_back(phrase.substr(0, pos));
		phrase.erase(0, pos + delimiter.length());
	}
	list.push_back(phrase);
	return list;
}

auto read()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<std::vector<std::string>> ret;
	while (!fcin.eof())
	{
		std::vector<std::string> vline;
		std::string line;
		std::getline(fcin, line);
		replace_str(line, " ","");
		int prev = 0;
		auto pos = line.find_first_of("/*-+()");
		for (; pos!= std::string::npos; pos = line.find_first_of("/*-+()", prev))
		{
			if (pos != prev)
			{
				vline.push_back(line.substr(prev, pos-prev));
				prev = pos;
			}
			else
			{
				vline.push_back(line.substr(prev, 1));
				prev = pos+1;
			}			
		}
		ret.push_back(vline);
	}
	return ret;
}

//will try https://en.wikipedia.org/wiki/Shunting-yard_algorithm
auto eval(std::vector<std::string>& input)
{
	std::stack< std::variant<int, char>> output;
	std::stack<char> operation;
	for (auto& member : input)
	{
		char candidate = '\0';
		if (std::isdigit(member[0]))
		{
			output.push(view_to_int(member));
		}
		else
		{
			candidate = member[0];
		}

		if (operation.size())
		{
			int prev = std::get<int>(output.top());
			output.pop();
			int cur = std::get<int>(output.top());
			output.pop();
			switch (operation.top())
			{
			case '+': prev = prev + cur; break;
			case '-': prev = prev - cur; break;
			case '*': prev = prev * cur; break;
			case '/': prev = prev / cur; break;
			default: break;
			}
			output.push(prev);
			operation.pop();
		}
		if (candidate!='\0')
			operation.push(candidate);
	}
	while (operation.size())
	{
		output.push(operation.top());
		operation.pop();
	}
	
#if 0
	std::stack<int> buffer;
	while (input.size())
	{
		if (std::holds_alternative<int>(input.top()))
			buffer.push(get<int>(input.top()));
		else
		{
			int prev = buffer.top();
			buffer.pop();
			switch (get<char>(input.top()))
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
		input.pop();
	}
#endif
	return 0;
}

void step1()
{
	auto total = 0;	
	auto ret = read();
	for (auto & elem:ret)
		total+= eval(elem);
	std::cout << "step 1:" << total << std::endl;
}


void step2()
{
	auto total = 0;
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();
	return 0;
}
