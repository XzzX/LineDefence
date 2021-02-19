#include "Hero.h"

#include "CLI/CLI.hpp"

#include <iostream>

void fight_callback(std::string& filename)
{
    auto heros = YAML::LoadFile(filename);
    auto h = create_hero(heros);
    std::cout << h.id << std::endl;
}

int main(int argc, char** argv)
{
    CLI::App app{"App description"};
    app.require_subcommand(1);

    auto fight = app.add_subcommand("fight", "clash of two armies");

    std::string heros_filename = "heros.yaml";
    fight->add_option("--heros", heros_filename, "A help string");
    std::string army1_filename = "army1.yaml";
    fight->add_option("army1", heros_filename, "A help string")->required();
    std::string army2_filename = "army2.yaml";
    fight->add_option("army2", heros_filename, "A help string")->required();
    fight->final_callback([&heros_filename]()
                          {
                              fight_callback(heros_filename);
                          });

    CLI11_PARSE(app, argc, argv);

    return EXIT_SUCCESS;
}