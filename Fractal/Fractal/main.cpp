#include <iostream>
#include <FractalMath\Vector.h>

using namespace fractal;

int main() {
	fmath::vec2 a(2, 3);
	fmath::vec2 b(3, 4);

	std::cout << " test " << a.x + b.x << std::endl;

	getchar();

	return 0;
}