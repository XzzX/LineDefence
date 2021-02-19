#pragma once

#include "HeroList.h"

#include <vector>

using Army = std::vector<Hero>;
Army create_army(const HeroList& herolist,
                 const std::string& army_filename);

Army create_random_army(const HeroList& herolist,
                        const int hero_count);