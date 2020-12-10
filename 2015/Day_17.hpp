#ifndef ADVENTOFCODE2015_DAY17
#define ADVENTOFCODE2015_DAY17

#include <map>

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include <regex>

class Day17 {
private:
	const v2 north = v2(0, -1);
	const v2 south = v2(0, 1);
	const v2 west = v2(-1, 0);
	const v2 east = v2(1, 0);
	
	bool turnable(v2 direction, int& currentDirection, std::string& inout)
	{
		if (direction == north && (currentDirection == 'v' || currentDirection == '^'))
			return false;
		if (direction == south && (currentDirection == 'v' || currentDirection == '^'))
			return false;
		if (direction == west && (currentDirection == '<' || currentDirection == '>'))
			return false;
		if (direction == east && (currentDirection == '<' || currentDirection == '>'))
			return false;

		if ((direction == north && currentDirection == '<') ||
			(direction == west && currentDirection == 'v') ||
			(direction == south && currentDirection == '>') ||
			(direction == east && currentDirection == '^'))
			inout += "R";

		if ((direction == north && currentDirection == '>') ||
			(direction == west && currentDirection == '^') ||
			(direction == south && currentDirection == '<') ||
			(direction == east && currentDirection == 'v'))
			inout += "L";

		return true;
	}

	std::string createIntcodeString(std::string input)
	{
		std::string result = "";
		int offset = 0;

		for (auto character : input)
		{
			if (offset != 0 && (character == 'L' || character == 'R'))
				result += ',';

			result += character;
			++offset;

			if (character == 'L' || character == 'R')
				result += ',';
		}
		return result;
	}

	bool checkPatterns(std::string input, std::map<uint8_t, std::string>& dict)
	{
		uint64_t offset = 0;
		while (offset < input.length())
		{
			std::string subA = input.substr(offset, dict['A'].length());
			std::string subB = input.substr(offset, dict['B'].length());
			std::string subC = input.substr(offset, dict['C'].length());

			if (subA == dict['A'])
			{
				offset += dict['A'].length();
				continue;
			}

			if (subB == dict['B'])
			{
				offset += dict['B'].length();
				continue;
			}

			if (subC == dict['C'])
			{
				offset += dict['C'].length();
				continue;
			}

			return false;
		}

		return true;
	}

	std::map<uint8_t, std::string> findPatterns(std::string input)
	{
		int offset = 0;
		std::string substituted = input;
		std::map<std::string, bool> seen;
		uint8_t current = 'T';

		std::map<uint8_t, std::string> dict;
		dict['A'] = "";
		dict['B'] = "";
		dict['C'] = "";

		for (int lA = 20; lA > 0; --lA)
		{
			dict['A'] = input.substr(0, lA);
			if (createIntcodeString(dict['A']).length() > 20)
				continue;

			int offsetB = lA;

			for (int lB = 20; lB > 0; --lB)
			{
				while (input.substr(offsetB, lA) == dict['A'])
					offsetB += lA;

				dict['B'] = input.substr(offsetB, lB);

				if (createIntcodeString(dict['B']).length() > 20)
					continue;

				int offsetC = offsetB + lB;

				for (int lC = 20; lC > 0; --lC)
				{
					while (true)
					{
						if (input.substr(offsetC, lA) == dict['A'])
						{
							offsetC += lA;
							continue;
						}

						if (input.substr(offsetC, lB) == dict['B'])
						{
							offsetC += lB;
							continue;
						}

						break;
					}

					dict['C'] = input.substr(offsetC, lC);

					if (createIntcodeString(dict['B']).length() > 20)
						continue;

					if (checkPatterns(input, dict))
						goto PatternFound;
				}
			}
		}

PatternFound:
		return dict;
	}

