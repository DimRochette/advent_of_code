#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <charconv>
#include <bitset>
#include <type_traits>
#include <map>
#include <list>
#include <stack>
#include <set>


std::string replace_str(std::string& str, const std::string& from, const std::string& to)
{
	while (str.find(from) != std::string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

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

struct ticket_description
{
	using range_t = std::pair<int, int>;
	std::map<std::string, std::pair<range_t, range_t>> fields;
	using ticket_t = std::vector<int>;
	ticket_t myticket;
	std::vector<ticket_t> tickets;
};

ticket_description read()
{
	ticket_description ret;
	std::fstream fcin(advent_input().c_str());
	std::string line;

	while (!fcin.eof())
	{
		std::getline(fcin, line);
		if (line.empty())
			break;
		replace_str(line, "-", ",");
		replace_str(line, " or ", ",");
		auto desc_sep = line.find(':');
		auto s = split(line.substr(desc_sep + 2), ",");
		line = line.substr(0, desc_sep);
		ret.fields[line] = std::make_pair(std::make_pair(s[0], s[1]), std::make_pair(s[2], s[3]));
	}

	std::getline(fcin, line);
	while (!fcin.eof())
	{
		std::getline(fcin, line);
		if (line.empty())
			break;
		ret.myticket = split(line, ",");
	}

	std::getline(fcin, line);
	while (!fcin.eof())
	{
		std::getline(fcin, line);
		if (line.empty())
			break;
		ret.tickets.push_back(split(line, ","));
	}
	return ret;
}

bool valid_field(int value, ticket_description& input)
{
	bool ret = false;
	for (auto& field : input.fields)
	{
		auto range1ok = (value >= field.second.first.first) && (value <= field.second.first.second);
		auto range2ok = (value >= field.second.second.first) && (value <= field.second.second.second);
		if (range1ok || range2ok)
		{
			return true;
		}
	}
	return false;
}

std::set<std::string> valid_fields(std::vector<int>& values, ticket_description& input)
{
	std::set<std::string> responses;
	for (auto& elem : input.fields)
	{
		responses.insert(elem.first);
	}
	for (auto value : values)
	{
		std::set<std::string> list_current;
		for (auto& field : input.fields)
		{
			auto range1ok = (value >= field.second.first.first) && (value <= field.second.first.second);
			auto range2ok = (value >= field.second.second.first) && (value <= field.second.second.second);
			if (range1ok || range2ok)
			{
				list_current.insert(field.first);
			}
		}
		std::set<std::string> intersect;
		std::set_intersection(responses.begin(), responses.end(), list_current.begin(), list_current.end(),
			std::inserter(intersect, intersect.begin()));
		responses = intersect;
	}
	return responses;
}

void step1()
{
	auto total = 0;
	auto input = read();
	for (auto& nearby : input.tickets)
	{
		bool valfound = false;
		for (auto val : nearby)
		{
			if (!valid_field(val, input))
			{
				total += val;
			}
		}
	}
	std::cout << "step 1:" << total << std::endl;
}

std::vector<std::string> deduce(std::vector<std::set<std::string>>& full)
{
	std::vector<std::string> responses(full.size());
	for (int i = 0; i < full.size();)
	{
		if (full[i].size() == 1)
		{
			responses[i] = *(full[i].begin());
			for (auto& single : full)
			{
				single.erase(responses[i]);
			}
			i = 0;
			continue;
		}
		i++;
	}
	return responses;
}

void step2()
{
	auto input = read();
	std::vector<ticket_description::ticket_t> validtickets;
	for (auto& nearby : input.tickets)
	{
		bool lineok = true;
		for (auto val : nearby)
		{
			if (!valid_field(val, input))
			{
				lineok = false;
				break;
			}
		}
		if (lineok)
			validtickets.push_back(nearby);
	}
	input.tickets = validtickets;
	std::vector<std::set<std::string>> fields_names_possibility;
	for (int col = 0; col < validtickets[0].size(); col++)
	{
		std::vector<int> fullcol;
		for (int line = 0; line < validtickets.size(); line++)
		{
			fullcol.push_back(validtickets[line][col]);
		}
		fields_names_possibility.push_back(valid_fields(fullcol, input));
	}

	auto fieldnames = deduce(fields_names_possibility);
	long long total = 1;
	for (int i = 0; i < fieldnames.size(); i++)
	{
		if (fieldnames[i].starts_with("departure"))
			total *= input.myticket[i];
	}
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();
	return 0;
}
