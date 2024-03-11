#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include "doctest.h"
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class GDExample : public Sprite2D {
	GDCLASS(GDExample, Sprite2D)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	GDExample();
	~GDExample();

	void _process(double delta) override;
	static bool is_prime(int prime_candidate);
};

} //namespace godot

#endif // GDEXAMPLE_H
