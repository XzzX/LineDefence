#include "Hero.h"

#include <iostream>

int main(int argc, char** argv)
{
    auto heros = YAML::LoadFile("heros.yaml");
    auto h = Hero(heros);
    std::cout << h.id << std::endl;
}