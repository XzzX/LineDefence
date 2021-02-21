#include "Hero.h"
#include "gtest/gtest.h"

TEST(Hero, YAML)
{
    YAML::Node hero;
    hero["id"] = "Giant";
    hero["costs"] = 100;
    hero["hp"] = 200;
    hero["damage"] = 300;
    hero["armor"] = 400;
    Hero h1 = create_hero(hero);
    Hero h2;
    h2.id = "Giant";
    h2.costs = 100;
    h2.hp = 200;
    h2.damage = 300;
    h2.armor = 400;

    ASSERT_EQ(h1, h2);
}