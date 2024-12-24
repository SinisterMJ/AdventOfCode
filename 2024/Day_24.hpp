#ifndef ADVENTOFCODE2024_DAY24
#define ADVENTOFCODE2024_DAY24

#include "../includes/aoc.h"
#include <algorithm>
#include <bitset>

class Day24 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;

    struct gate {
        std::string input_1;
        std::string input_2;
        std::string logic;
        std::string output;
    };

    std::vector<gate> all_gates;
    std::map<std::string, bool> values_orig;

    int64_t get_output() 
    {
        auto values = values_orig;
        bool found_new = true;
        while (found_new)
        {
            found_new = false;

            for (auto& g : all_gates)
            {
                if (values.count(g.output) > 0)
                    continue;

                if (values.count(g.input_1) == 0 || values.count(g.input_2) == 0)
                    continue;

                found_new = true;

                if (g.logic == "AND")
                    values[g.output] = values[g.input_1] && values[g.input_2];
                if (g.logic == "OR")
                    values[g.output] = values[g.input_1] || values[g.input_2];
                if (g.logic == "XOR")
                    values[g.output] = values[g.input_1] ^ values[g.input_2];
            }
        }

        int index = 0;
        std::bitset<64> ringList(0);

        while (true)
        {
            std::string gate_name = "z";
            if (index < 10)
                gate_name += "0";
            gate_name += std::to_string(index);

            if (values.count(gate_name) == 0)
                break;

            ringList[index] = values[gate_name];
            index++;
        }

        return ringList.to_ullong();
    }

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            if (line.find(": ") != std::string::npos)
            {
                auto parts = util::split(line, ": ");
                values_orig[parts[0]] = (parts[1] == "1");
            }

            if (line.find(" -> ") != std::string::npos)
            {
                auto splits = util::split(line, " ");
                gate temp;
                temp.input_1 = splits[0];
                temp.logic = splits[1];
                temp.input_2 = splits[2];
                temp.output = splits[4];
                all_gates.push_back(temp);
            }
        }

        return get_output();
    }

    std::string part2()
    {
        int index = 0;
        std::bitset<64> x_val(0);
        std::bitset<64> y_val(0);

        int rule_1 = 67;
        int rule_2 = 138;
        int rule_3 = 208;
        int rule_4 = 213;

        while (true)
        {
            std::string gate_name = "x";
            if (index < 10)
                gate_name += "0";
            gate_name += std::to_string(index);

            if (values_orig.count(gate_name) == 0)
                break;

            x_val[index] = values_orig[gate_name];
            gate_name[0] = 'y';
            y_val[index] = values_orig[gate_name];
            index++;
        }

        int64_t target = x_val.to_ullong() + y_val.to_ullong();
        std::bitset<64> z_target(target);

        std::vector<std::pair<int32_t, int32_t>> candidates;

        auto temp_val = get_output();

        std::bitset<64> t(temp_val);
        auto def_same = (t ^ z_target).count();

        for (int a = 0; a < all_gates.size(); ++a)
        {
            for (int b = a + 1; b < all_gates.size(); ++b)
            {
                bool a_rule = (a == rule_1 || a == rule_2 || a == rule_3 || a == rule_4);
                bool b_rule = (b == rule_1 || b == rule_2 || b == rule_3 || b == rule_4);
                if (!a_rule && !b_rule)
                    continue;

                std::swap(all_gates[a].output, all_gates[b].output);
                auto result = get_output();
                std::bitset<64> z_out(result);

                auto same = (z_out ^ z_target).count();
                if (same < def_same)
                    candidates.push_back(std::make_pair(a, b));

                std::swap(all_gates[a].output, all_gates[b].output);
            }
        }

        for (int i = 0; i < candidates.size(); ++i)
        {
            for (int j = i + 1; j < candidates.size(); ++j)
            {
                if (candidates[i].first == candidates[j].first)
                    continue;
                for (int h = j + 1; h < candidates.size(); ++h)
                {
                    if (candidates[j].first == candidates[h].first)
                        continue;
                    for (int k = h + 1; k < candidates.size(); ++k)
                    {
                        if (candidates[h].first == candidates[k].first)
                            continue;
                        std::set<int32_t> vals;
                        vals.insert(candidates[i].first);
                        vals.insert(candidates[i].second);
                        vals.insert(candidates[j].first);
                        vals.insert(candidates[j].second);
                        vals.insert(candidates[h].first);
                        vals.insert(candidates[h].second);
                        vals.insert(candidates[k].first);
                        vals.insert(candidates[k].second);

                        if (vals.size() != 8)
                            continue;

                        std::swap(all_gates[candidates[i].first].output, all_gates[candidates[i].second].output);
                        std::swap(all_gates[candidates[j].first].output, all_gates[candidates[j].second].output);
                        std::swap(all_gates[candidates[h].first].output, all_gates[candidates[h].second].output);
                        std::swap(all_gates[candidates[k].first].output, all_gates[candidates[k].second].output);

                        auto result = get_output();

                        if (result == target)
                        {
                            std::vector<std::string> wrong_gates;
                            wrong_gates.push_back(all_gates[candidates[i].first].output);
                            wrong_gates.push_back(all_gates[candidates[i].second].output);
                            wrong_gates.push_back(all_gates[candidates[j].first].output);
                            wrong_gates.push_back(all_gates[candidates[j].second].output);
                            wrong_gates.push_back(all_gates[candidates[h].first].output);
                            wrong_gates.push_back(all_gates[candidates[h].second].output);
                            wrong_gates.push_back(all_gates[candidates[k].first].output);
                            wrong_gates.push_back(all_gates[candidates[k].second].output);

                            std::sort(wrong_gates.begin(), wrong_gates.end());
                            
                            std::string result = "";
                            for (auto& n : wrong_gates)
                            {
                                result += n + ",";
                            }
                            return result;
                        }

                        std::swap(all_gates[candidates[i].first].output, all_gates[candidates[i].second].output);
                        std::swap(all_gates[candidates[j].first].output, all_gates[candidates[j].second].output);
                        std::swap(all_gates[candidates[h].first].output, all_gates[candidates[h].second].output);
                        std::swap(all_gates[candidates[k].first].output, all_gates[candidates[k].second].output);
                    }
                }
            }
        }

        return "";

        /*for (int a = 0; a < all_gates.size(); ++a)
        {
            for (int b = a + 1; b < all_gates.size(); ++b)
            {
                std::swap(all_gates[a].output, all_gates[b].output);
                for (int c = a + 1; c < all_gates.size(); ++c)
                {
                    for (int d = c + 1; d < all_gates.size(); ++d)
                    {
                        std::swap(all_gates[c].output, all_gates[d].output);
                        for (int e = c + 1; e < all_gates.size(); ++e)
                        {
                            for (int f = e + 1; f < all_gates.size(); ++f)
                            {
                                std::set<int> check;
                                check.insert(a);
                                check.insert(b);
                                check.insert(c);
                                check.insert(d);
                                check.insert(e);
                                check.insert(f);
                                if (check.size() != 6)
                                    continue;

                                std::swap(all_gates[e].output, all_gates[f].output);
                                for (int g = e + 1; g < all_gates.size(); ++g)
                                {
                                    for (int h = g + 1; h < all_gates.size(); ++h)
                                    {
                                        std::swap(all_gates[g].output, all_gates[h].output);
                                        auto result = get_output();

                                        if (result == target)
                                        {
                                            std::vector<std::string> wrong_gates;
                                            wrong_gates.push_back(all_gates[a].output);
                                            wrong_gates.push_back(all_gates[b].output);
                                            wrong_gates.push_back(all_gates[c].output);
                                            wrong_gates.push_back(all_gates[d].output);
                                            wrong_gates.push_back(all_gates[e].output);
                                            wrong_gates.push_back(all_gates[f].output);
                                            wrong_gates.push_back(all_gates[g].output);
                                            wrong_gates.push_back(all_gates[h].output);
                                            std::sort(wrong_gates.begin(), wrong_gates.end());
                                            std::string result = "";
                                            for (auto& n : wrong_gates)
                                            {
                                                result += n + ",";
                                            }
                                            return result;
                                        }

                                        std::swap(all_gates[g].output, all_gates[h].output);
                                    }
                                }
                                std::swap(all_gates[e].output, all_gates[f].output);
                            }
                        }
                        std::swap(all_gates[c].output, all_gates[d].output);
                    }
                }
                std::swap(all_gates[a].output, all_gates[b].output);
            }
        }*/

        return "";
    }

public:
    Day24()
    {
        inputVector = util::readFileLines("..\\inputs\\2024\\input_24.txt");
        inputString = util::readFile("..\\inputs\\2024\\input_24.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 24 - Part 1: " << result_1 << '\n'
                  << "Day 24 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2024_DAY24