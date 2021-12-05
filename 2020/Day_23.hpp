#ifndef ADVENTOFCODE2020_DAY23
#define ADVENTOFCODE2020_DAY23

#include "../includes/aoc.h"
#include <algorithm>

class Day23 {
private:
    struct Node {
        int64_t val;
        Node* previous;
        Node* next;
    };

    std::string inputString;
    std::vector<std::string> inputVec;

    std::vector<int32_t> cups_start;

    int64_t runGame(int num_cups, int rounds_total, bool part1) 
    {
        std::vector<Node*> cups_dll(num_cups + 1);
    
        Node* front = nullptr;
        for (int index = 0; index < num_cups; index++)
        {
            Node* temp = new Node();
            temp->val = index + 1;
            if (index < cups_start.size())
            {
                temp->val = cups_start[index];
            }

            if (front != nullptr)
            {
                Node* previous = front->previous;
                previous->next = temp;
                temp->previous = previous;
                temp->next = front;
                front->previous = temp;
            }

            if (front == nullptr)
            {
                front = temp;
                front->next = front;
                front->previous = front;
            }

            cups_dll[temp->val] = temp;
        }

        int32_t min = 1;
        int32_t max = num_cups;

        Node* currentCup = cups_dll[cups_start[0]];
        
        for (int rounds = 0; rounds < rounds_total; ++rounds)
        {            
            Node* cup1 = currentCup->next;
            Node* cup2 = cup1->next;
            Node* cup3 = cup2->next;

            Node* cup4 = currentCup->next->next->next->next;

            int64_t targetCup = currentCup->val - 1;
            if (targetCup < min)
                targetCup = max;

            while (targetCup == cup1->val || targetCup == cup2->val || targetCup == cup3->val)
            {
                targetCup--;
                if (targetCup < min)
                    targetCup = max;
            }
            
            Node* destination = cups_dll[targetCup];
            
            currentCup->next = cup4;
            cup4->previous = currentCup;
            
            cup3->next = destination->next;
            destination->next->previous = cup3;

            cup1->previous = destination;
            destination->next = cup1;

            currentCup = currentCup->next;
        }

        int64_t result = cups_dll[1]->next->val * cups_dll[1]->next->next->val;

        if (part1)
        {
            result = 0;
            auto one = cups_dll[1];
            Node* current = one->next;
            for (int index = 1; index < num_cups; ++index)
            {
                result = result * 10 + current->val;
                current = current->next;
            }
        }
        
        for (int index = 0; index < num_cups; index++)
        {
            delete cups_dll[index];
        }
        return result;
    }

public:
    Day23()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_23.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_23.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        for (uint64_t index = 0; index < inputString.size(); ++index)
        {
            if (inputString[index] == '\n') break;

            cups_start.push_back(inputString[index] - '0');
        }

        auto result_1 = runGame(9, 100, true);
        auto result_2 = runGame(1'000'000, 10'000'000, false);

        int64_t time = myTime.usPassed();
        std::cout << "Day 23 - Part 1: " << result_1 << '\n'
                  << "Day 23 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY23
