#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "gdexample.h"

using namespace godot;

TEST_CASE("testing the is_prime function") {
	CHECK_FALSE(GDExample::is_prime(1));
	CHECK(GDExample::is_prime(3));
	CHECK_FALSE(GDExample::is_prime(9));
	CHECK(GDExample::is_prime(17));
	CHECK(GDExample::is_prime(51));
}
