#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <type_traits>
#include <map>
#include <bitset>

constexpr long long decalage = 8;
constexpr long long width = 8 + decalage*2;

struct coord
{
	int x;
	int y;
	int z;
	int t;
};

void init_empty(std::vector<std::vector<std::vector<std::bitset<width>>>>& input)
{
	input.resize(width);
	for (auto& x : input)
	{
		x.resize(width);
		for (auto& y : x)
		{
			y.resize(width);
		}
	}
}

auto read()
{
	std::fstream fcin(advent_input().c_str());	
	std::vector<std::vector<std::vector<std::bitset<width>>>> ret{};
	long long y = 0;

	init_empty(ret);

	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		std::bitset<width>& bitline = ret[decalage][decalage][decalage+y];
		for (long long x = 0; x < line.length(); ++x)
		{
			if (line[x] == '#')
				bitline[decalage +x] = 1;
		}		
		y++;
	}	
	return ret;
}

int count(coord& from, std::vector<std::vector<std::vector<std::bitset<width>>>>& input)
{	
	int count = 0;	
	std::vector<coord> matrix;
	for (int z = -1; z < 2; z++)
		for (int y = -1; y < 2; y++)
			for (int x = -1; x < 2; x++)
			{
				matrix.push_back({ x+from.x,y+from.y,z+from.z,from.t });
			}
	// remove center item
	matrix.erase(matrix.begin()+13);
	for (auto& elem : matrix)
	{
		if (input[from.t][elem.z][elem.y][elem.x])
			count++;
	}
	return count;
}

int counttime(coord& from, std::vector<std::vector<std::vector<std::bitset<width>>>>& input)
{
	int count = 0;
	std::vector<coord> matrix;
	for (int t = -1; t < 2; t++)
	{
		for (int z = -1; z < 2; z++)
			for (int y = -1; y < 2; y++)
				for (int x = -1; x < 2; x++)
				{
					matrix.push_back({ x + from.x,y + from.y,z + from.z ,t + from.t });
				}
	}
	// remove center item
	matrix.erase(matrix.begin() + 40);
	for (auto& elem : matrix)
	{
		if (input[elem.t][elem.z][elem.y][elem.x])
			count++;
	}
	return count;
}

auto display(std::vector<std::vector<std::vector<std::bitset<width>>>>& input, int time)
{

	int nodes = 0;
	coord point;
	point.t = time;
	for (point.z = 0; point.z <= (width -1); point.z++)
	{
		std::vector<std::string> planestr;
		auto& plane = input[time][point.z];
		nodes = 0;
		for (point.y = 0; point.y < (width - 1); point.y++)
		{
			std::string linestr;
			auto& line = plane[point.y];
			for (point.x = 0; point.x < (width - 1); point.x++)
			{
				if (line[point.x])
				{
					linestr += "#";
					nodes++;
				}
				else
					linestr += ".";
			}
			planestr.push_back(linestr);
		}
		if (nodes)
		{
			std::cout << "Plane z=" << point.z << std::endl;
			for (auto & line:planestr)
				std::cout << line << std::endl;
		}
	}
}

auto generate(std::vector<std::vector<std::vector<std::bitset<width>>>>& input,int time)
{
	int nodes = 0;
	coord point;
	time += decalage;
	point.t = time;

	for (point.z = 1; point.z <= (width - 2); point.z++)
	{
		auto& plane = input[time][point.z];
		if (plane.size() == 0)
			plane.resize(width);
		for (point.y = 1; point.y < (width - 2); point.y++)
		{
			auto& line = plane[point.y];
			for (point.x = 1; point.x < (width - 2); point.x++)
			{
				auto cpt= count(point, input);
				if (line[point.x])
				{
					if ((cpt == 2) || (cpt == 3))
					{
						input[time + 1][point.z][point.y][point.x] = 1;
						nodes++;
					}
				}
				else
				{
					if (cpt == 3)
					{						
						input[time + 1][point.z][point.y][point.x] = 1;
						nodes++;
					}
				}				
			}
		}
	}

	return nodes;
}

auto generatetime(std::vector<std::vector<std::vector<std::bitset<width>>>>& input, int time)
{
	int nodes = 0;
	coord point;
	time += decalage;
	point.t = time;	
	std::vector<std::vector<std::vector<std::bitset<width>>>> output;
	init_empty(output);

	for (point.t = 1; point.t <= (width - 2); point.t++)
	{
		for (point.z = 1; point.z <= (width - 2); point.z++)
		{
			auto& plane = input[point.t][point.z];
			if (plane.size() == 0)
				plane.resize(width);
			for (point.y = 1; point.y < (width - 2); point.y++)
			{
				auto& line = plane[point.y];
				for (point.x = 1; point.x < (width - 2); point.x++)
				{
					auto cpt = counttime(point, input);
					if (line[point.x])
					{
						if ((cpt == 2) || (cpt == 3))
						{
							output[point.t][point.z][point.y][point.x] = 1;
							nodes++;
						}
					}
					else
					{
						if (cpt == 3)
						{
							output[point.t][point.z][point.y][point.x] = 1;
							nodes++;
						}
					}
				}
			}
		}
	}

	input = output;
	return nodes;
}


void step1()
{
	auto total = 0;
	auto input = read();
	for (int i = 0; i < 6; i++)
	{
		std::cout << generate(input, i) << std::endl;
	}
	std::cout << "step 1:" << input.size() << std::endl;
}

void step2()
{
	auto total = 0;
	auto input = read();
	for (int i = 0; i < 6; i++)
	{
		total = generatetime(input, i);
	}
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();
	return 0;
}
