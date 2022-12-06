#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>
#include <regex>
#include <deque>
#include <tuple>

struct game
{
	std::vector<std::deque<char>> current;
	std::vector<int> movement;
};

auto read_input()
{
	std::fstream file(advent_input().c_str());
	game ret{};
	// assuming your file is open
	std::string line;
	std::regex helper{ "\\d+" };
	while (!file.eof())
	{
		getline(file, line);
		auto colcount = (line.size() + 1) / 4;
		if (line[1] == '1')
			break;
		if (colcount > ret.current.size())
			ret.current.resize(colcount);
		for (int i = 1; i < line.size(); i += 4)
		{
			if (line[i] != ' ')
			{
				ret.current[(i - 1) / 4].push_back(line[i]);
			}
		}
	}
	while (!file.eof())
	{
		getline(file, line);
		for (auto i = std::sregex_iterator(line.begin(), line.end(), helper); i != std::sregex_iterator(); i++)
		{
			std::smatch match = *i;
			ret.movement.push_back(std::stoi(match.str()));
		}
	}
	return ret;
}

void move_step(game& state, std::ranges::viewable_range auto&& op)
{
	for (int i = op[0]; i > 0; i--)
	{
		state.current[op[2] - 1].push_front(state.current[op[1] - 1].front());
		state.current[op[1] - 1].pop_front();
	}
}
void move_big(game& state, std::ranges::viewable_range auto&& op)
{
	std::deque<char> buffer;
	for (int i = op[0]; i > 0; i--)
	{
		buffer.push_front(state.current[op[1] - 1].front());
		state.current[op[1] - 1].pop_front();
	}
	for (auto box : buffer)
	{
		state.current[op[2] - 1].push_front(box);
	}
}


void print(game& state)
{
	std::cout << "positions:";
	for (auto elem : state.current)
		std::cout << elem.front();
	std::cout << std::endl;
}

void step1()
{
	auto state = read_input();
	auto operations = state.movement | std::views::chunk(3);
	std::ranges::for_each(operations, [&state](std::ranges::viewable_range auto&& elem) { move_step(state, elem); });
	print(state);
}

void step2()
{
	auto state = read_input();
	auto operations = state.movement | std::views::chunk(3);
	std::ranges::for_each(operations, [&state](std::ranges::viewable_range auto&& elem) { move_big(state, elem); });
	print(state);
}

int main()
{
	step1();
	step2();

	return 0;
}
