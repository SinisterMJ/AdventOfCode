#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdint.h>
#include <regex>
#include <map>
#include <thread>
#include <numeric>

#include "../includes/aoc.h"
#include "../includes/Map2DBase.h"
#include "../includes/IntcodeVM.h"
#include <inttypes.h>

std::vector<int> fftPattern = { 0, 1, 0, -1 };

int getLastDigit(int input)
{
    return std::abs(input) % 10;
}

int fft(std::vector<int>& signal, int fftLength)
{
    int index = 0;
    int result = 0;
        
    while (index < signal.size())
    {
        int indexFFT = ((index + 1) / fftLength) % 4;

        if (fftPattern[indexFFT] == 1)
            result += signal[index];
        if (fftPattern[indexFFT] == -1)
            result -= signal[index];
        
        index++;
    }

    return getLastDigit(result);
}

int getResult1(std::vector<int32_t> inputSignal)
{
    std::vector<int> temporary;
    temporary.resize(inputSignal.size());

    int result = 0;

    for (int run = 0; run < 100; ++run)
    {
        for (int index = 1; index <= inputSignal.size(); ++index)
        {
            temporary[index - 1] = fft(inputSignal, index);
        }
        std::swap(temporary, inputSignal);
    }

    for (int index = 0; index < 8; ++index)
    {
        result = result * 10 + inputSignal[index];
    }

    return result;
}

int getResult2(std::vector<int32_t> inputSignal)
{
    std::vector<int> repeatedSignal;
    int result = 0;

    int neededDigits = 10000 * static_cast<int32_t>(inputSignal.size());
    int offset = 0;

    for (int index = 0; index < 7; ++index)
        offset = offset * 10 + inputSignal[index];

    for (int i = 0; i < 10000; ++i)
        repeatedSignal.insert(repeatedSignal.end(), inputSignal.begin(), inputSignal.end());
        
    for (int run = 0; run < 100; ++run)
    {
        int val = repeatedSignal.back();
        for (int index = repeatedSignal.size() - 2; index >= offset; --index)
        {
            val += repeatedSignal[index];
            val = val % 10;
            repeatedSignal[index] = val;
        }
    }

    for (int index = offset; index < offset + 8; ++index)
        result = 10 * result + repeatedSignal[index];
    
    return result;
}

int main()
{
	util::Timer myTime;
	myTime.start();

	auto input = util::readFile("..\\inputs\\input_2019_16.txt");

    std::vector<int32_t> inputSignal;

    for (int index = 0; index < input.length(); ++index)
    {
        std::string digit = input.substr(index, 1);
        if (digit == "\n")
            break;
        inputSignal.push_back(std::stoi(digit));
    }
    
	int64_t result1 = getResult1(inputSignal);
	int64_t result2 = getResult2(inputSignal);

	std::cout << "Part 1: " << result1 << std::endl;
	std::cout << "Part 2: " << result2 << std::endl;
	std::cout << "Time taken: " << myTime.usPassed() << " [us]" << std::endl;
	getchar();
	return 0;
}