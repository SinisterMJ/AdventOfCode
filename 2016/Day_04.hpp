#ifndef ADVENTOFCODE2016_DAY04
#define ADVENTOFCODE2016_DAY04

#include "../includes/aoc.h"
#include <map>

class Day04 {
private:
	std::vector<std::string> inputVec;
	std::vector<std::string> validCodes;

	int part1()
	{
		int result = 0;

		for (auto elem : inputVec)
		{
			std::map<char, int> letters;

			for (auto ch : elem)
			{
				if (in_range<char>(ch, 'a', 'z'))
					letters[ch] += 1;
				
				if (in_range<char>(ch, '0', '9'))
					break;
			}

			auto pos_lastdash = elem.rfind('-');
			auto pos_checksum = elem.find('[');
			int id = std::stoi(elem.substr(pos_lastdash + 1, pos_checksum - pos_lastdash - 1));
			std::string checksum = elem.substr(pos_checksum + 1, 5);

			std::string truth = "";

			for (int i = 0; i < 5; i++)
			{
				if (truth.size() == 5)
					break;

				int max = 0;
				for (auto [key, count] : letters)
					max = std::max(max, count);

				for (auto& [key, count] : letters)
				{
					if (truth.size() == 5)
						break;

					if (count == max)
					{
						truth += key;
						count = 0;
					}
				}
			}

			if (truth == checksum)
			{
				result += id;
				validCodes.emplace_back(elem);
			}
		}

		return result;
	}

	int part2()
	{
		int result = 0;

		for (auto elem : inputVec)
		{
			auto pos_lastdash = elem.rfind('-');
			auto pos_checksum = elem.find('[');
			int id = std::stoi(elem.substr(pos_lastdash + 1, pos_checksum - pos_lastdash - 1));
			int orig_id = id;
			id = id % 26;

			for (auto& ch : elem)
			{
				if (in_range<char>(ch + id, 'a', 'z'))
					ch += id;
				else
					ch += id - 26;
			}

			if (elem.find("north") != std::string::npos)
				return orig_id;
		}

		return result;
	}

public:
	Day04()
	{
		inputVec = util::readFileLines("..\\inputs\\2016\\input_4.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

		std::cout << "Day 04 - Part 1: " << result_1 << std::endl
				  << "Day 04 - Part 2: " << result_2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2016_DAY04