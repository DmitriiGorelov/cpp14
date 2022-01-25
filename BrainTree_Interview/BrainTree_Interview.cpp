// C14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;

int mostBalancedPartition(vector<int> parent, vector<int> files_size) {

	if (parent.size() < 1)
		return 0;

	vector<int> dirs_size(parent.size(), 0);

	for (int i = (int)parent.size() - 1; i >= 0; i--)
	{
		int idx = i;
		int s = files_size[i];
		files_size[i] = 0;
		while (idx >= 0)
		{
			dirs_size[idx] += s;
			int p = parent[idx];
			if (p < 0)
				break;
			s += files_size[p];
			files_size[p] = 0;
			idx = p;
		}
	}

	int minv = dirs_size[0];
	for (size_t i = 1; i < dirs_size.size(); i++)
	{
		files_size[i] = abs(2 * dirs_size[i] - dirs_size[0]);
		if (files_size[i] < minv) minv = files_size[i];
	}

	return minv;
}

int bestTrio(int friends_nodes, vector<int> friends_from, vector<int> friends_to) {

	using iterator = decltype(friends_from)::iterator;


	std::map<int, std::vector<iterator> > relations;

	auto it2 = friends_to.begin();
	for (auto it1 = friends_from.begin(); it1 != friends_from.end(); it1++)
	{
		relations[*it1].emplace_back(it2);

		it2++;
	}

	auto it1 = friends_from.begin();
	for (auto it2 = friends_to.begin(); it2 != friends_to.end(); it2++)
	{
		relations[*it2].emplace_back(it1);

		it1++;
	}

	int mins = friends_nodes;
	bool b = false;
	//std::vector<std::tuple<int, int, int> > trios;
	for (auto it : relations)
	{
		if (it.second.size() > 1)
		{
			for (auto n : it.second)
			{
				for (auto m : relations[*n])
				{
					for (auto l : relations[*m])
					{
						if (*l == it.first)
						{
							//trios.emplace_back(std::make_tuple(it.first, *n, *m));

							int s = relations[it.first].size() + relations[*n].size() + relations[*m].size() - 6;
							if (s <= mins)
							{
								b = true;
								mins = s;
							}
						}
					}
				}
			}
		}
	}

	/*int mins = friends_nodes;
	bool b = false;
	for (auto it : trios)
	{
	int s = relations[std::get<0>(it)].size()+ relations[std::get<1>(it)].size()+ relations[std::get<2>(it)].size()-6;
	if (s <= mins)
	{
	b = true;
	mins = s;
	}
	}*/

	return (b ? mins : -1);
}



int main()
{
	std::cout << mostBalancedPartition({ -1,0,0,1,1,1,2,2 }, { 1,2,3,2,1,1,1,2 }) << "\n";

	std::cout << bestTrio(6, { 1,2,2,3,4,5 }, { 2,4,5,5,5,6 });

	return 0;
}

