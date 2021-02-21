#pragma once

#include "common/HeroList.h"

void evolve(const HeroList& herolist,
            int64_t population_size,
            int64_t growth_factor,
            int64_t num_rounds,
            int64_t num_evolutions);