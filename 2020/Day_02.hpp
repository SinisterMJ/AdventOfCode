#ifndef ADVENTOFCODE2020_DAY02
#define ADVENTOFCODE2020_DAY02

#include "../includes/aoc.h"
//#include <regex>

class Day02 {
private:
    struct Password {
        int32_t min;
        int32_t max;
        std::string password;
        char character;
    };

    std::vector<Password> passwords;
	std::string inputString;
    std::vector<std::string> inputVector;
public:

	Day02()
	{
		inputString = util::readFile("..\\inputs\\2020\\input_2.txt");
        inputVector = util::readFileLines("..\\inputs\\2020\\input_2.txt");
	}

    void parsePasswords() {
        /*std::regex password_regex("([0-9]*)-([0-9]*) ([a-z]): ([a-z]*)");
        std::smatch password_match;*/
        for (auto elem : inputVector)
        {
            int position_minus = static_cast<int>(elem.find('-'));
            int position_doppel = static_cast<int>(elem.find(':'));

            Password pw_out;
            pw_out.min = std::stoi(elem.substr(0, position_minus));
            pw_out.max = std::stoi(elem.substr(position_minus + 1, position_doppel - position_minus - 3));
            pw_out.character = elem.substr(position_doppel - 1, 1)[0];
            pw_out.password = elem.substr(position_doppel + 2);

            passwords.push_back(pw_out);

            /*if (std::regex_search(elem, password_match, password_regex))
            {
                Password pw;
                pw.min = std::stoi(password_match[1]);
                pw.max = std::stoi(password_match[2]);
                pw.character = password_match[3].str()[0];
                pw.password = password_match[4];
                passwords.push_back(pw);
            }*/
        }
    }

    int countPasswords() {
        int result = 0;

        for (auto pw : passwords)
        {
            int32_t count = static_cast<int32_t>(std::count(pw.password.begin(), pw.password.end(), pw.character));
            result += in_range(count, pw.min, pw.max);
        }

        return result;
    }

    int checkPasswords() {
        int result = 0;
        
        for (auto pw : passwords)
        {
            result += ((pw.password[pw.min - 1] == pw.character) ^ (pw.password[pw.max - 1] == pw.character));
        }

        return result;
    }

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        parsePasswords();

        int32_t result_1 = countPasswords();
        int32_t result_2 = checkPasswords();

        int64_t time = myTime.usPassed();

        std::cout << "Day 02 - Part 1: " << result_1 << '\n'
                  << "Day 02 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY02