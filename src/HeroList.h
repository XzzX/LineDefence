#pragma once

#include "Hero.h"

#include <string>
#include <unordered_map>

using HeroList = std::unordered_map<std::string, Hero>;

HeroList create_herolist(const std::string& heros_filename);