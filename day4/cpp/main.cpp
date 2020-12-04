#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>

using namespace std;

static tuple<bool, int> to_int(const string& s)
{
    if (s.empty()) return make_tuple(false, -1);
	try
	{
        auto t = stoi(s);
        return make_tuple(true, t);
	}
	catch(...)
	{
        return make_tuple(false, -1);
	}
}

std::vector<std::string> split(const std::string& text, const char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while (std::getline(ss, line, delim)) {
        vec.push_back(line);
    }
    return vec;
}

string replace(string str, const string& str2, const string& str3)
{
    return str.replace(str.find(str2), str2.length(), str3);
}

bool is_in_range(const string& s, const int v1, const int v2)
{
    bool valid;
    int year;
    tie(valid, year) = to_int(s);
    return valid && year >= v1 && year <= v2;
}

class Passport
{
public:
    string birth_year;
    string issue_year;
    string expire_year;
    string height;
    string hair_color;
    string eye_color;
    string passport_id;
    string country_id;

	bool naive_is_valid() const
	{
        auto fields_present = 0;
        if (!empty(birth_year)) fields_present++;
        if (!empty(issue_year)) fields_present++;
        if (!empty(expire_year)) fields_present++;
        if (!empty(height)) fields_present++;
        if (!empty(hair_color)) fields_present++;
        if (!empty(eye_color)) fields_present++;
        if (!empty(passport_id)) fields_present++;
        if (!empty(country_id)) fields_present++;
        const auto all_fields_present = fields_present == 8;
        const auto missing_cid = fields_present == 7 && empty(country_id);
        return all_fields_present || missing_cid;
    }
	bool is_valid() const
	{
        return birth_year_valid() && issue_year_valid() && expire_year_valid() && height_valid() && hair_color_valid() && eye_color_valid() && passport_id_valid();
	}
	
private:
	bool birth_year_valid() const
	{
        return is_in_range(birth_year, 1920, 2002);
	}
    bool issue_year_valid() const
    {
        return is_in_range(issue_year, 2010, 2020);
    }
    bool expire_year_valid() const
    {
        return is_in_range(expire_year, 2020, 2030);
    }
	bool height_valid() const
	{
		const auto is_cm = static_cast<int>(height.find("cm", 0)) >= 0;
        const auto is_in = static_cast<int>(height.find("in", 0)) >= 0;
		if (is_cm)
		{
			const auto tmp = replace(height, "cm", "");
            return is_in_range(tmp, 150, 193);
		}
		if (is_in)
		{
            const auto tmp = replace(height, "in", "");
            return is_in_range(tmp, 59, 76);
        }
        return false;
	}
	bool hair_color_valid() const
	{
		if (hair_color.rfind('#', 0) == 0)
		{
            auto tmp = replace(hair_color, "#", "");
            if (std::all_of(tmp.begin(), tmp.end(), ::isxdigit)) return true;
            return false;
		}
        return false;
    }
	bool eye_color_valid() const
	{
        auto valid_colors = vector<string>{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        auto key = eye_color;
        std::transform(key.begin(), key.end(), key.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return count(valid_colors.begin(), valid_colors.end(), key);
	}
	bool passport_id_valid() const
	{
		if (passport_id.length() == 9)
		{
            bool valid;
            int v;
            tie(valid, v) = to_int(passport_id);
            return valid;
        }
        return false;
	}
};

static vector<string> read_file(const string& filename)
{
    ifstream inf(filename);
    vector<string> lines;
    string line;
    for (unsigned int i = 1; getline(inf, line); ++i)
        lines.emplace_back(line);
    return lines;
}

static Passport parse_data(const vector<string>& input)
{
    auto res = Passport();
	for(const auto& item : input)
	{
        auto pairs = split(item, ' ');
		for(const auto& pair : pairs)
		{
            auto kvp = split(pair, ':');
            auto key = kvp[0];
            std::transform(key.begin(), key.end(), key.begin(),
                [](unsigned char c) { return std::tolower(c); });
            const auto value = kvp[1];
            if (key == "byr") res.birth_year = value;
            if (key == "iyr") res.issue_year = value;
            if (key == "eyr") res.expire_year = value;
            if (key == "hgt") res.height = value;
            if (key == "ecl") res.eye_color = value;
            if (key == "hcl") res.hair_color = value;
            if (key == "pid") res.passport_id = value;
            if (key == "cid") res.country_id = value;
        }
	}
    return res;
}

static vector<Passport> passports;

static void parse_passports(const vector<string>& lines)
{
    passports.clear();
	
    auto input = vector<string>();
	for(const auto& line : lines)
	{
		if (empty(line))
		{
            passports.emplace_back(parse_data(input));
            input.clear();
		} else
		{
            input.emplace_back(line);
		}
	}
	if (!input.empty()) passports.emplace_back(parse_data(input));
}

int main()
{
	const auto lines = read_file("c:\\temp\\aoc4f.txt");

    parse_passports(lines);    

    auto valid = 0;
	for(const auto& passport : passports)
	{
        if (passport.naive_is_valid()) valid++;
	}
    cout << "Valid: " << valid << " shall be 192\n";
    
    valid = 0;
	for(const auto& passport : passports)
	{
        if (passport.is_valid()) valid++;
	}
    cout << "Valid: " << valid << " shall be 101\n";
    passports.clear();
}
