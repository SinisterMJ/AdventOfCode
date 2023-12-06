#ifndef ADVENTOFCODE_AOC
#define ADVENTOFCODE_AOC

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdint.h>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <class T>
inline T modulo(T a, T b)
{
    return a >= 0 ? a % b : (b - std::abs(a % b)) % b;
}

template <class T>
inline bool in_range(T input, T low, T high)
{
    return low <= input && input <= high;
}

template <class T>
bool overlap(std::pair<T, T> left, std::pair<T, T> right)
{
    return (in_range(left.first, right.first, right.second) || in_range(right.first, left.first, left.second));
}

template <class T>
std::pair<T, T> merge_overlap(std::pair<T, T> left, std::pair<T, T> right)
{
    return std::make_pair(std::min<T>(left.first, right.first), std::max<T>(left.second, right.second));
}

namespace util
{
    bool replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        while (start_pos != std::string::npos)
        {
            str.replace(start_pos, from.length(), to);
            start_pos = str.find(from);
        }
        return true;
    }

    class Timer {
    private:
        std::chrono::time_point<std::chrono::steady_clock> startP;
    public:
        Timer() {}
        void start() { startP = std::chrono::steady_clock::now(); }
        int64_t nsPassed() { auto end = std::chrono::steady_clock::now(); return std::chrono::duration_cast<std::chrono::nanoseconds>(end - startP).count(); }
        int64_t usPassed() { auto end = std::chrono::steady_clock::now(); return std::chrono::duration_cast<std::chrono::microseconds>(end - startP).count(); }
		int64_t msPassed() { auto end = std::chrono::steady_clock::now(); return std::chrono::duration_cast<std::chrono::milliseconds>(end - startP).count(); }
    };

	static inline std::string readFile(const std::string& path)
	{
		FILE* f;
		fopen_s(&f, path.c_str(), "rb+");
		if (f == nullptr)
			return "";

		std::string input;
		{
			fseek(f, 0, SEEK_END);

			long fsize = ftell(f);
			fseek(f, 0, SEEK_SET);  //same as rewind(f);

			char* s = new char[fsize + 1];

#pragma warning( push )
#pragma warning( disable : 6386 )
			fread(s, fsize, 1, f);
#pragma warning( pop )

			fclose(f);
			s[fsize] = 0;

			input = std::string(s);
			while(input.back() == '\n' || input.back() == '\r')
				input.pop_back();

            delete[] s;
		}

		return input;
	}

	static inline std::vector<std::string> readFileLines(const std::string& path, char delim = '\n', bool skipEmpty = false)
	{
		std::vector<std::string> lines;
		{
			auto input = std::ifstream(path, std::ios::in);
			for(std::string line; std::getline(input, line, delim); )
			{
                if (line.empty() && skipEmpty)
                    continue;

			    lines.emplace_back(line);
			}

            if (lines.size() > 0 && lines.at(lines.size() - 1) == "")
            {
                lines.erase(lines.begin() + lines.size() - 1);
            }
		}

		return lines;
	}

    std::vector<std::string> split(std::string s, std::string delim) {
        std::vector<std::string> elems;

        while (s.find(delim) != std::string::npos) {
            elems.emplace_back(s.substr(0, s.find(delim)));
            s = s.substr(s.find(delim) + delim.size());
        }

        elems.emplace_back(s);

        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string number;
        while (std::getline(ss, number, delim)) {
            if (number == "")
                continue;

            elems.emplace_back(number);
        }
        return elems;
    }

	std::vector<int32_t> splitInt(const std::string &s, char delim) {
		std::vector<int32_t> elems;
		std::stringstream ss(s);
		std::string number;
		while (std::getline(ss, number, delim)) {
            if (number == "")
                continue;
			elems.emplace_back(std::stoi(number));
		}
		return elems;
	}

	std::vector<int64_t> splitInt64(const std::string &s, char delim) {
		std::vector<int64_t> elems;
		std::stringstream ss(s);
		std::string number;
		while (std::getline(ss, number, delim)) {
            if (number == "")
                continue;
			elems.emplace_back(std::stoll(number));
		}
		return elems;
	}

	std::vector<int64_t> ConvertToInt64(std::vector<std::string> &s) {
		std::vector<int64_t> elems;
		for (auto elem : s)
		{
			elems.emplace_back(std::stoll(elem));
		}
		return elems;
	}

	std::vector<int32_t> ConvertToInt(std::vector<std::string> &s) {
		std::vector<int32_t> elems;
		for (auto elem : s)
		{
			elems.emplace_back(std::stoi(elem));
		}
		return elems;
	}

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
}

const double PI = 3.14159265359;

struct v2
{
	v2() : x(0), y(0) { }
	v2(int x, int y) : x(x), y(y) { }
	int abs() { return std::abs(x) + std::abs(y); }
	int abs() const { return std::abs(x) + std::abs(y); }

    v2 getDirection()
    {
        if (x > 0)
            return v2(1, 0);
        if (x < 0)
            return v2(-1, 0);
        if (y > 0)
            return v2(0, 1);
        if (y < 0)
            return v2(0, -1);
        return v2(0, 0);
    }

