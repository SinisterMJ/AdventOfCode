#ifndef ADVENTOFCODE2021_DAY23
#define ADVENTOFCODE2021_DAY23

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"

class Day23 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    std::vector<v2> neighbours = MapHelper::getNeighboursVec(false);

    bool checkDone(std::map<v2, int8_t>& room)
    {
        bool result = true;
        for (auto [pos, val] : room)
        {
            if (val == 'A')
                result &= (pos.x == 3) && (pos.y >= 2);

            if (val == 'B')
                result &= (pos.x == 5) && (pos.y >= 2);
            
            if (val == 'C')
                result &= (pos.x == 7) && (pos.y >= 2);
            
            if (val == 'D')
                result &= (pos.x == 9) && (pos.y >= 2);
        }

        return result;
    }

    void print(std::map<v2, int8_t>& room)
    {
        int32_t min_y = 5;
        int32_t max_y = 0;

        for (auto [pos, val] : room)
        {
            min_y = std::min(pos.y, min_y);
            max_y = std::max(pos.y, max_y);
        }

        for (int y = min_y; y <= max_y; ++y)
        {
            for (int x = 0; x < 14; ++x)
            {
                v2 tempPos(x, y);
                if (room.find(tempPos) != room.end())
                {
                    std::cout << room[tempPos];
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    int32_t checkBelow(std::map<v2, int8_t>& room, int8_t val, v2 pos)
    {
        int32_t targetRow = 1;
        if (val == 'A')
            targetRow = 3;
        if (val == 'B')
            targetRow = 5;
        if (val == 'C')
            targetRow = 7;
        if (val == 'D')
            targetRow = 9;
        
        if (pos.x != targetRow)
            return -1;

        for (int y = pos.y + 1;; y++)
        {
            if (room.find(v2(targetRow, y)) == room.end() || room[v2(targetRow, y)] == val)
                return y - pos.y - 1;

            if (room[v2(targetRow, y)] != val && room[v2(targetRow, y)] != '.')
                return -1;
        }
    }

    bool checkAbove(std::map<v2, int8_t>& room, v2 pos)
    {
        for (int y = pos.y - 1; y > 1; y--)
        {
            if (room[v2(pos.x, y)] != '.')
                return false;
        }

        return true;
    }
    
    std::vector<std::pair<int32_t, v2>> findValidMoves(std::map<v2, int8_t>& room, v2 start)
    {
        std::vector<std::pair<int32_t, v2>> result;
        auto val = room[start];
        int32_t targetRow = 1;
        if (val == 'A')
            targetRow = 3;
        if (val == 'B')
            targetRow = 5;
        if (val == 'C')
            targetRow = 7;
        if (val == 'D')
            targetRow = 9;

        v2 east(1, 0);
        v2 west(-1, 0);
        v2 south(0, 1);
        v2 north(0, -1);
        
        if (start.y == 1) // left, right, south
        {
            {
                int steps = checkBelow(room, val, start + east);
                if (steps > 0)
                    result.push_back(std::make_pair(steps + 1, start + east + south * steps));
            }
            {
                int steps = checkBelow(room, val, start + west);
                if (steps > 0)
                    result.push_back(std::make_pair(steps + 1, start + west + south * steps));
            }
            if (start.x == 2 || start.x == 4 || start.x == 6 || start.x == 8)
                east = v2(2, 0);

            if (start.x == 4 || start.x == 6 || start.x == 8 || start.x == 10)
                west = v2(-2, 0);

            if (room.find(start + east) != room.end() && room[start + east] == '.')
                result.push_back(std::make_pair(std::abs(east.x), start + east));
            
            if (room.find(start + west) != room.end() && room[start + west] == '.')
                result.push_back(std::make_pair(std::abs(west.x), start + west));
        }

        if (start.y > 1 && checkAbove(room, start) && (checkBelow(room, val, start) != 0)) // north only with 1 west / east
        {
            int steps = start.y - 1;

            if (room.find(start + north * steps + east) != room.end() && room[start + north * steps + east] == '.')
                result.push_back(std::make_pair(steps + 1, start + north * steps + east));

            if (room.find(start + north * steps + west) != room.end() && room[start + north * steps + west] == '.')
                result.push_back(std::make_pair(steps + 1, start + north * steps + west));
        }

        return result;
    }

    int32_t runSteps(std::map<v2, int8_t>& rooms)
    {
        std::set<std::map<v2, int8_t>> states;
        std::set<std::pair<int32_t, std::map<v2, int8_t>>> candidates;
        std::map<v2, int8_t> room(rooms);

        std::map<int8_t, int32_t> costs;
        costs['A'] = 1;
        costs['B'] = 10;
        costs['C'] = 100;
        costs['D'] = 1000;
        std::vector<v2> sideSteps;
        sideSteps.push_back(v2(1, 0));
        sideSteps.push_back(v2(-1, 0));
        sideSteps.push_back(v2(0, 1));

        candidates.insert(std::make_pair(0, room));

        while (true)
        {
            auto cand = *candidates.begin();
            room = cand.second;
            int32_t cost = cand.first;
            candidates.erase(candidates.begin());

            if (states.find(room) == states.end())
                states.insert(room);
            else
                continue;

            //std::cout << cost << std::endl;  print(room);
   
            if (checkDone(room))
                return cost;
            
            for (auto [pos, val] : room)
            {
                if (val >= 'A' && val <= 'D')
                {
                    auto moves = findValidMoves(room, pos);

                    for (auto [steps, target] : moves)
                    {
                        room[target] = val;
                        room[pos] = '.';
                        cost += steps * costs[val];

                        candidates.insert(std::make_pair(cost, room));
                        
                        room[pos] = val;
                        room[target] = '.';
                        cost -= steps * costs[val];
                    }
                }
            }
        }

        return -1;
    }

    int64_t part1()
    {
        std::map<v2, int8_t> rooms;

        v2 pos;

        for (auto ln : inputVec)
        {
            for (auto ch : ln)
            {
                if (ch == ' ' || ch == '#')
                {
                    pos.x++;
                    continue;
                }
                rooms[pos] = ch;
                pos.x++;
            }
            pos.y++;
            pos.x = 0;
        }

        return runSteps(rooms);
    }

    int64_t part2()
    {
        std::map<v2, int8_t> rooms;

        inputVec.resize(inputVec.size() + 2);
        inputVec[6] = inputVec[4];
        inputVec[5] = inputVec[3];

        inputVec[3] = "  #D#C#B#A#";
        inputVec[4] = "  #D#B#A#C#";

        v2 pos;

        for (auto ln : inputVec)
        {
            for (auto ch : ln)
            {
                if (ch == ' ' || ch == '#')
                {
                    pos.x++;
                    continue;
                }
                rooms[pos] = ch;
                pos.x++;
            }
            pos.y++;
            pos.x = 0;
        }

        return runSteps(rooms);
    }

public:
    Day23()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_23.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_23.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 23 - Part 1: " << result_1 << '\n'
            << "Day 23 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
