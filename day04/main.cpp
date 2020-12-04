#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <charconv>
#include "fileinput.h"




void step1()
{
	std::vector<std::string> required = { "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" };
	int total = 0;
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
			if (std::all_of(required.begin(), required.end(), [&bigline](auto current) {
				return (bigline.find(current)) != std::string::npos; }))
				total++;
				bigline.clear();
		}

	}
	std::cout << "total 1:" << total << std::endl;
}

void step2()
{
	std::vector<std::string> required = { "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" };
	std::vector<std::string> eyes = { "amb","blu","brn","gry","grn","hzl","oth" };
	int total = 0;
	std::fstream fcin(advent_input().c_str());
	std::string bigline;
	while (!fcin.eof())
	{
		std::string line;
		std::getline(fcin, line);
		if (!line.empty())
			bigline += " " + line;
		else
		{
			std::vector<std::string_view> fields;
			for (auto& elem : required)
			{
				if (auto position = bigline.find(elem); position != std::string::npos)
				{
					auto field = std::string_view(bigline).substr(position + 4);
					field = field.substr(0, field.find_first_of(" \n"));
					fields.push_back(field);
				}
				else break;
			}
			if (fields.size() == required.size())
			{
				auto view_to_int = [](std::string_view field)
				{
					int output;
					std::from_chars(field.data(), field.data() + field.size(), output);
					return output;
				};

				for (;;)
				{
					auto year = view_to_int(fields[0]);
					if ((year < 1920) || (year > 2002))
						break;
					year = view_to_int(fields[1]);
					if ((year < 2010) || (year > 2020))
						break;
					year = view_to_int(fields[2]);
					if ((year < 2020) || (year > 2030))
						break;
					auto height = view_to_int(fields[3]);
					if (fields[3].back() == 'm')
					{
						if ((height < 150) || (height > 193))
							break;
					}
					else
					{
						if ((height < 59) || (height > 76))
							break;
					}
					if ((fields[4].front() == '#') && (fields[4].size() == 7))
					{
						auto digits = fields[4].substr(1);
						if (!std::all_of(digits.begin(), digits.end(), ::isxdigit))
							break;
					}
					else break;
					if (std::find(eyes.begin(), eyes.end(), fields[5]) == eyes.end())
						break;
					if (fields[6].length() == 9)
					{
						if (!std::all_of(fields[6].begin(), fields[6].end(), ::isdigit))
							break;
					}
					else break;
					total++;
					break;
				}
			}
			bigline.clear();
		}

	}
	std::cout << "total 2:" << total << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
