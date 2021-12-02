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

struct code {
	char code;
	int counter;
};

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

int execute1(std::vector<code>& program)
{
	auto x = 0;
	auto y = 0;
	for (auto pos = 0; pos < program.size(); pos++)
	{
		switch (program[pos].code)
		{
		case 'f':
			x += program[pos].counter;
			break;
		case 'u':
			y -= program[pos].counter;
			break;
		case 'd':
			y += program[pos].counter;
			break;
		}
	}
	return x * y;
}

int execute2(std::vector<code>& program)
{
	auto x = 0;
	auto y = 0;
	auto aim = 0;
	for (auto pos = 0; pos < program.size(); pos++)
	{
		switch (program[pos].code)
		{
		case 'f':
			x += program[pos].counter;
			y += aim * program[pos].counter;
			break;
		case 'u':
			aim -= program[pos].counter;
			break;
		case 'd':
			aim += program[pos].counter;
			break;
		}
	}
	return x * y;
}

auto read_program()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<code> program;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		code instruction{ line[0], view_to_int(line.substr(line.find(" ") + 1)) };
		program.push_back(instruction);
	}
	return program;
}

void step1()
{
	auto program = read_program();
	std::cout << "step 1:" << execute1(program) << std::endl;
}

void step2()
{
	auto program = read_program();
	std::cout << "step 2:" << execute2(program) << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
