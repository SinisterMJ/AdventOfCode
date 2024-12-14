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
        int64_t min_y = 5;
        int64_t max_y = 0;

        for (auto [pos, val] : room)
        {
            min_y = std::min(pos.y, min_y);
            max_y = std::max(pos.y, max_y);
        }

        for (int64_t y = min_y; y <= max_y; ++y)
        {
            for (int x = 0; x < 14; ++x)
            {
                v2 tempPos(x, y);
                if (room.find(tempPos) != room.end())
                    std::cout << room[tempPos];
                else
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    std::string print_string(std::map<v2, int8_t>& room)
    {
        int64_t min_y = 5;
        int64_t max_y = 0;

        std::string res = "";

        for (auto [pos, val] : room)
        {
            min_y = std::min(pos.y, min_y);
            max_y = std::max(pos.y, max_y);
        }

        for (int64_t y = min_y; y <= max_y; ++y)
        {
            for (int x = 0; x < 14; ++x)
            {
                v2 tempPos(x, y);
                if (room.find(tempPos) != room.end())
                    res += room[tempPos];
                else
                    res += " ";
            }
            res += "\n";
        }

        return res;
    }

    int32_t checkBelow(std::map<v2, int8_t>& room, int8_t val)
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
                
        int32_t last_valid = -1;

        bool end_found = false;
        for (int y = 2; !end_found; y++)
        {
            if (room.find(v2(targetRow, y)) == room.end())
                break;

            if (room[v2(targetRow, y)] == '.')
                last_valid = y;

            if (room[v2(targetRow, y)] != val && room[v2(targetRow, y)] != '.')
                return -1;
        }

        return last_valid;
    }

    bool checkAbove(std::map<v2, int8_t>& room, v2 pos)
    {
        for (int64_t y = pos.y - 1; y > 1; y--)
        {
            if (room[v2(pos.x, y)] != '.')
                return false;
        }

        return true;
    }

    std::vector<std::pair<int64_t, v2>> findValidMoves(std::map<v2, int8_t>& room, v2 start)
    {
        std::vector<std::pair<int64_t, v2>> result;
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

        if (start.y == 1) // Find distance to own cell or nothing
        {
            // Check if way is free
            int64_t step = (targetRow - start.x) / std::abs(targetRow - start.x);

            for (int64_t x = start.x + step; x != targetRow; x += step)
                if (room[v2(x, 1)] != '.')
                    return result;
            
            // Check if space is free
            int steps = checkBelow(room, val);
            v2 target = v2(targetRow, steps);

            if (target.y == -1)
                return result;
            else
                result.push_back(std::make_pair((target - start).manhattan(), target));
        }
        else
        {
            // Check if path is free on top:
            if (!checkAbove(room, start))
                return result;

            // Go to the right:
            for (int64_t x = start.x;; ++x)
            {
                v2 pos(x, 1);
                if (room.find(pos) == room.end())
                    break;
                if (x == 3 || x == 5 || x == 7 || x == 9)
                    continue;
                if (room[pos] != '.')
                    break;

                result.push_back(std::make_pair((pos - start).manhattan(), pos));
            }

            // And the left...
            for (int64_t x = start.x;; --x)
            {
                v2 pos(x, 1);
                if (room.find(pos) == room.end())
                    break;
                if (x == 3 || x == 5 || x == 7 || x == 9)
                    continue;
                if (room[pos] != '.')
                    break;

                result.push_back(std::make_pair((pos - start).manhattan(), pos));
            }
        }

        return result;
    }

    int64_t runSteps(std::map<v2, int8_t>& rooms)
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
            int64_t cost = cand.first;
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
