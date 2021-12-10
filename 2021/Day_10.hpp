#ifndef ADVENTOFCODE2021_DAY10
#define ADVENTOFCODE2021_DAY10

#include "../includes/aoc.h"
#include <stack>

class Day10 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    int64_t part1()
    {
        int sum_error = 0;

        for (auto ln : inputVec)
        {
            std::stack<char> q;
            for (auto ch : ln)
            {
                if (ch == '{' || ch == '(' || ch == '[' || ch == '<')
                    q.push(ch);
                else
                {
                    if (ch == '}')
                    {
                        if (q.top() != '{')
                        {
                            sum_error += 1197;
                            break;
                        }
                    }

                    if (ch == ')')
                    {
                        if (q.top() != '(')
                        {
                            sum_error += 3;
                            break;
                        }
                    }

                    if (ch == '>')
                    {
                        if (q.top() != '<')
                        {
                            sum_error += 25137;
                            break;
                        }
                    }

                    if (ch == ']')
                    {
                        if (q.top() != '[')
                        {
                            sum_error += 57;
                            break;
                        }
                    }
                    q.pop();
                }
            }
        }

        return sum_error;
    }

    int64_t part2()
    {
        std::vector<int64_t> scores;

        for (auto ln : inputVec)
        {
            std::stack<char> q;
            bool invalid = false;

            for (auto ch : ln)
            {
                if (ch == '{' || ch == '(' || ch == '[' || ch == '<')
                    q.push(ch);
                else
                {
                    if (ch == '}')
                    {
                        if (q.top() != '{')
                        {
                            invalid = true;
                            break;
                        }
                    }

                    if (ch == ')')
                    {
                        if (q.top() != '(')
                        {
                            invalid = true;
                            break;
                        }
                    }

                    if (ch == '>')
                    {
                        if (q.top() != '<')
                        {
                            invalid = true;
                            break;
                        }
                    }

                    if (ch == ']')
                    {
                        if (q.top() != '[')
                        {
                            invalid = true;
                            break;
                        }
                    }

                    q.pop();
                }
            }

            int64_t sum = 0;
            if (!invalid)
            {
                while (!q.empty())
                {
                    sum *= 5;
                    if (q.top() == '(')
                        sum += 1;
                    if (q.top() == '[')
                        sum += 2;
                    if (q.top() == '{')
                        sum += 3;
                    if (q.top() == '<')
                        sum += 4;

                    q.pop();
                }

                scores.push_back(sum);
            }
        }

        std::sort(scores.begin(), scores.end());

        return scores[scores.size() / 2];
    }

public:
    Day10()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_10.txt");
        inputVec = util::readFileLines("..\\inputs\\2021\\input_10.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();
        
        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
