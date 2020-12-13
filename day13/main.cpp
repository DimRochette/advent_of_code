#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <charconv>

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

std::vector<int> split(std::string phrase, std::string delimiter) {
	std::vector<int> list;
	std::size_t pos = 0;
	std::string token;
	while ((pos = phrase.find(delimiter)) != std::string::npos) {
		token = phrase.substr(0, pos);
		list.push_back(view_to_int(token));
		phrase.erase(0, pos + delimiter.length());
	}
	list.push_back(view_to_int(phrase));
	return list;
}

auto read_bus()
{
	std::fstream fcin(advent_input().c_str());
	int starttime;
	fcin >> starttime;
	std::string line;
	fcin >> line;
	auto busid=split(line,",");
	
	return std::make_pair(starttime,busid);
}


void step1()
{
	auto businfo = read_bus();
	auto bestid = 0;
	auto besttime = std::numeric_limits<int>::max();
	for (auto& elem : businfo.second)
	{
		if (elem)
		{
			auto x = elem - (businfo.first % elem);
			if (x < besttime)
			{
				besttime = x;
				bestid = elem;
			}
		}
	}
	std::cout << "step 1:" << besttime*bestid << std::endl;
}

int cpt = 0;
int ok = 0;
long long check(std::vector<std::pair<int, int>>& bustime, int currentbus, long long currenttime)
{

	if (currentbus ==3)
	{
		
		cpt++;
	}
	if (0 == ((currenttime+ bustime[currentbus].second) % bustime[currentbus].first))
	{
		if (currentbus == -1)
		{			
			if ((ok==0) || (cpt - ok) != 19)
			{
				std::cout << "1: " << currenttime;
				std::cout << " OK " << ok << " diff " << (cpt - ok);
				std::cout << std::endl;
			}
			ok = cpt;
		}
		if ((currentbus + 1) == bustime.size())
			return true;
		auto objective = currenttime - bustime[currentbus].second + bustime[currentbus + 1].second;
		return check(bustime, currentbus + 1, currenttime);
	}
	if (currentbus == 1)
	{
		
	}
	return false;
}

long long recurse(std::vector<std::pair<int, int>>& bustime, int currentbus, long long currenttime)
{
	for (long long pos = currenttime;; pos += bustime[currentbus].first)
	{		
		auto objective = pos - bustime[currentbus].second;
		if (check(bustime,currentbus+1,objective))
		{
			return pos - bustime[currentbus].second; 
		}
	}
	return 0;
}

void step2()
{
	auto businfo = read_bus();
	std::vector<std::pair<int, int>> bustime;
	for (int i = 0; i < businfo.second.size(); i++)
	{
		if (businfo.second[i] != 0)
			bustime.push_back({ businfo.second[i], i} );
	}
	std::sort(bustime.begin(), bustime.end(), [](auto& a, auto& b) { return a.first > b.first; });
	auto timeref=std::accumulate(bustime.begin() + 1, bustime.end(), (long long)1, [](auto a, auto b) { return a * b.first; });
	// better start position
	timeref = timeref - (timeref % bustime[0].first);
	auto timestamp = recurse(bustime, 0, timeref);
	std::cout << "step 2:" << timestamp << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
