#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int solve(const vector<string> lines, const int xinc, const int yinc)
{
    auto xp = 0;
    auto count = 0;
    const auto line_width = lines[0].size();
    auto y = yinc;
    while (y < lines.size())
    {
        xp += xinc;
        const auto actual_xp = xp % line_width;
        auto prev_line = lines[y];

        if (prev_line[actual_xp] == '#') count++;
        y += yinc;
    }

    return count;
}

int main()
{
    const string filename = "c:\\temp\\aoc3f.txt";
    ifstream inf(filename);
    vector<string> lines;
    string line;
    for (unsigned int i = 1; getline(inf, line); ++i)
        lines.emplace_back(line);
	
    cout << "SolvePart 1: " << solve(lines, 3, 1) << " trees\n";

    vector<int> nums;
    nums.emplace_back(solve(lines, 1, 1));
    nums.emplace_back(solve(lines, 3, 1));
    nums.emplace_back(solve(lines, 5, 1));
    nums.emplace_back(solve(lines, 7, 1));
    nums.emplace_back(solve(lines, 1, 2));
    auto sum = 1;
    for (auto num : nums) sum *= num;
    cout << "SolvePart 2: " << sum << "\n";
}