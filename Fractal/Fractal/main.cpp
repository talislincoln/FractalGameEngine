#include <iostream>
#include <FractalMath\Vector.h>
#include <FractalMath\Matrix.h>

//> const, define = all upper case ex: PI, RADIUS_TO_DEGEE
//> Class = all first letter of all words upper case  ex: MyClass
//> function = first letter lower case, the rest of the first letter upper case ex: void myName() {}
//> private = m_myPrivate. <-- that set up
//> public =  first letter lower case, the rest of the first letter upper case ex : int myInt;


using namespace fractal;

int main() {

	fmath::vec3 a(2,5,1);
	fmath::vec3 b(3, 4, 3);
	fmath::Matrix4 projectionMatrix;
	projectionMatrix = fmath::Matrix4::rotate(30, 1,0,0) * fmath::Matrix4::translate(2,4,5) * fmath::Matrix4::scale(2,2,2);
	std::cout << fmath::Matrix4::rotate(30, 1, 0, 0);
	std::cout << fmath::Matrix4::translate(2, 4, 5);
	std::cout << fmath::Matrix4::scale(2, 2, 2);
	std::cout << projectionMatrix;
	projectionMatrix.print();

	std::cout << " test " << a + b << std::endl;
	std::cout << " test " << a.dot(b) << std::endl;
	std::cout << " test " << a.cross(b) << std::endl;
	std::cout << " test " << projectionMatrix * a << std::endl;


	getchar();

	return 0;
}