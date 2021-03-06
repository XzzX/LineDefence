#include "fight.h"

#include "common/Army.h"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <numeric>

void print_state(const Army& army1,
                 const Army& army2)
{
    auto& hero1 = army1.back();
    auto& hero2 = army2.back();
    auto value1 = std::accumulate(army1.begin(), army1.end(), 0, [](auto val, auto& hero){return val + hero.costs;});
    auto value2 = std::accumulate(army2.begin(), army2.end(), 0, [](auto val, auto& hero){return val + hero.costs;});
    std::cout << "==========================" << std::endl;
    std::cout << "| value   | " << std::setw(3) << value1       << "      " << std::setw(3) << value2       << " |" << std::endl;
    std::cout << "| size    | " << std::setw(3) << army1.size() << "      " << std::setw(3) << army2.size() << " |" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "| hp      | " << std::setw(3) << hero1.hp     << "      " << std::setw(3) << hero2.hp     << " |" << std::endl;
    std::cout << "| damage  | " << std::setw(3) << hero1.damage << "  vs  " << std::setw(3) << hero2.damage << " |" << std::endl;
    std::cout << "| armor   | " << std::setw(3) << hero1.armor  << "      " << std::setw(3) << hero2.armor  << " |" << std::endl;
    std::cout << "==========================" << std::endl;
}

int fight(Army army1,
          Army army2,
          bool print_rounds)
{
    while (!army1.empty() && !army2.empty())
    {
        auto& hero1 = army1.back();
        auto& hero2 = army2.back();
        auto damage1 = std::max(hero2.damage - hero1.armor, 1l);
        auto damage2 = std::max(hero1.damage - hero2.armor, 1l);
        assert(damage1 > 0 && "0 damage can lead to an infinite fight");
        assert(damage2 > 0 && "0 damage can lead to an infinite fight");
        if (print_rounds) print_state(army1, army2);
        hero1.hp -= damage1;
        hero2.hp -= damage2;
        if (hero1.hp < 0) army1.pop_back();
        if (hero2.hp < 0) army2.pop_back();
    }
    return army1.size() - army2.size();
}