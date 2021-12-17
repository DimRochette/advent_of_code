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
#include <stack>

using t_target = std::vector<int>;

auto view_to_int(std::string_view field)
{
	int output = 0;
	std::from_chars(field.data(), field.data() + field.size(), output);
	return output;
};

std::string replace_str(std::string& str, const std::string& from, const std::string& to)
{
	while (str.find(from) != std::string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}

auto read_values()
{
	t_target out;
	std::fstream fcin(advent_input().c_str());
	std::string tmp;
	std::getline(fcin, tmp);
	replace_str(tmp, "..", "=");
	for (auto subpos = tmp.find('='); std::string::npos != subpos; )
	{
		auto val = view_to_int(std::string_view(tmp.begin() + subpos+1, tmp.end()));
		out.push_back(val);
		tmp = tmp.substr(subpos+1);
		subpos = tmp.find('=');
	}
	return out;
}

auto steps(t_target& dest,int& x,int& y,int& vx, int& vy)
{
	x = x + vx;
	y = y + vy;
	if (vx != 0)
	{
		if (vx > 0)
			vx--;
		else
			vx++;
	}
	vy--;
	return (x>=dest[0] && (x<= dest[1]) && (y>=dest[2]) && (y<= dest[3]));	
}

void step1()
{
	auto data = read_values();
	int x, y, vx, vy;
	auto maxstepx = data[1];	
	auto higher_y = std::numeric_limits<int>::min();
	int total_hits = 0;
	for (int j = -100; j < 100; j++)
	{		
		bool hit = false;
		for (int i = 0; i <= maxstepx; i++)
		{
			vy = j;
			vx = i;
			x = 0;
			y = 0;
			auto local_besty = higher_y;
			hit = false;
			for (int step = 0; step < maxstepx; step++)
			{
				hit |= steps(data, x, y, vx, vy);
				local_besty = std::max(local_besty, y);
			}
			if (hit)
			{
				total_hits++;
				higher_y = local_besty;
			}
		}
	}
	std::cout << "step 1:" << higher_y << std::endl;
	std::cout << "step 2:" << total_hits << std::endl;
}

void SmallBench(auto fnct)
{
	auto start = std::chrono::steady_clock::now();
	fnct();
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << duration << " microseconds\n";
}

int main()
{
	SmallBench(step1);
	return 0;
}