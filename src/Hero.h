#pragma once

#include "yaml-cpp/yaml.h"

#include <string>

struct Hero
{
    Hero(const YAML::Node& yaml)
    {
        if (yaml["id"]) id = yaml["id"].as<std::string>();
        if (yaml["cost"]) cost = yaml["cost"].as<int64_t>();
        if (yaml["hp"]) hp = yaml["hp"].as<int64_t>();
        if (yaml["damage"]) damage = yaml["damage"].as<int64_t>();
        if (yaml["armor"]) armor = yaml["armor"].as<int64_t>();
    }

    std::string id = "ERROR";
    int64_t cost = std::numeric_limits<int64_t>::max();
    int64_t hp = 0;
    int64_t damage = 0;
    int64_t armor = 0;
};

inline
bool operator==(const Hero& lhs, const Hero& rhs)
{
    if (lhs.id != rhs.id) return false;
    if (lhs.cost != rhs.cost) return false;
    if (lhs.hp != rhs.hp) return false;
    if (lhs.damage != rhs.damage) return false;
    if (lhs.armor != rhs.armor) return false;
    return true;
}