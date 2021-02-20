#include "Army.h"

#include <chrono>
#include <random>

Army create_army(const HeroList& herolist,
                 const std::string& army_filename)
{
    Army army;
    auto army_yaml = YAML::LoadFile(army_filename);
    for (auto it = army_yaml.begin(); it != army_yaml.end(); ++it)
    {
        army.push_back(herolist.find(it->as<std::string>())->second);
    }
    return army;
}

Army create_random_army(const HeroList& herolist,
                        const int hero_count)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, herolist.size()-1);

    Army army;
    for (int i = 0; i < hero_count; ++i)
    {
        army.push_back(std::next(herolist.begin(), distribution(generator))->second);
    }
    return army;
}