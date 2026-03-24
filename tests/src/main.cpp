#include <iostream>
#include <mipp.h>
#include <catch2/catch_session.hpp>

int main(int argc, char* argv[])
{
    std::cout << "MIPP tests" << std::endl;
    std::cout << "----------" << std::endl << std::endl;

    // TODO: display MIPP infos here

    int result = Catch::Session().run(argc, argv);

    return result;
}
