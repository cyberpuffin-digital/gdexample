#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <gdexample.h>

using namespace godot;

TEST_CASE("Test is_prime as a class function") {
	GDExample example;

	CHECK_FALSE(example.is_prime(1));
	CHECK(example.is_prime(3));
	CHECK_FALSE(example.is_prime(9));
	CHECK(example.is_prime(17));
	CHECK(example.is_prime(51));
}

TEST_CASE("Test is_prime as a static function") {
	CHECK_FALSE(GDExample::is_prime(1));
	CHECK(GDExample::is_prime(3));
	CHECK_FALSE(GDExample::is_prime(9));
	CHECK(GDExample::is_prime(17));
	CHECK(GDExample::is_prime(51));
}
