#ifndef ADVENTOFCODE2019_DAY22
#define ADVENTOFCODE2019_DAY22

#include "../includes/aoc.h"
#include "../includes/IntcodeVM.h"
#include "../includes/Map2DBase.h"
#include <algorithm>
#include <numeric>
#include <map>
#include <deque>
#include <set>
#include <unordered_set>
#include <regex>

class Day22 {
private:
	std::string inputString;
	std::vector<std::string> inputVector;
	
	int64_t moduloMultiplication(int64_t a,
		int64_t b,
		int64_t mod)
	{
		int64_t res = 0; // Initialize result 

		// Update a if it is more than 
		// or equal to mod 
		a %= mod;

		while (b)
		{
			// If b is odd, add a with result 
			if (b & 1)
				res = (res + a) % mod;

			// Here we assume that doing 2*a 
			// doesn't cause overflow 
			a = (2 * a) % mod;

			b >>= 1; // b = b / 2 
		}

		return res;
	}

	int64_t modular(int64_t base, int64_t exp, int64_t mod)
	{
		int64_t x = 1;
		int64_t i;
		int64_t power = base % mod;

		for (i = 0; i < sizeof(int64_t) * 8; i++) {
			int64_t least_sig_bit = 0x00000001 & (exp >> i);
			if (least_sig_bit)
				x = moduloMultiplication(x, power, mod);
			power = moduloMultiplication(power, power, mod);
		}

		return x;
	}

	int64_t modInverse(int64_t input, int64_t power, int64_t modulo)
	{
		int64_t original = modulo;

		int64_t y = 0;
		int64_t x = 1;

		if (original == 1)
			return 0;

		while (input > 1)
		{
			int64_t q = input / modulo;
			int64_t t = modulo;
			modulo = input % modulo;
			input = t;
			t = y;
			y = x - q * y;
			x = t;
		}

		if (x < 0)
			x += original;

		return x;
	}

	int64_t calcSecondDeck(int64_t count, int64_t iterations, std::vector<std::string> manipulations, int64_t targetSlot)
	{
		std::regex increment("deal with increment (.*)");
		std::regex cut("cut (.*)");

		std::smatch match;

		int64_t a = 1;
		int64_t b = 0;
		
		for (int64_t index = manipulations.size() - 1; index >= 0; --index)
		{
			std::string order = manipulations[index];
			if (order == "deal into new stack")
			{
				b++;
				b *= -1;
				a *= -1;
			}

			if (std::regex_search(order, match, increment) && match.size() > 1)
			{
				int64_t inc = std::stoi(match[1]);

				int64_t inversePower = modInverse(inc, iterations, count);
				a = moduloMultiplication(a, inversePower, count);
				b = moduloMultiplication(b, inversePower, count);
			}

			if (std::regex_search(order, match, cut) && match.size() > 1)
			{
				int64_t icut = std::stoi(match[1]);
				if (icut < 0)
				{
					icut += count;
				}
				b += icut;
			}

			a %= count;
			b %= count;
			if (b < 0)
				b += count;
			if (a < 0)
				a += count;
		}

		int64_t first = moduloMultiplication(modular(a, iterations, count), targetSlot, count);
		int64_t second = (modular(a, iterations, count) + count - 1) % count;
		int64_t third = moduloMultiplication(b, second, count);
		int64_t fourth = modular(a - 1, count - 2, count);
		
		int64_t result = (first + moduloMultiplication(third, fourth, count)) % count;

		return result;
	}

	int64_t calcFirstDeck(int64_t count, std::vector<std::string> manipulations, int64_t targetCard)
	{
		std::vector<int64_t> start;
		for (int index = 0; index < count; ++index)
		{
			start.push_back(index);
		}

		std::vector<int64_t> temp;
		temp.reserve(count);

		std::regex increment("deal with increment (.*)");
		std::regex cut("cut (.*)");

		std::smatch match;

		for (auto order : manipulations)
		{
			temp.clear();

			if (order == "deal into new stack")
				for (int64_t index = start.size() - 1; index >= 0; --index)
					temp.push_back(start[index]);
			
			if (std::regex_search(order, match, increment) && match.size() > 1)
			{
				int32_t inc = std::stoi(match[1]);
				temp.resize(count);

				for (int index = 0; index < start.size(); ++index)
					temp[(index * inc) % temp.size()] = start[index];
			}

			if (std::regex_search(order, match, cut) && match.size() > 1)
			{
				int64_t icut = std::stoi(match[1]);
				temp.resize(count);

				if (icut < 0)
					icut += count;

				for (int index = 0; index < start.size(); ++index)
					temp[(count - icut + index) % count] = start[index];
			}

			temp.swap(start);
		}

		return std::distance(start.begin(), std::find(start.begin(), start.end(), targetCard));
	}

public:
	Day22()
	{
		inputString = util::readFile("..\\inputs\\2019\\input_22.txt");
		inputVector = util::readFileLines("..\\inputs\\2019\\input_22.txt");
	}

	int64_t run()
	{
		util::Timer myTime;
		myTime.start();
						
		int64_t result1 = calcFirstDeck(10007, inputVector, 2019);
		int64_t result2 = calcSecondDeck(119315717514047, 101741582076661, inputVector, 2020);

		std::cout << "Day 22 - Part 1: " << result1 << std::endl;
		std::cout << "Day 22 - Part 2: " << result2 << std::endl;

		return myTime.usPassed();
	}
};

#endif  // ADVENTOFCODE2019_DAY22