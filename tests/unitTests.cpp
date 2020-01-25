#include <src/catch.hpp>
#include <RentCar.h>

using namespace RentCar;

SCENARIO( "Verify no argument returns", "[unitTests.cpp]" )
{
    REQUIRE( RentCar() == "Rent Car" );
}

SCENARIO( "Verify empty string argument returns", "[unitTests.cpp]" )
{
    REQUIRE( RentCar( "" ) == "Rent Car" );
}
