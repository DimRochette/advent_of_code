#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"

auto treecount(int x, int y)
{
	std::fstream fcin(advent_input().c_str());
	int total = 0;
	int posx = x;
	std::string line;
	fcin >> line;
	int modulo = line.length();
	while (!fcin.eof())
	{
		for (auto extra = y - 1; extra > 0; extra--)
			fcin >> line;
		fcin >> line;
		if (line[posx % modulo] == '#')
			total++;
		posx += x;
	}
	return total;
}

void step1()
{
	std::cout << "total 1:" << treecount(3, 1) << std::endl;
}

void step2()
{	
	long long total = 1;
	for (auto [x,y] : std::vector<std::pair<int, int>>({ {1,1},{3,1},{5,1},{7,1},{1,2} }))
	{
		total *= treecount(x, y);
	}

	std::cout << "total 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
