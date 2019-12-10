#pragma once

#include <stdint.h>
#include <memory>

template<class T>
class Map2DBase {
public:
	Map2DBase(int32_t _width, int32_t _height, T _emptyCell)
		: width(_width)
		, height(_height)
		, data(new T[width * height])
		, emptyCell(_emptyCell)
	{

	}

	~Map2DBase()
	{
		delete[] data;
	}

	bool validIndex(int32_t x, int32_t y)
	{
		return (x >= 0 && x < width &&
				y >= 0 && y < height);
	}

	T read(int32_t x, int32_t y)
	{
		return data[y * width + x];
	}

	void write(int32_t x, int32_t y, T input)
	{
		data[y * width + x] = input;
	}

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

	void remove(int32_t x, int32_t y)
	{
		data[y * width + x] = emptyCell;
	}
		
	bool checkOccupation(int32_t x, int32_t y)
	{
		if (!validIndex(x, y))
			return false;
		
		T tempVal = read(x, y);
		
		return tempVal != emptyCell;
	}

private:
	int32_t width;
	int32_t height;

	T emptyCell;

	T* data;
};