#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <charconv>


struct path {
	char order;
	int counter;
};

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

auto read_path()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<path> input;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		path instruction{ line[0], view_to_int(line.substr(1)) };
		input.push_back(instruction);
	}
	return input;
}

struct boatpos
{
	std::pair<int, int> pos;
	std::pair<int, int> waypoint;
	char direction;
};

void advance1(boatpos& boat, path& instruction)
{
	std::vector<char> turn{ 'N','E','S','W','N','E','S','W','N','E','S','W' };
	switch (instruction.order)
	{
	case 'N': boat.pos.second -= instruction.counter; break;
	case 'E': boat.pos.first += instruction.counter; break;
	case 'S': boat.pos.second += instruction.counter; break;
	case 'W': boat.pos.first -= instruction.counter; break;
	case 'F':
	{
		path small = { boat.direction,instruction.counter };
		advance1(boat, small);
	}
	break;
	case 'L':
	case 'R':
	{
		instruction.counter /= 90;
		auto pos = std::find(turn.begin() + 4, turn.end(), boat.direction);
		auto idx = std::distance(turn.begin(), pos);
		if (instruction.order == 'L')
			idx -= instruction.counter;
		else
			idx += instruction.counter;
		boat.direction = turn[idx];
	}
	break;
	}
}

void advance2(boatpos& boat, path& instruction)
{
	switch (instruction.order)
	{
	case 'N': boat.waypoint.second += instruction.counter; break;
	case 'E': boat.waypoint.first += instruction.counter; break;
	case 'S': boat.waypoint.second -= instruction.counter; break;
	case 'W': boat.waypoint.first -= instruction.counter; break;
	case 'F':
	{
		boat.pos.first += boat.waypoint.first * instruction.counter;
		boat.pos.second += boat.waypoint.second * instruction.counter;
	}
	break;
	case 'L': instruction.counter = 360 - instruction.counter; // convert rotation from left to right
		[[fallthrough]];
	case 'R':
	{
		auto iteration = instruction.counter / 90;

		// repeat 90° turns
		for (auto count = 0; count < iteration; count++)
		{
			auto tmp = boat.waypoint.first;
			boat.waypoint.first = boat.waypoint.second;
			boat.waypoint.second = -tmp;
		}
	}
	break;
	}
}

void step1()
{
	boatpos boat{ {0,0},{0,0},'E' };
	auto input = read_path();
	for (auto instruction : input)
	{
		advance1(boat, instruction);
	}
	int manhattan = std::abs(boat.pos.first) + std::abs(boat.pos.second);
	std::cout << "step 1:" << manhattan << std::endl;
}

void step2()
{
	boatpos boat{ {0,0},{10,1},'E' };
	auto input = read_path();
	for (auto instruction : input)
	{
		advance2(boat, instruction);
	}
	int manhattan = std::abs(boat.pos.first) + std::abs(boat.pos.second);
	std::cout << "step 2:" << manhattan << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
