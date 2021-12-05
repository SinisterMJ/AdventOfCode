#ifndef ADVENTOFCODE2020_DAY04
#define ADVENTOFCODE2020_DAY04

#include "../includes/aoc.h"
#include <regex>

class Day04 {
private:
    struct Passport {
        std::string byr;
        std::string iyr;
        std::string eyr;
        std::string hgt;
        std::string hcl;
        std::string ecl;
        std::string pid;
        bool valid;
    };

	std::vector<std::string> inputs;
    std::string input;

    std::vector<Passport> inputPassports;

    bool ValidPassport(Passport elem)
    {
        if (!((elem.byr != "") && (elem.ecl != "") && (elem.eyr != "") && (elem.hcl != "") && (elem.hgt != "") && (elem.iyr != "") && (elem.pid != "")))
            return false;

        if (!in_range(std::stoi(elem.byr), 1920, 2002))
            return false;

        if (!in_range(std::stoi(elem.iyr), 2010, 2020))
            return false;

        if (!in_range(std::stoi(elem.eyr), 2020, 2030))
            return false;

        if (!(elem.ecl == "amb" || elem.ecl == "blu" || elem.ecl == "brn" || elem.ecl == "gry" || elem.ecl == "grn" || elem.ecl == "hzl" || elem.ecl == "oth"))
            return false;

        if (elem.pid.size() != 9 || !util::is_number(elem.pid))
            return false;

        if (elem.hcl[0] != '#' || elem.hcl.size() != 7)
            return false;

        bool cm = (elem.hgt.find("cm") != std::string::npos);
        std::string height = elem.hgt.substr(0, elem.hgt.size() - 2);
        
        if (!in_range(std::stoi(height), 59 + 91 * cm, 76 + 117 * cm))
            return false;

        return true;
    }

    void ReadPassports() 
    {
        std::vector<std::string> fields{ "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" };
        auto list = util::split(input, "\n\n");

        for (auto sEntry : list)
        {        
            Passport entry;
            std::replace(sEntry.begin(), sEntry.end(), '\n', ' ');
            
            std::vector<size_t> pos;
            for (auto elem : fields)
            {
                auto _sPos = sEntry.find(elem);
                if (_sPos != std::string::npos)
                    pos.push_back(_sPos);
            }

            if (pos.size() != 7)
                continue;

            entry.byr = sEntry.substr(pos[0] + 4, sEntry.find(' ', pos[0] + 4) - pos[0] - 4);
            entry.iyr = sEntry.substr(pos[1] + 4, sEntry.find(' ', pos[1] + 4) - pos[1] - 4);
            entry.eyr = sEntry.substr(pos[2] + 4, sEntry.find(' ', pos[2] + 4) - pos[2] - 4);
            entry.hgt = sEntry.substr(pos[3] + 4, sEntry.find(' ', pos[3] + 4) - pos[3] - 4);
            entry.hcl = sEntry.substr(pos[4] + 4, sEntry.find(' ', pos[4] + 4) - pos[4] - 4);
            entry.ecl = sEntry.substr(pos[5] + 4, sEntry.find(' ', pos[5] + 4) - pos[5] - 4);
            entry.pid = sEntry.substr(pos[6] + 4, sEntry.find(' ', pos[6] + 4) - pos[6] - 4);
            
            entry.valid = ValidPassport(entry);

            inputPassports.push_back(entry);
        }
    }
public:    
	Day04()
	{
		inputs = util::readFileLines("..\\inputs\\2020\\input_4.txt", '\n', false);
        input = util::readFile("..\\inputs\\2020\\input_4.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        ReadPassports();
              
        auto result_1 = static_cast<int64_t>(inputPassports.size());
        auto result_2 = 0;

        for (auto elem : inputPassports)
        {
            result_2 += elem.valid;
        }
        
        int64_t time = myTime.usPassed();

        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';

        return time;
	}
};

#endif  // ADVENTOFCODE2020_DAY04