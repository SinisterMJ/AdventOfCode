#ifndef ADVENTOFCODE2021_DAY10
#define ADVENTOFCODE2021_DAY10

#include "../includes/aoc.h"
#include <stack>

class Day10 {
private:
    std::string inputString;
    std::vector<std::string> inputVec;

    std::pair<int64_t, int64_t> solve()
    {
        int sum_error = 0;
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
                            sum_error += 1197;
                            invalid = true;
                            break;
                        }
                    }

                    if (ch == ')')
                    {
                        if (q.top() != '(')
                        {
                            sum_error += 3;
                            invalid = true;
                            break;
                        }
                    }

                    if (ch == '>')
                    {
                        if (q.top() != '<')
                        {
                            sum_error += 25137;
                            invalid = true;
                            break;
                        }
                    }

                    if (ch == ']')
                    {
                        if (q.top() != '[')
                        {
                            sum_error += 57;
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

        return std::make_pair(sum_error, scores[scores.size() / 2]);
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
        
        auto res = solve();
        auto result_1 = res.first;
        auto result_2 = res.second;

        int64_t time = myTime.usPassed();
        std::cout << "Day 10 - Part 1: " << result_1 << '\n'
                  << "Day 10 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
