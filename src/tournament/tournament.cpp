#include "tournament.h"

#include "common/Army.h"
#include "fight/fight.h"

#include <iostream>
#include <vector>
#include <iomanip>

std::vector<std::unique_ptr<Team>> create_random_teams(const HeroList& herolist,
                                                       const int64_t num_teams)
{
    std::vector<std::unique_ptr<Team>> teams;
    for (int64_t i = 0; i < num_teams; ++i)
        teams.emplace_back(new Team{i, false, create_random_army(herolist, 10), {}, 0l});
    return teams;
}

void print_top_x(const std::vector<std::unique_ptr<Team>>& teams,
                 const size_t num_teams)
{
    std::cout << "===================================================" << std::endl;
    std::cout << "pos |   id  | points | army" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    for (size_t pos = 0; pos < num_teams; ++pos)
    {
        std::cout << std::setw(3) << pos + 1 << " | "<< std::setw(5) << teams[pos]->id << " | " << std::setw(6) << teams[pos]->points << " | ";
        for (Hero& hero : teams[pos]->army)
        {
            std::cout << hero.id << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "===================================================" << std::endl;
}

void tournament(std::vector<std::unique_ptr<Team>>& teams,
                const int64_t num_rounds)
{
    constexpr int64_t points_win = 2l;
    constexpr int64_t points_remis = 1l;
    constexpr int64_t points_loss = 0l;

    const auto num_teams = teams.size();

    //resetting cache
    for (auto& team : teams)
    {
        team->points = 0;
        team->seated = false;
        team->previous_opponents.clear();
    }
    for (int64_t round = 0; round < num_rounds; ++round)
    {
//        std::cout << "Round " << round << std::endl;
        //finding pairings
        for (size_t team1 = 0; team1 < num_teams; ++team1)
        {
            if (teams[team1]->seated) continue;
            for (size_t team2 = team1 + 1; team2 < num_teams; ++team2)
            {
                if (teams[team2]->seated) continue;
                if (std::find(teams[team1]->previous_opponents.begin(),
                              teams[team1]->previous_opponents.end(),
                              team2) != teams[team1]->previous_opponents.end()) continue;
//                std::cout << teams[team1]->id << " vs " << teams[team2]->id << std::endl;
                teams[team1]->seated = true;
                teams[team2]->seated = true;
                teams[team1]->previous_opponents.emplace_back(team2);
                teams[team2]->previous_opponents.emplace_back(team1);

                auto res = fight(teams[team1]->army, teams[team2]->army);
                if (res > 0)
                {
                    teams[team1]->points += points_win;
                    teams[team2]->points += points_loss;
                } else if (res == 0)
                {
                    teams[team1]->points += points_remis;
                    teams[team2]->points += points_remis;
                } else
                {
                    teams[team1]->points += points_loss;
                    teams[team2]->points += points_win;
                }
                break;
            }
        }

        //checking every team was seated
//        std::cout << "not seated: " << std::count_if(teams.begin(),
//                                                     teams.end(),
//                                                     [](const auto& team){return !team->seated;}) << std::endl;

        //resetting cache
        for (auto& team : teams)
        {
            if (!team->seated)
                team->points += points_win;
            team->seated = false;
        }

        std::sort(teams.begin(),
                  teams.end(),
                  [](const auto& lhs, const auto& rhs)
                  {
                      return lhs->points > rhs->points;
                  });
    }

    std::cout << "final standings" << std::endl;
    print_top_x(teams, 10);
}