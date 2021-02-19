configure_file(heros.yaml heros.yaml COPYONLY)
add_executable(LineDefence
        main.cpp Hero.h)
target_compile_options(LineDefence PRIVATE
        -Wall
        -Wextra
        -Wunreachable-code
        -Wuninitialized
        -Wshadow)
target_link_libraries(LineDefence PRIVATE yaml-cpp)
