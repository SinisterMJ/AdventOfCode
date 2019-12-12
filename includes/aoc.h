// aoc.h
// Copyright (c) 2019, zhiayang
// Licensed under the Apache License Version 2.0.

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
#include <chrono>

namespace util
{
    class Timer {
    private:
        std::chrono::time_point<std::chrono::steady_clock> startP;
    public:
        Timer() {}
        void start() { startP = std::chrono::steady_clock::now(); }
        int64_t usPassed() { auto end = std::chrono::steady_clock::now(); return std::chrono::duration_cast<std::chrono::microseconds>(end - startP).count(); }
		int64_t msPassed() { auto end = std::chrono::steady_clock::now(); return std::chrono::duration_cast<std::chrono::milliseconds>(end - startP).count(); }
    };
	static inline std::string readFile(const std::string& path)
	{
		FILE* f;
		fopen_s(&f, path.c_str(), "r");
		std::string input;
		{
			fseek(f, 0, SEEK_END);

			long fsize = ftell(f);
			fseek(f, 0, SEEK_SET);  //same as rewind(f);

			char* s = new char[fsize + 1];
			fread(s, fsize, 1, f);
			fclose(f);
			s[fsize] = 0;

			input = std::string(s);
			while(input.back() == '\n')
				input.pop_back();
		}

		return input;
	}

	static inline std::vector<std::string> readFileLines(const std::string& path, char delim = '\n', bool skipEmpty = true)
	{
		std::vector<std::string> lines;
		{
			auto input = std::ifstream(path, std::ios::in);
			for(std::string line; std::getline(input, line, delim); )
			{
				if(!skipEmpty || !line.empty())
					lines.push_back(line);
			}
		}

		return lines;
	}

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string number;
        while (std::getline(ss, number, delim)) {
            elems.push_back(number);
        }
        return elems;
    }

	std::vector<int> splitInt(const std::string &s, char delim) {
		std::vector<int> elems;
		std::stringstream ss(s);
		std::string number;
		while (std::getline(ss, number, delim)) {
			elems.push_back(std::stoi(number));
		}
		return elems;
	}

	std::vector<int64_t> splitInt64(const std::string &s, char delim) {
		std::vector<int64_t> elems;
		std::stringstream ss(s);
		std::string number;
		while (std::getline(ss, number, delim)) {
			elems.push_back(std::stoll(number));
		}
		return elems;
	}
}

const double PI = 3.14159265359;

struct v2
{
	v2() : x(0), y(0) { }
	v2(int x, int y) : x(x), y(y) { }

	int x;
	int y;
    v2 operator + (const v2& a) const { return v2(a.x + x, a.y + y); }
    v2& operator+= (const v2& b) { x += b.x; y += b.y; return *this; }
    v2 operator - (const v2& a) const { return v2(x - a.x, y - a.y); }
    v2& operator-= (const v2& b) { x -= b.x; y -= b.y; return *this; }
    v2 operator / (const int div) const { return v2(x / div, y / div); }
    v2& operator/= (const int div) { x /= div; y /= div; return *this; }
};

bool operator == (const v2& a, const v2& b) { return a.x == b.x && a.y == b.y; }
bool operator < (const v2& a, const v2& b) { return a.x < b.x ? true : (b.x < a.x ? false : (a.y < b.y ? true : false)); }

bool operator > (const v2& a, const v2& b) { return b < a; }
bool operator != (const v2& a, const v2& b) { return !(a == b); }
bool operator <= (const v2& a, const v2& b) { return !(b < a); }
bool operator >= (const v2& a, const v2& b) { return !(a < b); }

struct v3
{
	v3() : x(0), y(0), z(0) { }
	v3(int x, int y, int z) : x(x), y(y), z(z) { }

	int x;
	int y;
	int z;

	int& operator[](int index)
	{
		if (index == 0)
			return x;
		if (index == 1)
			return y;
		return z;
	}
};

bool operator == (const v3& a, const v3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
bool operator < (const v3& a, const v3& b) { return a.x < b.x ? true : (b.x < a.x ? false : (a.y < b.y ? true : (b.y < a.y ? false : (a.z < b.z ? true : false)))); }

bool operator > (const v3& a, const v3& b) { return b < a; }
bool operator != (const v3& a, const v3& b) { return !(a == b); }
bool operator <= (const v3& a, const v3& b) { return !(b < a); }
bool operator >= (const v3& a, const v3& b) { return !(a < b); }


v3 operator + (const v3& a, const v3& b) { return v3(a.x + b.x, a.y + b.y, a.z + b.z); }
v3 operator - (const v3& a, const v3& b) { return v3(a.x - b.x, a.y - b.y, a.z - b.z); }


