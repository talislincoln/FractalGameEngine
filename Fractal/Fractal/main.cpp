#include <iostream>
#include <FractalMath\Vector.h>
#include <FractalMath\Matrix.h>


using namespace fractal;

int main() {
	fmath::Vector3 a(2,5,1);
	fmath::Vector3 b(3, 4, 3);
	fmath::Matrix4 projectionMatrix;
	projectionMatrix = fmath::Matrix4::rotate(30, 1,0,0) * fmath::Matrix4::translate(2,4,5) * fmath::Matrix4::scale(2,2,2);
	std::cout << fmath::Matrix4::rotate(30, 1, 0, 0);
	std::cout << fmath::Matrix4::translate(2, 4, 5);
	std::cout << fmath::Matrix4::scale(2, 2, 2);

	std::cout << " test " << a + b << std::endl;
	std::cout << " test " << a.dot(b) << std::endl;
	std::cout << " test " << a.cross(b) << std::endl;
	std::cout << " test " << projectionMatrix * a << std::endl;


	getchar();

	return 0;
}