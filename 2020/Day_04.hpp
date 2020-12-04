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

        int byr = std::stoi(elem.byr);
        if (!(1920 <= byr && byr <= 2002))
            return false;

        int iyr = std::stoi(elem.iyr);
        if (!(2010 <= iyr && iyr <= 2020))
            return false;

        int eyr = std::stoi(elem.eyr);
        if (!(2020 <= eyr && eyr <= 2030))
            return false;

        if (!(elem.ecl == "amb" || elem.ecl == "blu" || elem.ecl == "brn" || elem.ecl == "gry" || elem.ecl == "grn" || elem.ecl == "hzl" || elem.ecl == "oth"))
            return false;

        if (elem.pid.size() != 9)
            return false;

        if (elem.hcl[0] != '#' || elem.hcl.size() != 7)
            return false;

        bool cm = (elem.hgt.find("cm") != std::string::npos);
        std::string height = elem.hgt.substr(0, elem.hgt.size() - 2);
        int heightUnits = std::stoi(height);
        if (cm)
        {
            if (!(150 <= heightUnits && heightUnits <= 193))
                return false;
        }
        else
        {
            if (!(59 <= heightUnits && heightUnits <= 75))
                return false;
        }

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

            if (posByr != std::string::npos)
                entry.byr = sEntry.substr(posByr + 4, sEntry.find(' ', posByr + 4) - posByr - 4);
            else 
                continue;
            
            if (posIyr != std::string::npos)
                entry.iyr = sEntry.substr(posIyr + 4, sEntry.find(' ', posIyr + 4) - posIyr - 4);
            else
                continue;

            if (posEyr != std::string::npos)
                entry.eyr = sEntry.substr(posEyr + 4, sEntry.find(' ', posEyr + 4) - posEyr - 4);
            else
                continue;

            if (posHgt != std::string::npos)
                entry.hgt = sEntry.substr(posHgt + 4, sEntry.find(' ', posHgt + 4) - posHgt - 4);
            else
                continue;

            if (posHcl != std::string::npos)
                entry.hcl = sEntry.substr(posHcl + 4, sEntry.find(' ', posHcl + 4) - posHcl - 4);
            else
                continue;

            if (posEcl != std::string::npos)
                entry.ecl = sEntry.substr(posEcl + 4, sEntry.find(' ', posEcl + 4) - posEcl - 4);
            else
                continue;

            if (posPid != std::string::npos)
                entry.pid = sEntry.substr(posPid + 4, sEntry.find(' ', posPid + 4) - posPid - 4);
            else
                continue;

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