	std::string findPath(std::map<v2, int>& cameraView)
	{
		v2 startPos(0, 0);
		int direction = 0;
		std::string result = "";
		std::map<v2, bool> movedTo;

		for (auto elem : cameraView)
		{
			if (elem.second == 'v' ||
				elem.second == '<' ||
				elem.second == '>' ||
				elem.second == '^')
			{
				startPos = elem.first;
				direction = elem.second;
			}

			movedTo[elem.first] = (elem.second != 35);
		}

		while (true)
		{
			// Find neighbour
			if (cameraView[startPos + north] == 35 && turnable(north, direction, result))
			{
				direction = '^';
				int count = 0;
				do {
					startPos += north;
					movedTo[startPos] = true;
					count++;
				} while (cameraView[startPos + north] == 35);
				result += std::to_string(count);
			}

			if (cameraView[startPos + south] == 35 && turnable(south, direction, result))
			{
				direction = 'v';
				int count = 0;
				do {
					startPos += south;
					movedTo[startPos] = true;
					count++;
				} while (cameraView[startPos + south] == 35);
				result += std::to_string(count);
			}

			if (cameraView[startPos + east] == 35 && turnable(east, direction, result))
			{
				direction = '>';
				int count = 0;
				do {
					startPos += east;
					movedTo[startPos] = true;
					count++;
				} while (cameraView[startPos + east] == 35);
				result += std::to_string(count);
			}

			if (cameraView[startPos + west] == 35 && turnable(west, direction, result))
			{
				direction = '<';
				int count = 0;
				do {
					startPos += west;
					movedTo[startPos] = true;
					count++;
				} while (cameraView[startPos + west] == 35);
				result += std::to_string(count);
			}

			bool foundOnlyTrue = true;
			for (auto elem : movedTo)
			{
				foundOnlyTrue &= elem.second;
			}

			if (foundOnlyTrue)
				break;
		}

		return result;
	}

	int64_t moveRobot(std::vector<int64_t> commands, std::map<v2, int>& cameraView)
	{
		IntcodeVM vm;
		commands[0] = 2;
		vm.initializeCommands(commands);
		auto output = vm.runCommands();

		std::string path = findPath(cameraView);

		auto patterns = findPatterns(path);
		std::vector<int64_t> pattern;

		uint64_t handled = 0;
		while (handled != path.length())
		{
			for (uint8_t base = 'A'; base <= 'C'; ++base)
			{
				std::string comparePattern = patterns[base];
				if (handled + comparePattern.length() > path.length())
					continue;

				if (comparePattern == path.substr(handled, comparePattern.length()))
				{
					pattern.push_back(base);
					handled += comparePattern.length();
					if (handled != path.length())
						pattern.push_back(',');
				}
			}
		}
		pattern.push_back(10);

		vm.addInput(pattern);

		for (auto elem : patterns)
		{
			int offset = 0;
			std::vector<int64_t> input = {};

			for (auto character : elem.second)
			{
				if (offset != 0 && (character == 'L' || character == 'R'))
					input.push_back(',');

				input.push_back(character);
				++offset;

				if (character == 'L' || character == 'R')
					input.push_back(',');
			}

			input.push_back('\n');
			vm.addInput(input);
		}

		std::vector<int64_t> input = { 'n', 10 };
		vm.addInput(input);

		output = vm.runCommands();

		std::string outputString = "";
		for (auto elem : output)
		{
			outputString += static_cast<unsigned char>(elem);
		}

		int64_t result = output.back();
		return result;
	}

	int getScaffolds(std::vector<int64_t> commands, std::map<v2, int32_t>& cameraView)
	{
		IntcodeVM vm;
		vm.initializeCommands(commands);
		auto output = vm.runCommands();

		v2 pos(-1, 0);

		for (int32_t index = 0; index < output.size(); ++index)
		{
			if (output[index] == 10)
			{
				pos.x = -1;
				pos.y++;
			}
			else
			{
				pos.x++;
				cameraView[pos] = static_cast<int32_t>(output[index]);
			}

		}

		int32_t minX, minY, maxX, maxY;
		minX = minY = maxX = maxY = 0;

		for (auto elem : cameraView)
		{
			minX = std::min(minX, elem.first.x);
			minY = std::min(minY, elem.first.y);
			maxX = std::max(maxX, elem.first.x);
			maxY = std::max(maxY, elem.first.y);
		}

		int32_t overlaps = 0;
		for (int y = minY + 1; y < maxY; ++y)
		{
			for (int x = minX + 1; x < maxX; ++x)
			{
				v2 currPos(x, y);
				if (cameraView[currPos] == 35)
				{
					if (cameraView[currPos + north] == 35 &&
						cameraView[currPos + south] == 35 &&
						cameraView[currPos + west] == 35 &&
						cameraView[currPos + east] == 35)
					{
						overlaps += currPos.x * currPos.y;
					}
				}
			}
		}

		// DrawMap(cameraView);

		return overlaps;
	}

	std::vector<std::string> inputVector;
	std::string inputString;

public:
	Day17()
	{
		inputString = util::readFile("..\\inputs\\2015\\input_17.txt");
		inputVector = util::readFileLines("..\\inputs\\2015\\input_17.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		
		std::map<v2, int32_t> cameraView;
		int64_t result1 = getScaffolds(commands, cameraView);
		int64_t result2 = moveRobot(commands, cameraView);

		std::cout << "Day 17 - Part 1: " << result1 << std::endl
				  << "Day 17 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2015_DAY17