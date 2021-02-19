#include "fight.h"

#include "Army.h"
#include "HeroList.h"

#include "CLI/CLI.hpp"

int main(int argc, char** argv)
{
    CLI::App app{"multi-purpose tool to evaluate game balancing"};
    app.require_subcommand(1);

    auto fight = app.add_subcommand("fight", "clash of two armies");

    std::string heros_filename = "heros.yaml";
    fight->add_option("--heros", heros_filename, "YAML file with available heros")->check(CLI::ExistingFile);
    std::string army1_filename = "";
    fight->add_option("--army1", army1_filename, "YAML file with army1")->check(CLI::ExistingFile);
    std::string army2_filename = "";
    fight->add_option("--army2", army2_filename, "YAML file with army2")->check(CLI::ExistingFile);
    int army_size = 10;
    fight->add_option("-s,--size", army_size, "size of a random army")->check(CLI::NonNegativeNumber);
    fight->final_callback([&]()
                          {
                              auto herolist = create_herolist(heros_filename);

                              auto army1 = army1_filename == "" ?
                                      create_random_army(herolist, army_size) :
                                      create_army(herolist, army1_filename);
                              auto army2 = army2_filename == "" ?
                                      create_random_army(herolist, army_size) :
                                      create_army(herolist, army2_filename);

                              fight_callback(army1, army2);
                          });

    CLI11_PARSE(app, argc, argv);

    return EXIT_SUCCESS;
}