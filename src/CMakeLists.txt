configure_file(heros.yaml heros.yaml COPYONLY)
add_executable(LineDefence
        main.cpp Hero.h)
target_compile_options(LineDefence PRIVATE
        -Wall
        -Wextra
        -Wunreachable-code
        -Wuninitialized
        -Wshadow)
target_link_libraries(LineDefence PRIVATE CLI11 yaml-cpp)

add_executable(LineDefenceTest
        Hero.test.cpp)
target_compile_options(LineDefenceTest PRIVATE
        -Wall
        -Wextra
        -Wunreachable-code
        -Wuninitialized
        -Wshadow)
target_link_libraries(LineDefenceTest PRIVATE yaml-cpp)
target_link_libraries(LineDefenceTest PRIVATE gtest gtest_main)
