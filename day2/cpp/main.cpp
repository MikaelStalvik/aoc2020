#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <tuple>

using namespace std;


class PasswordRule
{
public:
	int min_occurances;
	int max_occurances;
	string pwd_char;

    bool validate(string s) const
    {
	    int occurances = std::count(s.begin(), s.end(), pwd_char[0]);
	    const auto min_ok = occurances >= min_occurances;
	    const auto max_ok = occurances <= max_occurances;
        return min_ok && max_ok;
    }
	bool validate_2(string s) const
    {
        auto ok1 = s[min_occurances - 1] == pwd_char[0];
        auto ok2 = s[max_occurances - 1] == pwd_char[0];
        auto both_ok = ok1 && ok2;
        return (ok1 || ok2) && !both_ok;
    }
};

std::vector<std::string> split(const std::string text, const char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while (std::getline(ss, line, delim)) {
        vec.push_back(line);
    }
    return vec;
}

static tuple<PasswordRule, string> parse_rule(string s)
{
    auto res = PasswordRule();
    auto parts = split(s, ' ');
    auto ranges = split(parts[0], '-');
    res.min_occurances = stoi(ranges[0]);
    res.max_occurances = stoi(ranges[1]);
    res.pwd_char = parts[1].replace(parts[1].find(":"), 3, "");
    return make_tuple(res, parts[2]);
}

static void solve_part1(vector<string> raw_data)
{
    auto rules = vector<PasswordRule>();
    auto passwords = vector<string>();
	for(auto item : raw_data)
	{
        PasswordRule rule;
        string pwd;
        tie(rule, pwd) = parse_rule(item);
        rules.emplace_back(rule);
        passwords.emplace_back(pwd);
	}

    auto i = 0, res = 0;
    for(auto password : passwords)
    {
        if (rules[i].validate(password)) res++;
        i++;
    }
    cout << "Valid passwords: " << res << "\n";
}

static void solve_part2(vector<string> raw_data)
{
    auto rules = vector<PasswordRule>();
    auto passwords = vector<string>();
    for (auto item : raw_data)
    {
        PasswordRule rule;
        string pwd;
        tie(rule, pwd) = parse_rule(item);
        rules.emplace_back(rule);
        passwords.emplace_back(pwd);
    }

    auto i = 0, res = 0;
    for (auto password : passwords)
    {
        if (rules[i].validate_2(password)) res++;
        i++;
    }
    cout << "Valid passwords: " << res << "\n";
}

int main()
{
    const string filename = "c:\\temp\\aoc2.txt";
    ifstream inf(filename);
    vector<string> lines;
    string line;
    for (unsigned int i = 1; getline(inf, line); ++i)
        lines.emplace_back(line);

    solve_part1(lines);
    solve_part2(lines);
}