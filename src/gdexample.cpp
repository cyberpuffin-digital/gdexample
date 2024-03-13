#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDExample::_bind_methods() {
	return;
}

GDExample::GDExample() {
	// Constructor
	time_passed = 0.0;

	return;
}

GDExample::~GDExample() {
	// Destructor
	return;
}

void GDExample::_process(double delta) {
	time_passed += delta;

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	set_position(new_position);
}

/* Sample function to calculate whether a number is prime. */
bool GDExample::is_prime(int prime_candidate) {
	if (prime_candidate < 2) {
		return false;
	}

	/* per ChatGPT:
	Optimization of Loop Conditions:
	  You can optimize the loop by iterating only up to the square root of the
	  candidate number instead of up to half of the candidate number. This is
	  because if a number has a divisor larger than its square root, then it
	  must also have a corresponding divisor smaller than its square root.
	*/
	int sqrt_candidate = (int)sqrt(prime_candidate);
	for (int divisor = 2; divisor <= sqrt_candidate; ++divisor) {
		if (prime_candidate % divisor == 0) {
			return false;
		}
	}

	return true;
}
