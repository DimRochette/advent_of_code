#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <numeric>
#include <functional>
#include <tuple>
#include <vector>
#include <map>
#include <set>

auto split_to_string(std::string src)
{
	if (*src.rbegin() == '|')
		src.resize(src.size() - 2);

	std::istringstream is{ src };
	std::vector<std::string> out{ std::istream_iterator<std::string>(is), std::istream_iterator<std::string>() };

	return out;
}

using t_line = std::tuple<std::vector<std::string>, std::vector<std::string>>;
using t_lines = std::vector<t_line>;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string tmp;

	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		auto pos = std::find(tmp.begin(), tmp.end(), '|');
		auto distance = std::distance(tmp.begin(), pos);
		std::string ten(tmp.begin(), --pos);
		std::advance(pos, 3);
		std::string four(pos, tmp.end());
		lines.push_back({ split_to_string(ten),split_to_string(four) });
	}
	return lines;
}

void step1()
{
	auto data = read_values();
	std::map<int, int> result;
	for (auto& elem : data)
	{
		for (auto& digit : std::get<1>(elem))
		{
			result[digit.length()]++;
		}
	}
	// digit 1,4,7,8 >> lenght of string 2,4,3,7
	std::cout << "step 1:" << result[2] + result[4] + result[3] + result[7] << std::endl;
}
/*
  0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....

  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg
 */

auto decipher(t_line guess)
{
	// number of times lighted
	// a => 8
	// b => 6
	// c => 8
	// d => 7
	// e => 4
	// f => 9
	// g => 7

	std::vector<std::string> results(10);
	std::map<char, int> segment;
	for (auto& elem : std::get<0>(guess))
	{
		// len (2) => digit 1
		// len (3) => digit 7
		// len (4) => digit 4
		// len (5) => digit 2,3,5
		// len (6) => digit 0,6,9
		// len (7) => digit 8

		// segment count => segment name
		// 4 => e
		// 6 => b
		// 7 => d,g
		// 8 => a,c
		// 9 => f
		std::sort(elem.begin(), elem.end());
		switch (elem.size())
		{
		case 2: results[1] = elem; break;
		case 3: results[7] = elem; break;
		case 4: results[4] = elem; break;
		case 7: results[8] = elem; break;
		}
		std::for_each(elem.begin(), elem.end(), [&segment](auto val) {segment[val]++; });
	}
	std::string a, b, c, d, e, f, g;
	std::set<char> dg;
	// missing digit in 7 compare to 1 give a	
	std::set_difference(results[7].begin(), results[7].end(),
		results[1].begin(), results[1].end(),
		std::back_inserter(a));
	for (auto& elem : segment)
	{
		switch (elem.second)
		{
		case 4: e = elem.first; break;
		case 6: b = elem.first; break;
		case 8:
		{
			if (elem.first != a[0])
				c = elem.first;
		}
		break;
		case 7:
		{
			// d and g not sure
			dg.insert(elem.first);
		}
		break;
		case 9: f = elem.first; break;
		}
	}
	// intersection of digit 4 and candidate for d and g give us d
	std::set_intersection(results[4].begin(), results[4].end(),
		dg.begin(), dg.end(),
		std::back_inserter(d));
	// missing letter dg from d give us g
	std::set_difference(dg.begin(), dg.end(),
		d.begin(), d.end(),
		std::back_inserter(g));

	results[0] = a + b + c + e + f + g;
	results[2] = a + c + d + e + g;
	results[3] = a + c + d + f + g;
	results[5] = a + b + d + f + g;
	results[6] = a + b + d + e + f + g;
	results[9] = a + b + c + d + f + g;
	// sort alpha results
	for (auto& elem : results)
	{
		std::sort(elem.begin(), elem.end());
	}

	auto total = 0;
	auto multiple = 1000;
	for (auto& elem : std::get<1>(guess))
	{
		std::sort(elem.begin(), elem.end());
		auto pos = std::find(results.begin(), results.end(), elem);
		total += multiple * std::distance(results.begin(), pos);
		multiple = multiple / 10;
	}
	return total;
}

void step2()
{

	// la lettre dans len(3) en plus de len(2) est le digit aaaaa
	// la lettre len(6) = 0 ou 6 ou 9
	auto data = read_values();
	auto total = 0;
	for (auto& elem : data)
	{
		total += decipher(elem);
	}
	std::cout << "step 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
