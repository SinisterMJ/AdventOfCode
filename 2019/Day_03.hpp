#ifndef ADVENTOFCODE2019_DAY03
#define ADVENTOFCODE2019_DAY03

#include "../includes/aoc.h"
#include <map>
#include <iostream>
#include <vector>

class Day03 {
private:
	
	class WireLine {
	private:
		struct Line {
			int32_t startOffset;
			v2 start;
			v2 end;
			bool vertical;
		};

		std::vector<Line> lines;

	public:
		WireLine(std::string in)
		{
			std::vector<std::string> directions = util::split(in, ',');
			v2 start;
			v2 end;
			lines.reserve(directions.size());
			int32_t offset = 0;
			for (uint32_t index = 0; index < directions.size(); ++index)
			{
				Line line;
				v2 direction;
				if (directions[index].at(0) == 'L')
				{
					direction.x = -1;
					line.vertical = false;
				}

				if (directions[index].at(0) == 'R')
				{	
					direction.x = 1;
					line.vertical = false;
				}

				if (directions[index].at(0) == 'U')
				{
					direction.y = 1;
					line.vertical = true;
				}

				if (directions[index].at(0) == 'D')
				{
					direction.y = -1;
					line.vertical = true;
				}

				int32_t length = std::stoi(directions[index].substr(1));

				end = start + v2(direction.x * length, direction.y * length);
				line.start = start;
				line.end = end;
				line.startOffset = offset;

				lines.push_back(line);
				
				offset += length;
				start = end;
			}
		}

		std::map<v2, int> getPositionsWithSteps(std::vector<Line>& others)
		{	
			std::map<v2, int32_t> crossings;
			for (auto lineA : lines)
			{
				for (auto lineB : others)
				{
					if (lineA.vertical == lineB.vertical)
						continue;

					Line* vert = lineA.vertical ? &lineA : &lineB;
					Line* hori = lineA.vertical ? &lineB : &lineA;
					int32_t minX = hori->start.x < hori->end.x ? hori->start.x : hori->end.x;
					int32_t maxX = hori->start.x > hori->end.x ? hori->start.x : hori->end.x;
					int32_t minY = vert->start.y < vert->end.y ? vert->start.y : vert->end.y;
					int32_t maxY = vert->start.y > vert->end.y ? vert->start.y : vert->end.y;

					if (minY <= hori->start.y && hori->start.y <= maxY &&
						minX <= vert->start.x && vert->start.x <= maxX)
					{
						v2 crossing(vert->start.x, hori->start.y);

						if (crossings.find(crossing) != crossings.end())
							continue;

						int32_t total = vert->startOffset + hori->startOffset + 
							(crossing - vert->start).abs() + 
							(crossing - hori->start).abs();

						crossings[crossing] = total;
						
					}
				}
			}

			return crossings;
		}

		std::vector<Line>& getLines()
		{
			return lines;
		}
	};

	std::vector<std::string> inputs;
public:
	Day03()
	{
		inputs = util::readFileLines("..\\inputs\\2019\\input_3.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();

		WireLine AL(inputs[0]);
		WireLine BL(inputs[1]);

		auto map = AL.getPositionsWithSteps(BL.getLines());

		int32_t distance = std::numeric_limits<int32_t>::max();
		int32_t steps = std::numeric_limits<int32_t>::max();

		for (auto elem : map)
		{
			distance = std::min(distance, elem.first.abs());
			steps = std::min(steps, elem.second);
		}
		
		std::cout << "Day 03 - Part 1: " << distance << std::endl
				  << "Day 03 - Part 2: " << steps << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY03