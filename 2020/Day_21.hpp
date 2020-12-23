#ifndef ADVENTOFCODE2020_DAY21
#define ADVENTOFCODE2020_DAY21

#include "../includes/aoc.h"

class Day21 {
private:
    struct FoodItem {
        std::vector<std::string> ingredients;
        std::vector<std::string> allergens;
    };

    std::string inputString;
    std::vector<std::string> inputVec;
    std::vector<FoodItem> complete_list;

    std::map<std::string, std::string> ingredientToAllergen;
    std::map<std::string, std::string> allergenToIngredient;

    std::set<std::string> allergens;
    std::set<std::string> ingredients;

    void ReadFood()
    {
        for (auto& elem : inputVec)
        {
            FoodItem temp;
            auto pos_split = elem.find(" (contain");
            std::string ingred = "";
            std::string allerg = "";
            if (pos_split != std::string::npos)
            {
                ingred = elem.substr(0, pos_split);
                temp.ingredients = util::split(ingred, ' ');
                allerg = elem.substr(pos_split + 11);

                std::sort(temp.ingredients.begin(), temp.ingredients.end());
                for (auto& item : temp.ingredients)
                {
                    ingredients.insert(item);
                }
            }

            if (allerg != "")
            {
                temp.allergens = util::split(allerg, ',');

                for (auto& item : temp.allergens)
                {
                    if (item.find(" ") != std::string::npos)
                    {
                        item = item.substr(1);
                    }

                    if (item.find(")") != std::string::npos)
                    {
                        item = item.substr(0, item.find(")"));
                    }
                }

                for (auto& item : temp.allergens)
                {
                    allergens.insert(item);
                }
            }

            complete_list.push_back(temp);
        }

        std::map<std::string, std::set<std::string>> allergen_candidates;

        for (auto& allerg : allergens)
        {
            std::set<std::string> candidates(ingredients);
            std::set<std::string> remaining_candidates;

            for (auto& item : complete_list)
            {
                if (std::find(item.allergens.begin(), item.allergens.end(), allerg) != item.allergens.end())
                {
                    std::set_intersection(candidates.begin(), candidates.end(), item.ingredients.begin(), item.ingredients.end(), std::inserter(remaining_candidates, remaining_candidates.begin()));
                    std::swap(remaining_candidates, candidates);
                    remaining_candidates.clear();
                }
            }

            allergen_candidates[allerg] = candidates;
        }
        
        while (allergen_candidates.size() > 0)
        {
            for (auto& candidate : allergen_candidates)
            {
                if (candidate.second.size() == 1)
                {
                    std::string ingredient = *candidate.second.begin();
                    allergenToIngredient[candidate.first] = ingredient;
                    ingredientToAllergen[ingredient] = candidate.first;

                    for (auto& elem : allergen_candidates)
                    {
                        if (elem.second.find(ingredient) != elem.second.end())
                        {
                            elem.second.erase(ingredient);
                        }
                    }

                    allergen_candidates.erase(candidate.first);
                    break;
                }
            }
        }
    }

    int64_t part1()
    {
        int64_t result = 0;

        for (auto& item : complete_list)
        {
            for (auto& ingredient : item.ingredients)
                result += (ingredientToAllergen.find(ingredient) == ingredientToAllergen.end());
        }

        return result;
    }

    std::string part2()
    {
        std::string result = "";
        for (auto& item : allergenToIngredient)
            result += "," + item.second;

        return result.substr(1);
    }
public:
    Day21()
    {
        inputString = util::readFile("..\\inputs\\2020\\input_21.txt");
        inputVec = util::readFileLines("..\\inputs\\2020\\input_21.txt", '\n', true);
    }

    int64_t run()
    {
        util::Timer myTime;
        myTime.start();

        ReadFood();

        int64_t result_1 = part1();
        std::string result_2 = part2();

        int64_t time = myTime.usPassed();
        std::cout << "Day 21 - Part 1: " << result_1 << '\n'
                  << "Day 21 - Part 2: " << result_2 << '\n';

        return time;
    }
};

#endif  // ADVENTOFCODE2020_DAY21
