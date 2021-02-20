#include "common/Army.h"
#include "common/HeroList.h"
#include "fight/fight.h"
#include "tournament/tournament.h"

#include "CLI/CLI.hpp"

int main(int argc, char** argv)
{
    CLI::App app{"multi-purpose tool to evaluate game balancing"};
    app.require_subcommand(1);

    auto fight_cmd = app.add_subcommand("fight", "clash of two armies");
    std::string heros_filename = "heros.yaml";
    fight_cmd->add_option("--heros", heros_filename, "YAML file with available heros")->check(CLI::ExistingFile);
    std::string army1_filename = "";
    fight_cmd->add_option("--army1", army1_filename, "YAML file with army1")->check(CLI::ExistingFile);
    std::string army2_filename = "";
    fight_cmd->add_option("--army2", army2_filename, "YAML file with army2")->check(CLI::ExistingFile);
    int army_size = 10;
    fight_cmd->add_option("-s,--size", army_size, "size of a random army")->check(CLI::NonNegativeNumber);
    fight_cmd->final_callback([&]()
                              {
                                  auto herolist = create_herolist(heros_filename);

                                  auto army1 = army1_filename == "" ?
                                               create_random_army(herolist, army_size) :
                                               create_army(herolist, army1_filename);
                                  auto army2 = army2_filename == "" ?
                                               create_random_army(herolist, army_size) :
                                               create_army(herolist, army2_filename);

                                  std::cout << fight(army1, army2, true) << std::endl;
                              });

    auto tournament_cmd = app.add_subcommand("tournament", "clash of two armies");
    tournament_cmd->add_option("--heros", heros_filename, "YAML file with available heros")->check(CLI::ExistingFile);
    std::string army_filename = "";
    tournament_cmd->add_option("--army", army_filename, "YAML file with army")->check(CLI::ExistingFile);
    int num_teams = 2048;
    tournament_cmd->add_option("-t,--num_teams", num_teams, "number of random teams in the tournament")->check(CLI::NonNegativeNumber);
    int num_rounds = 128;
    tournament_cmd->add_option("-r,--num_rounds", num_rounds, "army size of the teams")->check(CLI::NonNegativeNumber);
    tournament_cmd->final_callback([&]()
                                   {
                                       auto herolist = create_herolist(heros_filename);
                                       auto teams = create_random_teams(herolist, num_teams);
                                       if (army_filename != "")
                                       {
                                           teams.emplace_back(new Team{99999, false, create_army(herolist, army_filename), {}, 0l});
                                       }
                                       tournament(teams, num_rounds);
                                   });

    CLI11_PARSE(app, argc, argv);

    return EXIT_SUCCESS;
}