#ifndef ADVENTOFCODE2019_DAY17
#define ADVENTOFCODE2019_DAY17

#include <map>

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"

class Day17 {
private:
	const v2 north = v2(0, -1);
	const v2 south = v2(0, 1);
	const v2 west = v2(-1, 0);
	const v2 east = v2(1, 0);
	
	void DrawMap(std::map<v2, int>& map)
	{
		HANDLE hStdout;
		COORD destCoord;
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		//position cursor at start of window
		destCoord.X = 0;
		destCoord.Y = 0;
		SetConsoleCursorPosition(hStdout, destCoord);

		int minX = 0;
		int minY = 0;
		int maxX = 0;
		int maxY = 0;

		for (auto elem : map)
		{
			minX = std::min(minX, elem.first.x);
			maxX = std::max(maxX, elem.first.x);
			minY = std::min(minY, elem.first.y);
			maxY = std::max(maxY, elem.first.y);
		}

		std::string result = "";
		for (int y = minY; y <= maxY; ++y)
		{
			for (int x = minX; x <= maxX; ++x)
			{
				int val = map[v2(x, y)];

				if (val == 35)
					result += "#";
				else if (val == 46)
					result += ".";
				else if (val == 47)
					result += "O";
				else
					result += static_cast<unsigned char>(val);
			}
			result += "\n";
		}

		std::cout << result << std::endl;
		Sleep(15);
	}

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

	std::vector<std::string> findPatterns(std::string input)
	{
		std::vector<std::string> result;

		result.push_back("R8L10L12R4");
		result.push_back("R8L12R4R4");
		result.push_back("R8L10R8");

		/*int offset = 0;
/*
		while (result.size() < 3 && offset < input.length())
		{
			std::string substr;
			
			int countDir = 0;
			int index = 1;
			while (countDir < 5)
			{
				if (offset + index + 1 >= input.length())
					break;

				std::string internSubstr = input.substr(offset, index);
				if (input.find(internSubstr, offset + 1))
				{
					substr = internSubstr;
				}

				if (input.substr(offset + index, 1) == "R" ||
					input.substr(offset + index, 1) == "L")
					countDir++;
				index++;
			}

			if (std::find(result.begin(), result.end(), substr) == result.end())
			{
				result.push_back(substr);
				offset += substr.length();
			}
		}*/

		return result;
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

	int moveRobot(std::vector<int64_t> commands, std::map<v2, int>& cameraView)
	{
		IntcodeVM vm;
		commands[0] = 2;
		vm.initializeCommands(commands);
		auto output = vm.runCommands();

		std::string path = findPath(cameraView);

		auto patterns = findPatterns(path);
		std::vector<int64_t> pattern;

		int handled = 0;
		while (handled != path.length())
		{
			for (uint8_t base = 'A'; base <= 'C'; ++base)
			{
				std::string comparePattern = patterns[base - 'A'];
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

			for (auto character : elem)
			{
				if (offset != 0 && (character == 'L' || character == 'R'))
					input.push_back(',');

				input.push_back(character);
				++offset;

				if (character == 'L' || character == 'R')
					input.push_back(',');
			}

			input.push_back(10);
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

	int getScaffolds(std::vector<int64_t> commands, std::map<v2, int>& cameraView)
	{
		IntcodeVM vm;
		vm.initializeCommands(commands);
		auto output = vm.runCommands();

		v2 pos(-1, 0);

		for (int index = 0; index < output.size(); ++index)
		{
			if (output[index] == 10)
			{
				pos.x = -1;
				pos.y++;
			}
			else
			{
				pos.x++;
				cameraView[pos] = output[index];
			}

		}

		int minX, minY, maxX, maxY;
		minX = minY = maxX = maxY = 0;

		for (auto elem : cameraView)
		{
			minX = std::min(minX, elem.first.x);
			minY = std::min(minY, elem.first.y);
			maxX = std::max(maxX, elem.first.x);
			maxY = std::max(maxY, elem.first.y);
		}

		int overlaps = 0;
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
		inputString = util::readFile("..\\inputs\\input_2019_17.txt");
		inputVector = util::readFileLines("..\\inputs\\input_2019_17.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		std::vector<int64_t> commands = util::splitInt64(inputString, ',');
		
		std::map<v2, int> cameraView;
		int64_t result1 = getScaffolds(commands, cameraView);
		int64_t result2 = moveRobot(commands, cameraView);

		std::cout << "Day 17 - Part 1: " << result1 << std::endl
				  << "Day 17 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY17