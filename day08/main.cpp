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
	bool visited = false;
} ;

auto view_to_int(std::string_view field)
{
	int output=0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

int execute(std::vector<code>& program)
{
	auto acc = 0;
	for (auto pos = 0; program[pos].visited == false; )
	{
		program[pos].visited = true;
		switch (program[pos].code)
		{
		case 'a':
			acc += program[pos].counter;
			pos++;
			break;
		case 'n':
			pos++;
			break;
		case 'j': pos += program[pos].counter;
			break;
		}
	}
	return acc;
}

bool check_execute(std::vector<code>& program)
{
	auto acc = 0;
	auto pos = 0;
	for (; program[pos].visited == false; )
	{
		program[pos].visited = true;
		switch (program[pos].code)
		{
		case 'a':
			acc += program[pos].counter;
			pos++;
			break;
		case 'n':
			pos++;
			break;
		case 'j': pos += program[pos].counter;
			break;
		}
	}	
	return (pos==program.size()-1);
}

auto read_program()
{
	std::fstream fcin(advent_input().c_str());
	std::vector<code> program;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		code instruction{ line[0], view_to_int(line.substr(5)), false };
		if (line[4] == '-')
			instruction.counter = -instruction.counter;
		program.push_back(instruction);
	}
	// add visited instruction at end to stop
	program.push_back({ 'n', 0, true });
	return program;
}

void step1()
{
	auto program=read_program();

	std::cout << "step 1:" << execute(program) << std::endl;
}

void step2()
{
	auto program = read_program();
	
	for (auto pos=0;;pos++)
	{
		if (program[pos].code == 'a') 
			continue;
		decltype(program) workcopy;
		std::copy(program.begin(), program.end(), std::back_inserter(workcopy));
		if (workcopy[pos].code == 'j')
			workcopy[pos].code = 'n';
		else
			workcopy[pos].code = 'j';
		if (check_execute(workcopy))
		{
			program.clear();
			workcopy.resize(workcopy.size() - 1);
			for (auto& elem : workcopy)
			{
				elem.visited = false;
				program.push_back(elem);
			}
			program.push_back({ 'n', 0, true });
			break;
		}
	}
	
	std::cout << "step 2:" << execute(program) << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
