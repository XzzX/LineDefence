#pragma once

#include "tournament/Team.h"

#include <cstdint>
#include <string>
#include <vector>

std::vector<std::unique_ptr<Team>> create_random_teams(const HeroList& herolist,
                                                       const int64_t num_teams);

void tournament(std::vector<std::unique_ptr<Team>>& teams,
                const int64_t num_rounds);