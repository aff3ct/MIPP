#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <iostream>
//#include <mipp_v2.h>
int main(int argc, char* argv[])
{
	std::cout << "MIPP V2 tests" << std::endl;
	std::cout << "----------" << std::endl << std::endl;

	int result = Catch::Session().run(argc, argv);

	return result;
}
