#pragma once

#include <stdint.h>
#include "aoc.h"

template<class T>
class Map2DBase {
public:
	Map2DBase(int32_t _width_, int32_t _height_, T _emptyCell)
		: _width(_width_)
		, _height(_height_)
		, data(_width * _height)
		, emptyCell(_emptyCell)
	{

	}

	Map2DBase(v2 size, T _emptyCell)
		: _width(size.x)
		, _height(size.y)
		, data(_width * _height)
		, emptyCell(_emptyCell)
	{

	}

	~Map2DBase()
	{

	}

	bool validIndex(int32_t x, int32_t y)
	{
		return (x >= 0 && x < _width &&
				y >= 0 && y < _height);
	}

	bool validIndex(v2 pos)
	{
		return validIndex(pos.x, pos.y);
	}

	v2 find(T val)
	{
		auto it = std::find(data.begin(), data.end(), val);
		if (it == data.end())
		{
			return v2(-1, -1);
		}

		int index = std::distance(data.begin(), it);

		return v2(index % _width, index / _width);
	}

	T read(int32_t x, int32_t y)
	{
		return data[y * _width + x];
	}

    T read(v2 pos)
    {
		return read(pos.x, pos.y);
    }

	void write(int32_t x, int32_t y, T input)
	{
		data[y * _width + x] = input;
	}

	void write(v2 pos, T input)
	{
		write(pos.x, pos.y, input);
	}

    void inc(v2 pos, T val)
    {
        data[pos.y * _width + pos.x] += val;
    }

    int32_t height() { return _height; }
    int32_t width() { return _width; }

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
		data[y * _width + x] = emptyCell;
	}
	
	void remove(v2 pos)
	{
		remove(pos.x, pos.y);
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

private:
	int32_t _width;
	int32_t _height;

	T emptyCell;

	std::vector<T> data;
};