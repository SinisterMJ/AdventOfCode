#ifndef ADVENTOFCODE2020_DAY20
#define ADVENTOFCODE2020_DAY20

#include "../includes/aoc.h"

class Day20 {
private:
    class Tile {
    public:
        std::map<v2, uint8_t> layout;
        int32_t max_x = 0;
        int32_t max_y = 0;
        int32_t id;
        int32_t north[2];
        int32_t south[2];
        int32_t west[2];
        int32_t east[2];

        Tile() { }

        Tile(std::vector<std::string> _input, int32_t _id) : id(_id)
        {
            for (int y = 0; y < _input.size(); ++y)
            {
                for (int x = 0; x < _input[y].size(); ++x)
                {
                    max_x = std::max(max_x, x);
                    v2 pos(x, y);
                    layout[pos] = _input[y][x];
                }
                max_y = std::max(max_y, y);
            }

            if (_id == 3793)
                int breakHere = 0;
            updateBorders();
        }

        void drawMap() {
            for (int y = 0; y <= max_y; ++y)
            {
                for (int x = 0; x <= max_x; ++x)
                {
                    std::cout << layout[v2(x, y)];
                }
                std::cout << std::endl;
            }

            std::cout << std::endl;
        }

        void flip_x() 
        {
            std::map<v2, uint8_t> layout_new(layout);
            
            for (int y = 0; y <= max_y; ++y)
            { 
                for (int x = 0; x <= max_x; ++x)
                {
                    layout[v2(x, y)] = layout_new[v2(max_x - x, y)];
                }
            }

            updateBorders();
        }

        void flip_y() 
        {
            std::map<v2, uint8_t> layout_new(layout);

            for (int y = 0; y <= max_y; ++y)
            {
                for (int x = 0; x <= max_x; ++x)
                {
                    layout[v2(x, y)] = layout_new[v2(x, max_y - y)];
                }
            }

            updateBorders();
        }

        void rotate_180() 
        {
            flip_x();
            flip_y();
        }

        void rotate_90_ccw() 
        {
            rotate_90_cw();
            rotate_90_cw();
            rotate_90_cw();
        }

        void rotate_90_cw()
        {
            std::map<v2, uint8_t> layout_new(layout);

            for (int y = 0; y <= max_y; ++y)
            {
                for (int x = 0; x <= max_x; ++x)
                {
                    layout[v2(x, y)] = layout_new[v2(y, max_y - x)];
                }
            }

            updateBorders();
        }

        void updateBorders()
        {
            int32_t input = 0;
            int32_t input_reverse = 0;
            for (int32_t x = 0; x <= max_x; ++x)
            {
                v2 pos(x, 0);
                if (layout[pos] != '.')
                {
                    input |= (0x1 << x);
                    input_reverse |= (0x1 << (max_x - x));
                }
            }

            north[0] = input;
            north[1] = input_reverse;
            
            input = 0;
            input_reverse = 0;
            for (int32_t x = 0; x <= max_x; ++x)
            {
                v2 pos(x, max_y);
                if (layout[pos] != '.')
                {
                    input |= (0x1 << x);
                    input_reverse |= (0x1 << (max_x - x));
                }
            }
            south[0] = input;
            south[1] = input_reverse;
            
            input = 0;
            input_reverse = 0;
            for (int32_t y = 0; y <= max_y; ++y)
            {
                v2 pos(0, y);
                if (layout[pos] != '.')
                {
                    input |= (0x1 << y);
                    input_reverse |= (0x1 << (max_y - y));
                }
            }
            west[0] = input;
            west[1] = input_reverse;
            
            input = 0;
            input_reverse = 0;
            for (int32_t y = 0; y <= max_x; ++y)
            {
                v2 pos(max_x, y);
                if (layout[pos] != '.')
                {
                    input |= (0x1 << y);
                    input_reverse |= (0x1 << (max_y - y));
                }
            }
            east[0] = input;
            east[1] = input_reverse;
        }

        std::vector<int32_t> getBorders() 
        {
            std::vector<int32_t> borders;
            borders.push_back(north[0] < north[1] ? north[0] : north[1]);
            borders.push_back(south[0] < south[1] ? south[0] : south[1]);
            borders.push_back(west[0] < west[1] ? west[0] : west[1]);
            borders.push_back(east[0] < east[1] ? east[0] : east[1]);

            return borders;
        }
    };

    std::map<int32_t, Tile> tiles;
    std::map<v2, uint32_t> gridTiles;
    std::map<v2, uint8_t> grid;

