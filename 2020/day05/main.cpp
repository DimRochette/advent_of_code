#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <charconv>
#include "fileinput.h"


int compute_seat(std::string_view from)
{
	int init = 1 << 6;
	auto depth = from.substr(0, 7);
	auto row = 0;
	for (auto c : depth)
	{
		if (c == 'B')
			row += init;
		init = (init >> 1);
	}
	init = 1 << 2;
	auto col = 0;
	auto width = from.substr(7);
	for (auto c : width)
	{
		if (c == 'R')
			col += init;
		init = (init >> 1);
	}
	return row * 8 + col;
}

void step1()
{
	int seatId = 0;
	std::fstream fcin(advent_input().c_str());
	while (!fcin.eof())
	{
		std::string line;
		fcin >> line;
		seatId = std::max(seatId, compute_seat(line));
	}
	std::cout << "Seat ID 1:" << seatId << std::endl;
}

void step2()
{
	int seatId = 0;
	std::fstream fcin(advent_input().c_str());
	std::vector<int> FlightPlan;
	while (!fcin.eof())
	{
		std::string line;
		fcin >> line;
		FlightPlan.push_back(compute_seat(line));
	}
	std::sort(FlightPlan.begin(), FlightPlan.end());
	auto pos = std::adjacent_find(FlightPlan.begin(), FlightPlan.end(), [](auto a, auto b) {return ((a + 1) != b); });
	std::cout << "Seat ID 2:" << (*pos) + 1 << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
