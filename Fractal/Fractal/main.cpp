#include <iostream>
#include <FractalMath\Math.h>
#include <FractalMath\Matrix.h>
#include <FractalMath\TQuaternion.h>

#include "core\systems\Engine.h"
#include "MyGame.h"

//> const, define = all upper case ex: PI, RADIUS_TO_DEGEE
//> Class = all first letter of all words upper case  ex: MyClass
//> function = first letter lower case, the rest of the first letter upper case ex: void myName() {}
//> private = m_myPrivate. <-- that set up
//> public =  first letter lower case, the rest of the first letter upper case ex : int myInt;

void quaternionTest();

void testMath();

int main(int argc, char* argv[]) {
	//quaternionTest();
	//testMath();

	fractal::fcore::Engine* engine = new fractal::fcore::Engine(new MyGame());
	engine->run();
	delete engine;

	//getchar();

	return 0;
}

void quaternionTest() {
	using namespace fractal;
	using namespace fmath;

	TQuaternion q1(0.237f, 0.06f, -0.257f, -0.935);
	TQuaternion q2(-0.752f, 0.286f, 0.374f, 0.459);

	std::cout << "qdot " << q1.dot(q2) << std::endl;
	std::cout << "qmag " << q1.magnitude() << std::endl;
	std::cout << "qinv " << q1.inverse() << std::endl;
}

void testMath() {
	using namespace fractal;
	using namespace fmath;

	fmath::Vector3 a(2, 5, 1);
	fmath::Vector3 b(3, 4, 3);
	Vector3 c = a + b;
	Point3 pp(2, 5, 1);
	Point3 pp2(3, 4, 4);
	c = pp + pp2;
	std::cout << " a + b " << c << std::endl;
	fmath::Matrix4 projectionMatrix = fmath::Matrix4::rotate(30, 1, 0, 0) * fmath::Matrix4::translate(2, 4, 5) * fmath::Matrix4::scale(2, 2, 2);
	std::cout << fmath::Matrix4::rotate(30, 1, 0, 0);
	std::cout << fmath::Matrix4::translate(2, 4, 5);
	std::cout << fmath::Matrix4::scale(2, 2, 2);
	std::cout << projectionMatrix;
	projectionMatrix.print();

	std::cout << " test " << a + b << std::endl;
	std::cout << " test " << a.dot(b) << std::endl;
	std::cout << " test " << a.cross(b) << std::endl;
	std::cout << " test " << projectionMatrix * a << std::endl;

	fmath::Point3 p(1.0f, 2.0f, 3.0f);
	fmath::Point3 p2(0.0f, 0.0f, 1.0f);
	p = p2;

	//p = a.normalize();
	b = p2;

	std::cout << " point " << p << std::endl;
	std::cout << " a " << a.normalize() << std::endl;

	std::cout << " a " << a << std::endl;

	quaternionTest();

	Plane plane1(1, 2, 3, 4);
	Plane plane2(2, 4, 6, 5);
	if (plane1 == plane2) {

		std::cout << "p = p ? ";
	}
}