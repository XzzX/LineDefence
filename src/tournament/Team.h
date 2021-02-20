#pragma once

#include "common/Army.h"

struct Team
{
    int64_t id;
    bool seated;
    Army army;
    std::vector<size_t> previous_opponents;
    int64_t points;
};