#include "Hero.h"

#include "CLI/CLI.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    CLI::App app{"App description"};

    std::string filename = "heros.yaml";
    app.add_option("-f,--file", filename, "A help string");

    CLI11_PARSE(app, argc, argv);

    auto heros = YAML::LoadFile(filename);
    auto h = create_hero(heros);
    std::cout << h.id << std::endl;
}