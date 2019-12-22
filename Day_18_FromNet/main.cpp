#include <fstream>
#include <iostream>
#include <chrono>

#include "solve.h"

#define TIMING_START auto __timing_start = std::chrono::high_resolution_clock::now();
#define TIMING_FINISH \
    auto __timing_finish = std::chrono::high_resolution_clock::now(); \
    std::chrono::duration<double> __timing_elapsed = __timing_finish - __timing_start; \
    std::cout << "Elapsed time: " << __timing_elapsed.count() << " s\n";

int main() {
    std::ifstream input;
    input.open(std::string("../inputs/input_2019_18.txt").c_str());
	TIMING_START
    std::cout << Day18::solve1(input) << std::endl;
	TIMING_FINISH
	getchar();
    return 0;
}
