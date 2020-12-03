#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int answer = 2020;

static int SolvePuzzle1(vector<int> input)
{
	for(auto i = 0; i < input.size(); i++)
	{
		for(auto j = 0; j < input.size(); j++)
		{
            auto sum = input[i] + input[j];
			if (sum == answer) return input[i] * input[j];
		}
	}
	return -1;
}

static int SolvePuzzle2(vector<int> input)
{
	for (auto i = 0; i < input.size(); i++)
	{
		for (auto j = 0; j < input.size(); j++)
		{
			for (auto k = 0; k < input.size(); k++)
			{
				auto sum = input[i] + input[j] + input[k];
				if (sum == answer)
				{
					return input[i] * input[j] * input[k];
				}
			}
		}
	}
	return -1;
}

int main()
{
	const string filename = "c:\\temp\\aoc1.txt";
    ifstream inf(filename);
    set<string> lines;
    string line;
    for (unsigned int i = 1; getline(inf, line); ++i)
        lines.insert(line);
    vector<int> ints;
    for (auto line : lines) ints.emplace_back(stoi(line));

	cout << "Puzzle 1 answer: " << SolvePuzzle1(ints) << "\n";
	cout << "Puzzle 2 answer: " << SolvePuzzle2(ints) << "\n";
}
