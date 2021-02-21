configure_file(heros.yaml heros.yaml COPYONLY)
add_executable(LineDefence
        main.cpp common/Hero.h fight/fight.cpp fight/fight.h common/Army.cpp common/Army.h common/HeroList.cpp common/HeroList.h tournament/Team.cpp tournament/Team.h tournament/tournament.cpp tournament/tournament.h)
target_compile_options(LineDefence PRIVATE
        -Wall
        -Wextra
        -Wunreachable-code
        -Wuninitialized
        -Wshadow)
target_include_directories(LineDefence PRIVATE .)
target_link_libraries(LineDefence PRIVATE CLI11 yaml-cpp)

add_executable(LineDefenceTest
        common/Army.cpp
        common/Army.test.cpp
        common/Hero.test.cpp)
target_compile_options(LineDefenceTest PRIVATE
        -Wall
        -Wextra
        -Wunreachable-code
        -Wuninitialized
        -Wshadow)
target_include_directories(LineDefenceTest PRIVATE .)
target_link_libraries(LineDefenceTest PRIVATE yaml-cpp gtest gtest_main)
