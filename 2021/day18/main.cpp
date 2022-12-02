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
#include <variant>

using t_lines = std::vector<std::string>;

struct node;
using t_pnode = std::shared_ptr<node>;
struct node
{
	t_pnode left;
	t_pnode right;
	int value;
};

/*

auto read_values()
{
	std::fstream fcin(advent_input().c_str());
	t_lines lines;
	std::string tmp;
	while (!fcin.eof())
	{
		std::getline(fcin, tmp);
		lines.push_back(tmp);
	}
	return lines;
}

auto read_tree(std::string line)
{	
	auto root = std::make_shared<node>();
	std::stack<t_pnode> opens;
	t_pnode current = root;
	bool onleft = true;
	for (auto pos=line.begin()+1;pos<(line.end()-1);++pos)
	{
		switch (*pos)
		{
			case '[': 
			{
				auto next = std::make_shared<node>();
				if (onleft)
					current->left = next;
				else
					current->right = next;
				opens.push(current);
				current = next;
				onleft = true;
			} break;
			case ']':
			{
				onleft = true;
				current = opens.top();
				opens.pop();
			} break;
			case ',':
			{
				onleft = false;
			}
			break;
			default:
			{
				auto value = std::make_shared<node>();
				value->value = (*pos - '0');
				if (onleft)
				{
					current->left = value;
				}
				else
				{
					current->right = value;
				}
			}
			break;
		}
	}
	return root;
}

void print_tree(t_pnode& tree)
{
	if ((tree->left == nullptr) && (tree->right == nullptr))
	{
		std::cout << tree->value;
		return;
	}	
	std::cout << "[";
	print_tree(tree->left);
	std::cout << ",";	
	if (tree->right == nullptr)
	{
		std::cout << "*";		
	}
	else
		print_tree(tree->right);
	std::cout << "]";
}

t_pnode add(t_pnode left, t_pnode right)
{
	auto root = std::make_shared<node>();
	root->left = left;
	root->right = right;
	return root;
}

t_pnode findparent(std::stack<t_pnode>& branch, bool first_node_on_left)
{
	auto ret = branch.top();
	branch.pop();
	for (;;)
	{
		if (branch.size() == 0)
			return nullptr;
		if (first_node_on_left)
		{
			if (ret == branch.top()->left)
			{
				ret = branch.top();
				branch.pop();
			}
			else
			{
				ret = branch.top()->left;
				branch.push(ret);
				return ret;
			}
		}
		else
		{
			if (ret == branch.top()->right)
			{
				ret = branch.top();
				branch.pop();
			}
			else
			{
				ret = branch.top()->right;
				branch.push(ret);
				return ret;
			}
		}
	}
	return ret;
}

t_pnode findexplode(std::stack<t_pnode> branch, bool rightmost)
{	
	auto ret = findparent(branch, rightmost);
	if (rightmost)
	{
		for (; ret; ret = ret->right)
		{
			if ((ret->left == nullptr) && (ret->right == nullptr))
				return ret;
		}
	}
	else {
		for (; ret; ret = ret->left)
		{
			if ((ret->left == nullptr) && (ret->right == nullptr))
				return ret;
		}
	}	
	return nullptr;
}

t_pnode work(t_pnode root)
{
	auto current = root;
	std::stack<t_pnode> opens;
	for (;;)
	{
		if (opens.size() == 5)
		{
			current=opens.top();
			opens.pop();
			int left = current->left->value;
			int right = current->right->value;
			// find if left or right side
			// find left number or zero
			auto nleft=findexplode(opens, true);
			if (nleft)
				nleft->value+=left;
			// find right number or zero
			auto nright=findexplode(opens, false);
			if (nright)
				nright->value+=right;

			current->left = nullptr;
			current->right = nullptr;
			current->value = 0;
			break;
		}
		if (current->left)
		{
			opens.push(current);
			current = current->left;
			continue;
		}
		else if (current->right)
		{
			opens.push(current);
			current = current->left;
			continue;
		}
		else
		{
			//opens.pop();
			if (current == opens.top()->left)
			{
				current = opens.top()->right;
				continue;
			}			
			for (opens.pop(); current!=opens.top()->right;)
			{
				current = opens.top();
				opens.pop();
			}
			current = opens.top()->right;
			
		}
	}
	return root;	
}


void step1()
{
	auto data = read_values();
	auto total = 0;
	auto current=std::make_shared<node>();
	for (auto& lines : data)
	{
		auto ret = read_tree(lines);
		print_tree(ret);
		std::cout << "\n";
		current=work(ret);
		print_tree(current);
		//print_tree(current);
		
	}
	//print_tree(current);

	std::cout << "step 1:" << total << std::endl;
}

void step2()
{
	auto data = read_values();
	std::cout << "step 2:" << 2 << std::endl;
}

int main()
{
	step1();
	step2();

	return 0;
}
*/