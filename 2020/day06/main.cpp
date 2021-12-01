#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <charconv>
#include <set>
#include "fileinput.h"


void step1()
{
	std::size_t total = 0;
	std::fstream fcin(advent_input().c_str());
	std::string bigline;	
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		if (!line.empty())
			bigline += line;
		else
		{
			std::set<char> group;
			for (auto& elem : bigline)
			{
				group.emplace(elem);
			}
			total += group.size();
			bigline.clear();
		}

	}
	std::cout << "step 1:" << total << std::endl;
}

void step2()
{
	std::size_t total = 0;
	std::fstream fcin(advent_input().c_str());
	std::set<char> group;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		if (!line.empty())
		{
			std::set<char> single;
			for (auto& elem : line)
			{
				single.emplace(elem);
			}
			if (group.empty())
				group = single;
			else
			{
				std::set<char> intersect;				
				std::set_intersection(group.begin(), group.end(), single.begin(), single.end(),
					std::inserter(intersect, intersect.begin()));
				group = intersect;
				if (group.empty())
				{
					// end group ignoring eveything
					do 
					{
						std::getline(fcin, line);
					} while (!line.empty());
				}
			}
		}
		else
		{
			total += group.size();
			group.clear();
		}

	}
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
