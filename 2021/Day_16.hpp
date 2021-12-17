#ifndef ADVENTOFCODE2021_DAY16
#define ADVENTOFCODE2021_DAY16

#include "../includes/aoc.h"

class Day16 {
private:
    std::string inputString;
    std::map<int8_t, std::string> hex;

    std::pair<int32_t, int64_t> readPackets(std::string binary, int& versionSum)
    {
        if (binary.size() < 6)
            return std::make_pair(0, 0);

        // Get Packet Version
        std::string version = binary.substr(0, 3);
        int iVersion = std::stoi(version, nullptr, 2);
        versionSum += iVersion;

        std::string sType = binary.substr(3, 3);
        int type = std::stoi(sType, nullptr, 2);

        if (type == 4)
        {
            auto sGroup = binary.substr(6, 5);
            int counter = 0;

            auto sValue = binary.substr(7, 4);

            while (sGroup[0] != '0')
            {
                counter++;
                sGroup = binary.substr(6 + counter * 5, 5);
                sValue += binary.substr(7 + counter * 5, 4);
            }

            int64_t value = std::stoll(sValue, nullptr, 2);

            return std::make_pair(11 + counter * 5, value);
        }
        else
        {
            auto sLength = binary.substr(6, 1);

            int32_t length_used = 0;
            int64_t value = 0;
            std::vector<int64_t> values;

            if (sLength == "0")
            {
                auto sLengthPackets = binary.substr(7, 15);
                length_used = std::stoi(sLengthPackets, nullptr, 2);

                int returned_length = 0;

                while (returned_length < length_used)
                {
                    auto res = readPackets(binary.substr(22 + returned_length, length_used - returned_length), versionSum);
                    returned_length += res.first;
                    values.push_back(res.second);
                }

                length_used += 22;            
            }

            if (sLength == "1")
            {
                auto sNumPackets = binary.substr(7, 11);
                int num_packets = std::stoi(sNumPackets, nullptr, 2);
                for (int packet = 0; packet < num_packets; ++packet)
                {
                    auto res = readPackets(binary.substr(18 + length_used), versionSum);
                    length_used += res.first;
                    values.push_back(res.second);
                }

                length_used += 18;
            }

            if (type == 0)
                for (auto val : values)
                    value += val;

            if (type == 1)
            {
                value = 1;
                for (auto val : values)
                    value *= val;
            }
            
            if (type == 2)
                value = *std::min_element(values.begin(), values.end());
            
            if (type == 3)
                value = *std::max_element(values.begin(), values.end());
            
            if (type == 5)
                value = (values[0] > values[1]);
            
            if (type == 6)
                value = (values[0] < values[1]);

            if (type == 7)
                value = (values[0] == values[1]);

            return std::make_pair(length_used, value);
        }
    }

    std::pair<int64_t, int64_t> solve()
    {
        hex['0'] = "0000";
        hex['1'] = "0001";
        hex['2'] = "0010";
        hex['3'] = "0011";
        hex['4'] = "0100";
        hex['5'] = "0101";
        hex['6'] = "0110";
        hex['7'] = "0111";
        hex['8'] = "1000";
        hex['9'] = "1001";
        hex['A'] = "1010";
        hex['B'] = "1011";
        hex['C'] = "1100";
        hex['D'] = "1101";
        hex['E'] = "1110";
        hex['F'] = "1111";

        std::string binary = "";

        for (auto ch : inputString)
            binary += hex[ch];

        int versionSum = 0;
        auto value = readPackets(binary, versionSum);
        return std::make_pair(versionSum, value.second);
    }

    int64_t part2()
    {
        return 0;
    }

public:
    Day16()
    {
        inputString = util::readFile("..\\inputs\\2021\\input_16.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto res = solve();
        auto result_1 = res.first;
        auto result_2 = res.second;

        int64_t time = myTime.usPassed();
        std::cout
            << "Day 16 - Part 1: " << result_1 << '\n'
            << "Day 16 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2021_DAY10