    int32_t manhattan()
    {
        return std::abs(x) + std::abs(y);
    }

	int x;
	int y;
    v2 operator + (const v2& a) const { return v2(a.x + x, a.y + y); }
    v2& operator+= (const v2& b) { x += b.x; y += b.y; return *this; }
    
    v2 operator * (const int32_t& a) const { return v2(a * x, a * y); }
    v2& operator*= (const int32_t& b) { x *= b; y *= b; return *this; }

    v2 operator - (const v2& a) const { return v2(x - a.x, y - a.y); }
    v2& operator-= (const v2& b) { x -= b.x; y -= b.y; return *this; }
    v2 operator / (const int div) const { return v2(x / div, y / div); }
    v2& operator/= (const int div) { x /= div; y /= div; return *this; }

	int& operator[](int index)
	{
		if (index == 0)
			return x;
		return y;
	}

    bool operator == (const v2 a) { return x == a.x && y == a.y; }
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

    double length()
    {
        double l2 = x * x + y * y + z * z;
        return std::sqrt(l2);
    }

    int32_t manhattan()
    {
        return std::abs(x) + std::abs(y) + std::abs(z);
    }

    v3& operator+= (const v3& b) { x += b.x; y += b.y; z += b.z;  return *this; }
    v3& operator-= (const v3& b) { x -= b.x; y -= b.y; z -= b.z;  return *this; }
    v3& operator-= (const int32_t& b) { x *= b; y *= b; z *= b;  return *this; }
    v3 cross(const v3& b) 
    {
        v3 result;

        result.x = y * b.z - z * b.y;
        result.y = z * b.x - x * b.z;
        result.z = x * b.y - y * b.x;

        return result;
    }

	int& operator[](int index)
	{
		if (index == 0)
			return x;
		if (index == 1)
			return y;
		return z;
	}

    int operator[](int index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        return z;
    }

    v3 operator-() const
    {
        return v3(-x, -y, -z);
    }
};

bool operator == (const v3& a, const v3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
bool operator < (const v3& a, const v3& b) { return a.z != b.z ? a.z < b.z : a.x != b.x ? a.x < b.x : a.y < b.y; }

bool operator > (const v3& a, const v3& b) { return b < a; }
bool operator != (const v3& a, const v3& b) { return !(a == b); }
bool operator <= (const v3& a, const v3& b) { return !(b < a); }
bool operator >= (const v3& a, const v3& b) { return !(a < b); }


v3 operator + (const v3& a, const v3& b) { return v3(a.x + b.x, a.y + b.y, a.z + b.z); }
v3 operator - (const v3& a, const v3& b) { return v3(a.x - b.x, a.y - b.y, a.z - b.z); }
v3 operator * (const v3& a, const int32_t& b) { return v3(a.x * b, a.y * b, a.z * b); }

int operator * (const v3& a, const v3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct v4
{
    v4() : x(0), y(0), z(0), w(0) { }
    v4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) { }

    int x;
    int y;
    int z;
    int w;

    v4& operator+= (const v4& b) { x += b.x; y += b.y; z += b.z; w += b.w; return *this; }

    int& operator[](int index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;
        return w;
    }

    int operator[](int index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        if (index == 2)
            return z;

        return w;
    }
};

bool operator == (const v4& a, const v4& b) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
bool operator < (const v4& a, const v4& b) { return a.z != b.z ? a.z < b.z : a.x != b.x ? a.x < b.x : a.y != b.y ? a.y < b.y : a.w < b.w; }

bool operator > (const v4& a, const v4& b) { return b < a; }
bool operator != (const v4& a, const v4& b) { return !(a == b); }
bool operator <= (const v4& a, const v4& b) { return !(b < a); }
bool operator >= (const v4& a, const v4& b) { return !(a < b); }


v4 operator + (const v4& a, const v4& b) { return v4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
v4 operator - (const v4& a, const v4& b) { return v4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

namespace std
{
  template<> struct hash<v2>
  {
    inline size_t operator()(const v2 & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.x);
      ::hash_combine(seed, v.y);
      return seed;
    }
  };
}


int64_t mulInv(int64_t a, int64_t b) {
    int64_t b0 = b;
    int64_t x0 = 0;
    int64_t x1 = 1;

    if (b == 1) {
        return 1;
    }

    while (a > 1) {
        int64_t q = a / b;
        int64_t amb = a % b;
        a = b;
        b = amb;

        int64_t xqx = x1 - q * x0;
        x1 = x0;
        x0 = xqx;
    }

    if (x1 < 0) {
        x1 += b0;
    }

    return x1;
}

int64_t chineseRemainder(std::vector<int64_t> n, std::vector<int64_t> a) {
    int64_t prod = 1;

    for (auto elem : n)
        prod *= elem;

    int64_t sm = 0;
    for (uint64_t i = 0; i < n.size(); i++) {
        int64_t p = prod / n[i];
        sm += a[i] * mulInv(p, n[i])*p;
    }

    return sm % prod;
}

int64_t gcd(int64_t a, int64_t b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int64_t lcm(int64_t a, int64_t b)
{
    return (a * b) / gcd(a, b);
}

#endif  // ADVENTOFCODE_AOC