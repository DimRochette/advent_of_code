#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>
#include <map>

auto read_input()
{
	std::fstream file(advent_input().c_str());
	std::map<std::tuple<char, char>, int> cards;
	// assuming your file is open
	std::string line;
	while (!file.eof())
	{
		getline(file, line);
		std::tuple<char, char> hand = { line[0] - 'A' + 1,line[2] - 'X' + 1 };
		cards[hand] = cards[hand] + 1;
	}
	return cards;
}

int score(std::tuple<char, char> hand)
{
	auto [left, right] = hand;
	switch (left)
	{
	case 1: {
		switch (right)
		{
		case 1: return right + 3;
		case 2: return right + 6;
		case 3: return right + 0;
		}
	}
	case 2: {
		switch (right)
		{
		case 1: return right + 0;
		case 2: return right + 3;
		case 3: return right + 6;
		}
	}
	case 3: {
		switch (right)
		{
		case 1: return right + 6;
		case 2: return right + 0;
		case 3: return right + 3;
		}
	}
	}
}

int goal(std::tuple<char, char> hand)
{
	auto [left, right] = hand;
	switch (right)
	{
	case 1: {
		switch (left)
		{
		case 1: return 3;
		case 2: return 1;
		case 3: return 2;
		}
	}
	case 2: {
		return left + 3;
	}
	case 3: {
		switch (left)
		{
		case 1: return 2 + 6;
		case 2: return 3 + 6;
		case 3: return 1 + 6;
		}
	}
	}
}

void step1()
{
	auto cards = read_input();
	auto total = std::accumulate(cards.begin(), cards.end(), 0, [](auto sum, const auto& hand) {return sum + score(hand.first) * hand.second; });
	std::cout << "score:" << total << std::endl;
}

void step2()
{
	auto cards = read_input();
	auto total = std::accumulate(cards.begin(), cards.end(), 0, [](auto sum, const auto& hand) {return sum + goal(hand.first) * hand.second; });
	std::cout << "score:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
