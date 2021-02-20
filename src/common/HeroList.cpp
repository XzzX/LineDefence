#include "HeroList.h"

HeroList create_herolist(const std::string& heros_filename)
{
    HeroList herolist;
    auto heros_yaml = YAML::LoadFile(heros_filename);
    for (auto it = heros_yaml.begin(); it != heros_yaml.end(); ++it)
    {
        herolist.insert(std::make_pair((*it)["id"].as<std::string>(), create_hero(*it)));
    }
    return herolist;
}
