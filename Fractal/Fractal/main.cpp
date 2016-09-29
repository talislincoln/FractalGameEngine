#include <iostream>
#include <FractalMath\Vector.h>

using namespace fractal;

int main() {
	fmath::vec3 a(2, 3, 3);
	fmath::vec3 b(3, 4, 3);

	std::cout << " test " << a + b << std::endl;

	getchar();

	return 0;
}