    void flip_y(std::map<v2, uint8_t>& input)
    {
        std::map<v2, uint8_t> layout_new(input);

        for (int y = 0; y < 120; ++y)
        {
            for (int x = 0; x < 120; ++x)
            {
                std::cout << input[v2(x, y)];
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        for (int y = 0; y < 120; ++y)
        {
            for (int x = 0; x < 120; ++x)
            {
                input[v2(x, y)] = layout_new[v2(x, 119 - y)];
            }
        }

        for (int y = 0; y < 120; ++y)
        {
            for (int x = 0; x < 120; ++x)
            {
                std::cout << input[v2(x, y)];
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    void rotate_90_cw(std::map<v2, uint8_t>& input)
    {
        std::map<v2, uint8_t> layout_new(input);

        for (int y = 0; y < 120; ++y)
        {
            for (int x = 0; x < 120; ++x)
            {
                input[v2(x, y)] = layout_new[v2(y, 119 - x)];
            }
        }
    }

    void buildGrid(int64_t startGrid) 
    {
        auto borderStart = tiles[startGrid].getBorders();

        bool northUnique = count[borderStart[0]] == 1;
        bool southUnique = count[borderStart[1]] == 1;
        bool westUnique = count[borderStart[2]] == 1;
        bool eastUnique = count[borderStart[3]] == 1;

        if (northUnique && westUnique)
        {
            // We are happy with this
        }

        if (northUnique && eastUnique)
        {
            tiles[startGrid].rotate_90_ccw();
        }

        if (southUnique && westUnique)
        {
            tiles[startGrid].rotate_90_cw();
        }

        if (southUnique && eastUnique)
        {
            tiles[startGrid].rotate_180();
        }

        gridTiles[v2(0, 0)] = startGrid;
        for (int y = 0; y < 12; ++y)
        {
            int32_t idEast_border_former = tiles[gridTiles[v2(0, y)]].getBorders()[3];
            int32_t idEast_border_former_original = tiles[gridTiles[v2(0, y)]].east[0];
            int32_t idEast_former = gridTiles[v2(0, y)];

            for (int x = 1; x < 12; x++)
            {
                for (auto& elem : tiles)
                {
                    if (elem.first == idEast_former) continue;

                    auto borderIds = elem.second.getBorders();
                    for (int index = 0; index < borderIds.size(); ++index)
                    {
                        if (borderIds[index] == idEast_border_former)
                        {
                            // Matching tile, now orient it properly
                            switch (index)
                            {
                            case 0: elem.second.rotate_90_ccw(); break;
                            case 1: elem.second.rotate_90_cw(); break;
                            case 2: break;
                            case 3: elem.second.rotate_180(); break;
                            }

                            if (elem.second.west[0] != idEast_border_former_original)
                                elem.second.flip_y();

                            gridTiles[v2(x, y)] = elem.first;
                        }
                    }
                }

                idEast_border_former = tiles[gridTiles[v2(x, y)]].getBorders()[3];
                idEast_border_former_original = tiles[gridTiles[v2(x, y)]].east[0];
                idEast_former = gridTiles[v2(x, y)];
            }

            if (y < 11)
            {
                int32_t idSouth_border_former = tiles[gridTiles[v2(0, y)]].getBorders()[1];
                int32_t idSouth_border_former_original = tiles[gridTiles[v2(0, y)]].south[0];
                int32_t idSouth_former = gridTiles[v2(0, y)];
               
                for (auto& elem : tiles)
                {
                    if (elem.first == idSouth_former) continue;

                    auto borderIds = elem.second.getBorders();
                    for (int index = 0; index < borderIds.size(); ++index)
                    {
                        if (borderIds[index] == idSouth_border_former)
                        {
                            // Matching tile, now orient it properly
                            switch (index)
                            {
                            case 0: break;
                            case 1: elem.second.rotate_180(); break;
                            case 2: elem.second.rotate_90_cw(); break;
                            case 3: elem.second.rotate_90_ccw(); break;
                            }

                            if (elem.second.north[0] != idSouth_border_former_original)
                                elem.second.flip_x();

                            gridTiles[v2(0, y + 1)] = elem.first;
                        }
                    }
                }
            }
        }

        for (int y = 0; y < 12; ++y)
        {            
            for (int x = 0; x < 12; ++x)
            {
                v2 pos(0, y * 10);
                for (int grid_y = 0; grid_y < 10; ++grid_y, pos.y++)
                {                    
                    pos.x = x * 10;
                    for (int grid_x = 0; grid_x < 10; ++grid_x, pos.x++)
                    {
                        v2 pos_tile(grid_x, grid_y);
                        grid[pos] = tiles[gridTiles[v2(x, y)]].layout[pos_tile];
                    }
                }
            }
        }
    }

    int64_t part2(std::map<v2, uint8_t> grid, std::vector<std::string> pattern) 
    {
        int32_t monsterCount = 0;
        int32_t patternCount = 0;
        for (auto& elem : pattern)
        {
            patternCount += std::count(elem.begin(), elem.end(), '#');
        }

        for (int y = 1; y < 119; ++y)
        {
            for (int x = 1; x < 119; ++x)
            {
                int32_t match = 0;
                for (int y_m = 0; y_m < pattern.size(); ++y_m)
                {
                    for (int x_m = 0; x_m < pattern[y_m].size(); ++x_m)
                    {
                        if (pattern[y_m][x_m] == '#' && grid[v2(x + x_m, y + y_m)] == '#')
                            match++;
                    }
                }

                if (match == patternCount)
                {
                    monsterCount++;
                }
            }
        }

        return monsterCount * patternCount;
    }
    
    std::string inputString;
    std::vector<std::string> inputVec;
    int32_t count[1024];    

    std::vector<std::string> monster{
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

public:
    Day20()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_20.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_20.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        int64_t waveCount = std::count(inputString.begin(), inputString.end(), '#');

        int32_t currentId = -1;
        std::vector<std::string> tileLines{ };
        for (int index = 0; index < inputVec.size(); ++index)
        {
            if (inputVec[index].find("Tile ") != std::string::npos)
            {
                if (currentId != -1)
                {
                    tiles[currentId] = (Tile(tileLines, currentId));
                    tileLines.clear();
                }
                currentId = std::stoi(inputVec[index].substr(5, inputVec[index].find(":") - 5));
            }
            if (inputVec[index].find(".") != std::string::npos ||
                inputVec[index].find("#") != std::string::npos)
            {
                tileLines.push_back(inputVec[index]);
            }
        }

        tiles[currentId] = (Tile(tileLines, currentId));

        std::memset(count, 0x00000000, 1024 * sizeof(int32_t));
        for (auto& tile : tiles)
        {
            for (auto border : tile.second.getBorders())
            {
                count[border]++;
            }
        }

        int64_t multiply = 1;
        int64_t cornerID = -1;

        for (auto& tile : tiles)
        {
            auto borders = tile.second.getBorders();
            int8_t count_singles = 0;

            for (auto border : borders)
            {
                count_singles += (count[border] == 1);
            }

            if (count_singles == 2)
            {
                if (cornerID == -1)
                    cornerID = tile.first;

                multiply *= tile.first;
            }
        }

        //std::vector<std::string> sampleGrid{
        //    ".####...#####..#...###..",
        //    "#####..#..#.#.####..#.#.",
        //    ".#.#...#.###...#.##.##..",
        //    "#.#.##.###.#.##.##.#####",
        //    "..##.###.####..#.####.##",
        //    "...#.#..##.##...#..#..##",
        //    "#.##.#..#.#..#..##.#.#..",
        //    ".###.##.....#...###.#...",
        //    "#.####.#.#....##.#..#.#.",
        //    "##...#..#....#..#...####",
        //    "..#.##...###..#.#####..#",
        //    "....#.##.#.#####....#...",
        //    "..##.##.###.....#.##..#.",
        //    "#...#...###..####....##.",
        //    ".#.##...#.##.#.#.###...#",
        //    "#.###.#..####...##..#...",
        //    "#.###...#.##...#.######.",
        //    ".###.###.#######..#####.",
        //    "..##.#..#..#.#######.###",
        //    "#.#..##.########..#..##.",
        //    "#.#####..#.#...##..#....",
        //    "#....##..#.#########..##",
        //    "#...#.....#..##...###.##",
        //    "#..###....##.#...##.##.#" 
        //};

        //std::map<v2, uint8_t> sampleInput;
        //for (int y = 0; y < sampleGrid.size(); ++y)
        //{
        //    for (int x = 0; x < sampleGrid[y].size(); ++x)
        //    {
        //        sampleInput[v2(x, y)] = sampleGrid[y][x];
        //    }
        //}

        //int testCount = part2(sampleInput, monster);

        buildGrid(cornerID);

        int64_t result_1 = multiply;
        int64_t result_2 = 0;
        
        int count = 0;
        while (result_2 == 0)
        {
            result_2 = part2(grid, monster);
            rotate_90_cw(grid);
            count++;
            if (count == 4)
                flip_y(grid);
        }

        int64_t time = myTime.usPassed();
        std::cout << "Day 20 - Part 1: " << result_1 << '\n'
                  << "Day 20 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY20
