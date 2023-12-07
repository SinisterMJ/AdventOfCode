#ifndef ADVENTOFCODE2023_DAY07
#define ADVENTOFCODE2023_DAY07

#include "../includes/aoc.h"
#include <algorithm>

class Day07 {
private:

    std::vector<std::string> inputVector;
    std::string inputString;
    
    struct CamelCards {
        std::string cards;
        int bid;

        std::map<int8_t, int8_t> cardStrength;

        CamelCards() {
            bid = 0;
            cards = "";
            cardStrength['2'] = 0;
            cardStrength['3'] = 1;
            cardStrength['4'] = 2;
            cardStrength['5'] = 3;
            cardStrength['6'] = 4;
            cardStrength['7'] = 5;
            cardStrength['8'] = 6;
            cardStrength['9'] = 7;
            cardStrength['T'] = 8;
            cardStrength['J'] = 9;
            cardStrength['Q'] = 10;
            cardStrength['K'] = 11;
            cardStrength['A'] = 12;
        }

        int rankLevel(std::map<int8_t, int8_t>& dict)
        {
            for (auto [ch, occ] : dict)
            {
                if (occ == 5)
                    return 7;
                if (occ == 4)
                    return 6;

                if (occ == 3)
                {
                    for (auto [ch_i, occ_i] : dict)
                    {
                        if (occ_i == 2)
                            return 5;
                    }
                    return 4;
                }

                if (occ == 2)
                {
                    for (auto [ch_i, occ_i] : dict)
                    {
                        if (ch_i != ch && occ_i == 2)
                            return 3;
                        if (occ_i == 3)
                            return 5;
                    }

                    return 2;
                }
            }

            return 1;
        }

        bool bigger(CamelCards comp)
        {
            std::map<int8_t, int8_t> occurences;
            std::map<int8_t, int8_t> occurences_comp;

            for (auto ch : cards)
                occurences[ch] += 1;

            for (auto ch : comp.cards)
                occurences_comp[ch] += 1;

            auto rank = rankLevel(occurences);
            auto rank_comp = rankLevel(occurences_comp);

            if (rank == rank_comp)
            {
                for (int index = 0; index < cards.size(); ++index)
                {
                    if (cards[index] != comp.cards[index])
                    {
                        return cardStrength[cards[index]] > cardStrength[comp.cards[index]];
                    }
                }

                return false;
            }

            return rank > rank_comp;
        }

        bool bigger_part2(CamelCards comp)
        {
            std::map<int8_t, int8_t> occurences;
            std::map<int8_t, int8_t> occurences_comp;
            cardStrength['J'] = -1;

            for (auto ch : cards)
                occurences[ch] += 1;

            for (auto ch : comp.cards)
                occurences_comp[ch] += 1;

            int8_t max = 0;
            for (auto [ch, occ] : occurences)
            {
                if (ch == 'J')
                    continue;
                max = std::max(occ, max);
            }

            for (auto [ch, occ] : occurences)
            {
                if (ch == 'J')
                    continue;
                if (occ == max)
                {
                    occurences[ch] += occurences['J'];
                    occurences['J'] = 0;
                    break;
                }
            }

            max = 0;
            for (auto [ch, occ] : occurences_comp)
            {
                if (ch == 'J')
                    continue;
                max = std::max(occ, max);
            }

            for (auto [ch, occ] : occurences_comp)
            {
                if (ch == 'J')
                    continue;
                if (occ == max)
                {
                    occurences_comp[ch] += occurences_comp['J'];
                    occurences_comp['J'] = 0;
                    break;
                }
            }

            auto rank = rankLevel(occurences);
            auto rank_comp = rankLevel(occurences_comp);

            if (rank == rank_comp)
            {
                for (int index = 0; index < cards.size(); ++index)
                {
                    if (cards[index] != comp.cards[index])
                    {
                        return cardStrength[cards[index]] > cardStrength[comp.cards[index]];
                    }
                }

                return false;
            }

            return rank > rank_comp;
        }
    };

    std::vector<CamelCards> allCards;

    int64_t part1()
    {
        for (auto line : inputVector)
        {
            auto card = util::split(line, ' ');
            CamelCards temp;
            temp.cards = card[0];
            temp.bid = std::stoi(card[1]);
            allCards.push_back(temp);
        }

        bool shuffled = true;
        while (shuffled)
        {
            shuffled = false;
            for (int index = 0; index < allCards.size() - 1; ++index)
            {
                if (allCards[index].bigger(allCards[index + 1]))
                {
                    std::swap(allCards[index], allCards[index + 1]);
                    shuffled = true;
                }
            }
        }

        int64_t result = 0;
        for (int index = 0; index < allCards.size(); ++index)
        {
            result += (index + 1) * allCards[index].bid;
        }

        return result;
    }

    int64_t part2()
    {
        bool shuffled = true;
        while (shuffled)
        {
            shuffled = false;
            for (int index = 0; index < allCards.size() - 1; ++index)
            {
                if (allCards[index].bigger_part2(allCards[index + 1]))
                {
                    std::swap(allCards[index], allCards[index + 1]);
                    shuffled = true;
                }
            }
        }

        int64_t result = 0;
        for (int index = 0; index < allCards.size(); ++index)
        {
            result += (index + 1) * allCards[index].bid;
        }

        return result;
    }

public:
    Day07()
    {
        inputVector = util::readFileLines("..\\inputs\\2023\\input_7.txt");
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        auto result_1 = part1();
        auto result_2 = part2();

        int64_t time = myTime.usPassed();

        std::cout << "Day 07 - Part 1: " << result_1 << '\n'
                  << "Day 07 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2023_DAY07