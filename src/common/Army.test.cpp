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
    auto army1 = create_random_army(heros_, 10);
    auto army2 = create_random_army(heros_, 10);

    ASSERT_EQ(army1.size(), 10);
    ASSERT_EQ(army2.size(), 10);
}