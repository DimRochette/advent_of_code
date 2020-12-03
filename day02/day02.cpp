#include <iostream>
#include <sstream>
#include <string_view>
#include <fstream>
#include <algorithm>
#include "fileinput.h"

void step1()
{
	std::fstream fcin(advent_input().c_str());
	int total = 0;
	while (!fcin.eof())
	{
		int low, high;
		char letter;
		std::string word;
		fcin >> low >> high >> letter >> word;
		auto number = std::count_if(word.begin(), word.end(), [letter](auto elem) { return letter == elem; });
		if ((number >= low) && (number <= high))
			total++;
	}

	std::cout << "total:" << total << std::endl;
}

void step2()
{
	std::fstream fcin(advent_input().c_str());
	int total = 0;
	while (!fcin.eof())
	{
		int low, high;
		char letter;
		std::string word;
		fcin >> low >> high >> letter >> word;		
		low--;
		high--;
		if ((word[low] == letter) != (word[high] == letter)) 
			total++;		
	}

	std::cout << "total:" << total << std::endl;
}

int main()
{
	step1();
	step2();
	
	return 0;
}
