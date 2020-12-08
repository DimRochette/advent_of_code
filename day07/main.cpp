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


std::string replace_str(std::string& str, const std::string& from, const std::string& to)
{
	while (str.find(from) != std::string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

std::pair<int,std::string> splitcount(std::string str)
{
	int count = 0;
	if (isdigit(str[0]))
	{
		count = std::stoi(str);
		str = str.substr(str.find(" ")+1);
	}
	return { count, str };
}

std::vector<std::string> extract(std::map<std::string, std::vector<std::string>> &full,std::string bag)
{
	if (full.find(bag) != full.end())
	{
		auto node=full.extract(bag);
		return node.mapped();
	}
	return {};
}

int countbags(std::map<std::string, std::vector<std::pair<int, std::string>>> &full, std::string from,int level=0)
{
	int total = 0;
	auto bag = full[from];
	for (auto& [number,elem] : bag)
	{
		total += number * countbags(full, elem,level+1);
	}
	return total+1;
}

void step1()
{
	std::size_t total = 0;
	std::fstream fcin(advent_input().c_str());
	std::string bigline;
	std::map<std::string, std::vector<std::string>> full;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		// ugly but easy replace string by ,
		for (auto& elem : { " bags contain "," bags"," bag","no other",".",",,",", " })
		{
			replace_str(line, elem, ",");
		}
		auto sep=line.find(',');
		auto firstbag = line.substr(0, sep);
		
		std::vector<std::string> bags;
		for (auto bagstart=sep+1;bagstart!=std::string::npos;)
		{
			auto bagend=line.find(",",bagstart);
			auto bag = splitcount(line.substr(bagstart, bagend - bagstart));
			if (bag.second.empty())
				break;
			bags.push_back(bag.second);
			if (bagend == std::string::npos)
				break;
			bagstart = bagend + 1;
		}
		for (auto& elem : bags)
		{			
			auto& node = full[elem];
			node.push_back(firstbag);
			if (full.find(firstbag) == full.end())
				full[firstbag] = {};
		}
	}
	
	std::set<std::string> colorlist;
	for (auto firstbag = extract(full, "shiny gold"); !firstbag.empty();)
	{
		for (auto& elem : firstbag)
		{
			colorlist.insert(elem);
		}
		decltype(firstbag) addnew;
		for (auto& elem : firstbag)
		{
			auto ret=extract(full, elem);
			addnew.insert(addnew.end(),ret.begin(), ret.end());
		}
		for (auto& elem : addnew)
		{
			colorlist.insert(elem);
		}
		
		firstbag = addnew;		
	}

	std::cout << "step 1:" << colorlist.size() << std::endl;
}

void step2()
{
	int total = 0;
	std::fstream fcin(advent_input().c_str());
	std::string bigline;
	std::map<std::string, std::vector<std::pair<int, std::string>>> full;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		// ugly but easy replace string by ,
		for (auto& elem : { " bags contain "," bags"," bag","no other",".",",,",", " })
		{
			replace_str(line, elem, ",");
		}
		auto sep = line.find(',');
		auto firstbag = line.substr(0, sep);

		std::vector<std::pair<int, std::string>> bags;
		for (auto bagstart = sep + 1; bagstart != std::string::npos;)
		{
			auto bagend = line.find(",", bagstart);
			auto bag = splitcount(line.substr(bagstart, bagend - bagstart));
			if (bag.second.empty())
				break;
			bags.push_back(bag);
			if (bagend == std::string::npos)
				break;
			bagstart = bagend + 1;
		}
		auto& node = full[firstbag];
		node.insert(node.end(), bags.begin(), bags.end());
	}	
	total = countbags(full, "shiny gold")-1;

	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
