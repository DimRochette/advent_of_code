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

// check a number+position division and return how many numbers are ok with this predicate
long long check(std::vector<std::pair<int, int>>& bustime, int currentbus, long long currenttime)
{
	if (0 == ((currenttime + bustime[currentbus].second) % bustime[currentbus].first))
	{
		// if we are on last item return length
		if ((currentbus + 1) == bustime.size())
			return currentbus + 1;
		auto objective = currenttime - bustime[currentbus].second + bustime[currentbus + 1].second;
		return check(bustime, currentbus + 1, currenttime);
	}
	// failed to devide we return previous value
	return currentbus -1;
}

long long recurse(std::vector<std::pair<int, int>>& bustime, int currentbus, long long currenttime)
{
	long long increment= bustime[currentbus].first;
	long long bestok = 0;
	int cpt = 0;
	for (long long pos = currenttime;; pos += increment)
	{
		cpt++;
		auto objective = pos - bustime[currentbus].second;
		auto lastok = check(bustime, currentbus + 1, objective); 
		if (lastok == bustime.size())
		{
			std::cout << "number of iteration " << cpt << std::endl;
			return objective; // all number ok
		}
		else
			if (lastok> bestok)
			{
				// number from 0 to bestok included are correctly aligned so we increment by their multiplication now
				increment = std::accumulate(bustime.begin(), bustime.begin() + lastok+1, (long long)1, [](auto a, auto b) { return a * b.first; });
				bestok = lastok;
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
	auto timestamp = recurse(bustime, 0, 0);
	std::cout << "step 2:" << timestamp << std::endl;
}

int main()
{
	step1();	
	step2();
	return 0;
}
