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
#include <bitset>

using t_iter = std::vector<bool>::iterator;

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	std::string tmp;
	std::getline(fcin, tmp);
	return tmp;
}

std::tuple<int, t_iter> read(t_iter pos, int nbbit)
{
	int out = 0;
	for (int i = 0; i < nbbit; i++)
	{
		out = out << 1;
		if (*pos)
			out |= 1;
		pos++;
	}

	return std::make_tuple(out, pos);
}

std::tuple<long long, t_iter> readnumber(t_iter pos)
{
	long long out = 0;
	for (;; out = out << 4)
	{
		auto [nibble, next] = read(pos, 5);
		pos = next;
		out = out | (nibble & 0xf);
		if (0 == (nibble & (1 << 4)))
		{
			break;
		}
	}
	return std::make_tuple(out, pos);
}

t_iter readpacket(t_iter from, long long& version_total, long long& result)
{

	decltype(from) pos;
	auto [version, nextheader] = read(from, 3);

	version_total += version;
	pos = nextheader;
	auto [pid, nextid] = read(pos, 3);
	pos = nextid;
	if (pid == 4)
	{
		auto [nb, next] = readnumber(pos);
		result = nb;
		pos = next;
	}
	else
	{
		// operator
		auto [id, nextoperator] = read(pos, 1);
		pos = nextoperator;
		std::vector<long long> values;
		if (id == 0)
		{
			auto [size, next] = read(pos, 15);
			pos = next;
			auto goal = pos + size;
			while (pos != goal)
			{
				long long tmp = 0;
				pos = readpacket(pos, version_total, tmp);
				values.push_back(tmp);
			}
		}
		else
		{
			// (id == 1)
			auto [count, next] = read(pos, 11);
			pos = next;
			for (int i = 0; i < count; i++)
			{
				long long tmp = 0;
				pos = readpacket(pos, version_total, tmp);
				values.push_back(tmp);
			}
		}
		enum class operation { sum = 0, mul = 1, min = 2, max = 3, greater = 5, lower = 6, equal = 7 };
		switch (static_cast<operation>(pid))
		{
		case operation::sum: result = std::accumulate(values.cbegin(), values.cend(), static_cast <long long>(0)); break;
		case operation::mul: result = std::accumulate(values.cbegin(), values.cend(), static_cast<long long>(1), [](auto acc, auto val) {return acc * val; }); break;
		case operation::min: result = *std::min_element(values.cbegin(), values.cend()); break;
		case operation::max: result = *std::max_element(values.cbegin(), values.cend()); break;
		case operation::greater: result = (values[0] > values[1]) ? 1 : 0; break;
		case operation::lower: result = (values[0] < values[1]) ? 1 : 0; break;
		case operation::equal: result = (values[0] == values[1]) ? 1 : 0; break;
		default:
			throw(1);
		}
	}
	return pos;
}

auto HexToBit(std::string from)
{
	if (0 != (from.size() % 16))
	{
		// keep always multiple of 16 complete with zero
		from.resize(from.size() + (16 - (from.size() % 16)), '0');
	}
	auto maximum = from.data() + from.size();
	std::vector<bool> output;
	output.reserve(from.size() * 4);
	for (auto iter = from.data(); iter < maximum; iter += 16)
	{
		unsigned long long val = 0;
		std::from_chars(iter, iter + 16, val, 16);
		for (int i = 0; i < 64; i++)
		{
			output.push_back(val & (1LL << 63));
			val = val << 1;
		}
	}
	return output;
}

void steps()
{
	auto data = read_values();
	auto ret = HexToBit(data);
	long long totalv = 0, result = 0;
	readpacket(ret.begin(), totalv, result);
	auto total = 0;
	std::cout << "step 1:" << totalv << std::endl;
	std::cout << "step 2:" << result << std::endl;
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
	SmallBench(steps);
	return 0;
}