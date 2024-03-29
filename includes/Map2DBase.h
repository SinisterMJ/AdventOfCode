#pragma once

#include <stdint.h>
#include <map>
#include <iostream>

#include "aoc.h"

#define NOMINMAX
#include <Windows.h>

template<class T>
class Map2DBase {
public:
	
    Map2DBase(T _emptyCell)
		: _minX(std::numeric_limits<int32_t>::max())
		, _minY(std::numeric_limits<int32_t>::max())
		, _maxX(std::numeric_limits<int32_t>::min())
		, _maxY(std::numeric_limits<int32_t>::min())
		, emptyCell(_emptyCell)
	{

	}

	Map2DBase()
		: _minX(std::numeric_limits<int32_t>::max())
		, _minY(std::numeric_limits<int32_t>::max())
		, _maxX(std::numeric_limits<int32_t>::min())
		, _maxY(std::numeric_limits<int32_t>::min())
		, emptyCell(0)
	{

	}

	~Map2DBase()
	{

	}

	bool validIndex(int32_t x, int32_t y)
	{
		return validIndex(v2(x, y));
	}

	bool validIndex(v2 pos)
	{
		return dataMap.find(pos) != dataMap.end();
	}

	v2 find(T val)
	{
		for (auto elem : dataMap)
		{
			if (elem.second == val)
				return elem.first;
		}

		return v2(-1, -1);
	}

	std::vector<v2> findAll(T val)
	{
		std::vector<v2> allPositions;
		for (auto& elem : dataMap)
		{
			if (elem.second == val)
				allPositions.emplace_back(elem.first);
		}

		return allPositions;
	}

    int32_t countAll(T val)
    {
        int32_t count = 0;
        for (auto elem : dataMap)
        {
            if (elem.second == val)
                count++;
        }

        return count;
    }

	T read(int32_t x, int32_t y)
	{
		return read(v2(x, y));
	}

    T read(v2 pos)
    {
		return dataMap[pos];
    }

	void write(int32_t x, int32_t y, T input)
	{
		write(v2(x, y), input);
	}

	void write(v2 pos, T input)
	{
		_minX = std::min(_minX, pos.x);
		_maxX = std::max(_maxX, pos.x);
		_minY = std::min(_minY, pos.y);
		_maxY = std::max(_maxY, pos.y);

		dataMap[pos] = input;
	}

    void inc(v2 pos, T val)
    {
		dataMap[pos] += val;
    }

    int64_t height() { return _maxY - _minY + 1; }
    int64_t width() { return _maxX - _minX + 1; }
	
	int64_t minX() { return _minX; }
	int64_t minY() { return _minY; }
	int64_t maxX() { return _maxX; }
	int64_t maxY() { return _maxY; }

	bool move(int32_t from_x, int32_t from_y, int32_t to_x, int32_t to_y, bool checkOccupation = true)
	{
		if (!(validIndex(from_x, from_y) && validIndex(to_x, to_y)))
			return false;

		T tempVal = read(from_x, from_y);

		if (checkOccupation && read(to_x, to_y) != emptyCell)
			return false;

		write(to_x, to_y, tempVal);
		write(from_x, from_y, emptyCell);

		return true;
	}

	bool move(v2 from, v2 to, bool checkOccupation = true)
	{
		return move(from.x, from.y, to.x, to.y, checkOccupation);
	}

	void remove(int32_t x, int32_t y)
	{
		remove(v2(x, y));
	}
	
	void remove(v2 pos)
	{
		dataMap[pos] = emptyCell;
	}

	bool checkOccupation(int32_t x, int32_t y)
	{
		if (!validIndex(x, y))
			return false;
		
		T tempVal = read(x, y);
		
		return tempVal != emptyCell;
	}

	bool checkOccupation(v2 pos)
	{
		return checkOccupation(pos.x, pos.y);
	}

	std::map<v2, T>& getMap()
	{
		return dataMap;
	}

private:
	int64_t _minY;
	int64_t _minX;
	int64_t _maxY;
	int64_t _maxX;

	T emptyCell;

	std::map<v2, T> dataMap;
};

void DrawMap(std::map<v2, int>& map, const std::map<int, uint8_t>& dict, bool resetScreen = true)
{
	if (resetScreen)
	{
		HANDLE hStdout;
		COORD destCoord;
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		//position cursor at start of window
		destCoord.X = 0;
		destCoord.Y = 0;
		SetConsoleCursorPosition(hStdout, destCoord);
	}

	int64_t minX = 0;
	int64_t minY = 0;
	int64_t maxX = 0;
	int64_t maxY = 0;

	for (auto& elem : map)
	{
		minX = std::min(minX, elem.first.x);
		maxX = std::max(maxX, elem.first.x);
		minY = std::min(minY, elem.first.y);
		maxY = std::max(maxY, elem.first.y);
	}

	std::string result = "";
	for (int64_t y = minY; y <= maxY; ++y)
	{
		for (int64_t x = minX; x <= maxX; ++x)
		{
			int val = map[v2(x, y)];
			if (dict.find(val) == dict.end())
			{
				result += static_cast<unsigned char>(val);
				continue;
			}

			result += dict.at(val);
		}
		result += "\n";
	}

	std::cout << result << std::endl;
}

void DrawMap(std::map<v2, int8_t>& map, bool resetScreen = true)
{
    if (resetScreen)
    {
        HANDLE hStdout;
        COORD destCoord;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        //position cursor at start of window
        destCoord.X = 0;
        destCoord.Y = 0;
        SetConsoleCursorPosition(hStdout, destCoord);
    }

	int64_t minX = 0;
	int64_t minY = 0;
	int64_t maxX = 0;
	int64_t maxY = 0;

    for (auto &elem : map)
    {
        minX = std::min(minX, elem.first.x);
        maxX = std::max(maxX, elem.first.x);
        minY = std::min(minY, elem.first.y);
        maxY = std::max(maxY, elem.first.y);
    }

    std::string result = "";
    for (int64_t y = minY; y <= maxY; ++y)
    {
        for (int64_t x = minX; x <= maxX; ++x)
        {
            int8_t val = map[v2(x, y)];
            
            result += val;
        }
        result += "\n";
    }

    std::cout << result << std::endl;
}