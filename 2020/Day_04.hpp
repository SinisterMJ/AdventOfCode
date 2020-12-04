#ifndef ADVENTOFCODE2020_DAY04
#define ADVENTOFCODE2020_DAY04

#include "../includes/aoc.h"

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
        std::string cid;
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

        if (elem.pid.size() != 9)
            return false;

        if (elem.hcl[0] != '#' || elem.hcl.size() != 7)
            return false;

        bool cm = (elem.hgt.find("cm") != std::string::npos);
        std::string height = elem.hgt.substr(0, elem.hgt.size() - 2);
        
        if (!in_range(std::stoi(height), 59 + 91 * cm, 76 + 117 * cm))
            return false;

        return true;
    }

    void ReadPassports() {
        int index = 0;
        
        for (; index < inputs.size();)
        {
            Passport entry;
            std::string sEntry = "";

            while (index < inputs.size() && inputs[index] != "")
            {
                sEntry += inputs[index] + " ";
                index++;
            }

            index++;

            auto posByr = sEntry.find("byr:");
            auto posIyr = sEntry.find("iyr:");
            auto posEyr = sEntry.find("eyr:");
            auto posHgt = sEntry.find("hgt:");
            auto posHcl = sEntry.find("hcl:");
            auto posEcl = sEntry.find("ecl:");
            auto posPid = sEntry.find("pid:");
            auto posCid = sEntry.find("cid:");

            if (posByr == std::string::npos ||
                posIyr == std::string::npos ||
                posEyr == std::string::npos ||
                posHgt == std::string::npos ||
                posHcl == std::string::npos ||
                posEcl == std::string::npos ||
                posPid == std::string::npos)
                continue;

            if (posByr != std::string::npos)
                entry.byr = sEntry.substr(posByr + 4, sEntry.find(' ', posByr + 4) - posByr - 4);
            
            if (posIyr != std::string::npos)
                entry.iyr = sEntry.substr(posIyr + 4, sEntry.find(' ', posIyr + 4) - posIyr - 4);

            if (posEyr != std::string::npos)
                entry.eyr = sEntry.substr(posEyr + 4, sEntry.find(' ', posEyr + 4) - posEyr - 4);

            if (posHgt != std::string::npos)
                entry.hgt = sEntry.substr(posHgt + 4, sEntry.find(' ', posHgt + 4) - posHgt - 4);

            if (posHcl != std::string::npos)
                entry.hcl = sEntry.substr(posHcl + 4, sEntry.find(' ', posHcl + 4) - posHcl - 4);

            if (posEcl != std::string::npos)
                entry.ecl = sEntry.substr(posEcl + 4, sEntry.find(' ', posEcl + 4) - posEcl - 4);

            if (posPid != std::string::npos)
                entry.pid = sEntry.substr(posPid + 4, sEntry.find(' ', posPid + 4) - posPid - 4);

            if (posCid != std::string::npos)
                entry.cid = sEntry.substr(posCid + 4, sEntry.find(' ', posCid + 4) - posCid - 4);

            entry.valid = ValidPassport(entry);

            inputPassports.push_back(entry);
        }
    }
public:    
	Day04()
	{
		inputs = util::readFileLines("..\\inputs\\input_2020_4.txt", '\n', false);
        input = util::readFile("..\\inputs\\input_2020_4.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
        
        ReadPassports();
              
        int64_t result_1 = static_cast<int64_t>(inputPassports.size());
        int64_t result_2 = 0;

        for (auto elem : inputPassports)
        {
            result_2 += elem.valid;
        }
        
        std::cout << "Day 04 - Part 1: " << result_1 << '\n'
                  << "Day 04 - Part 2: " << result_2 << '\n';
                
		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2020_DAY04