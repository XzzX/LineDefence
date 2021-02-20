#include "Hero.h"
#include "gtest/gtest.h"

TEST(Hero, YAML)
{
    YAML::Node hero;
    hero["id"] = "Giant";
    hero["cost"] = 100;
    hero["hp"] = 200;
    hero["damage"] = 300;
    hero["armor"] = 400;
    Hero h1 = create_hero(hero);
    Hero h2 = {"Giant", 100, 200, 300, 400};

    ASSERT_EQ(h1, h2);
}