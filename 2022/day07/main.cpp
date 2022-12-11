#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"
#include <ranges>
#include <numeric>
#include <regex>
#include <deque>
#include <tuple>
#include <any>
#include <map>

struct fsentry
{
	std::string path;
	std::string name;
	int size;
};

auto read_input()
{
	std::fstream file(advent_input().c_str());
	// assuming your file is open
	std::string line;
	std::string currentpath;
	std::vector<fsentry> ret{ {"/","root",0} };
	while (!file.eof())
	{
		getline(file, line);
		switch (line[0])
		{
		case '$': {
			if (line[2] == 'c')
			{
				if (line[5] == '.')
				{
					// up on dir
					auto pos = std::find(currentpath.rbegin(), currentpath.rend(), '/');
					if (pos != currentpath.rend())
					{
						auto cut_pos = std::distance(pos + 1, currentpath.rend());
						std::string old_dirname = currentpath.substr(cut_pos + 1);
						currentpath.resize(cut_pos);
						fsentry filename{ currentpath, old_dirname,0 };
						ret.push_back(filename);
						if (currentpath.empty())
							currentpath = "/";
					}
				}
				else
				{
					//down one dir
					if (!currentpath.empty() && currentpath.back() != '/')
						currentpath += '/';
					currentpath.append(line, 5);
				}
			}
		}
				break;
		case 'd': break;
		default:
		{
			auto namepos = std::find(line.begin(), line.end(), ' ');
			auto taille = std::stoi(line);
			fsentry filename{ currentpath, line.substr(std::distance(line.begin(),namepos)),taille };
			ret.push_back(filename);
		}
		break;
		}
	}
	return ret;
}

auto folder_recurse(std::vector<fsentry>& tree)
{
	std::map<std::string, long long> rescurse_size;
	for (auto posentry = tree.begin(); posentry != tree.end(); ++posentry)
	{
		if (rescurse_size.contains((*posentry).path)) continue;
		long long sum = 0;
		for (auto subtree = tree.begin(); subtree < tree.end(); ++subtree)
		{
			if ((*subtree).path.starts_with((*posentry).path))
			{
				sum += (*subtree).size;
			}
		}
		rescurse_size[(*posentry).path] = sum;
	}
	return rescurse_size;
}

auto sum_tree(const std::map<std::string, long long>& rescurse_size)
{
	auto total = std::accumulate(rescurse_size.begin(), rescurse_size.end(), 0ll, [](auto sum, const auto& item) {
		auto const& [key, value] = item;
	return sum + value;
		});
	return total;
}

void step1()
{
	auto tree = read_input();
	auto rescurse_size = folder_recurse(tree);

	// filter small entries
	std::erase_if(rescurse_size, [](const auto& item)
		{
			auto const& [key, value] = item;
	return value > 100'000;
		});

	auto total = sum_tree(rescurse_size);

	std::cout << "step 1:" << total << "\n";
}

void step2()
{
	auto tree = read_input();
	auto rescurse_size = folder_recurse(tree);
	auto total = rescurse_size["/"];

	auto objective = 30'000'000 - (70'000'000 - total);
	std::vector<std::pair<std::string, long long>> table;
	std::transform(
		rescurse_size.begin(),
		rescurse_size.end(),
		std::back_inserter(table),
		[](auto& kv) { return kv; }
	);
	std::sort(table.begin(), table.end(), [](const auto& a, const auto& b) {return a.second < b.second; });
	auto best = std::lower_bound(table.begin(), table.end(), objective, [](const auto& a, long long b)
		{return a.second < b; });

	std::cout << "step 2:" << (*best).second << "\n";

}

int main()
{
	step1();
	step2();
	return 0;
}
