#include "evolve.h"

#include "tournament/tournament.h"

#include <chrono>
#include <iostream>
#include <random>

void mutate(const HeroList& herolist,
            Army& army)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> random_mutation(0, 1);

    switch (random_mutation(generator))
    {
        case 0:
            army = create_random_army(herolist, army.size());
            break;
        case 1:
            std::uniform_int_distribution<int> random_hero(0, herolist.size()-1);
            std::uniform_int_distribution<int> random_army_slot(0, army.size()-1);

            auto idx = random_army_slot(generator);
            army[idx] = std::next(herolist.begin(), random_hero(generator))->second;
            break;
    }
}

void evolve(const HeroList& herolist,
            int64_t population_size,
            int64_t growth_factor,
            int64_t num_rounds,
            int64_t num_evolutions)
{
    //create initial list of teams
    auto teams = create_random_teams(herolist, population_size * growth_factor);
    tournament(teams, num_rounds);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    for (int64_t i = 0; i < num_evolutions; ++i)
    {
        //selection phase
        teams.erase(teams.begin() + population_size, teams.end());

        for (int64_t team_id = 0; team_id < population_size; ++team_id)
        {
            for (int64_t new_gen_id = 1; new_gen_id < growth_factor; ++new_gen_id)
            {
                auto new_team = std::make_unique<Team>(*teams[0]);
                mutate(herolist, new_team->army);
                teams.push_back(std::move(new_team));
            }
        }

        std::shuffle(teams.begin(), teams.end(), generator);

        tournament(teams, num_rounds);
    }
}
