#include "common/Army.h"
#include "common/HeroList.h"

#include "gtest/gtest.h"

class ArmyTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        Hero hero;
        hero.id = "A";
        heros_.insert(std::make_pair("A", hero));
        hero.id = "B";
        heros_.insert(std::make_pair("B", hero));
    }

    // void TearDown() override {}

    HeroList heros_;
};

TEST_F(ArmyTest, create_random_army)
{
    Army army1 = create_random_army(heros_, 10);
    Army army2 = create_random_army(heros_, 10);

    ASSERT_EQ(army1.size(), 10);
    ASSERT_EQ(army2.size(), 10);

    bool unequal = false;
    for (int i = 0; i < 10; ++i)
    {
        if (army1[i].id != army2[i].id)
        {
            unequal = true;
            break;
        }
    }
    ASSERT_TRUE(unequal);
}