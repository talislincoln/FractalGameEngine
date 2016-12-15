#include <iostream>
#include <FractalMath\Math.h>
#include <FractalMath\Matrix.h>
#include <FractalMath\Quaternion.h>
#include <FractalPhysics\include\Transform.h>
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
	quaternionTest();
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

<<<<<<< HEAD
	Quaternion q1(0.237f, 0.06f, -0.257f, -0.935f);
	Quaternion q2(-0.752f, 0.286f, 0.374f, 0.459f);

=======
	Quaternion q1;
	q1.fromEuler(10.0f, 5.0f, 90.0f);
	Quaternion q2;
	q2.fromEuler(7.0f, -80.0f, 360.0f);
	q1.print();
	q2.print();
	printf(" %f \n",q1.angleBetween(q2));
>>>>>>> e68834e9c1dd03f1bf056453103d2977b69e5357
	std::cout << "qdot " << q1.dot(q2) << std::endl;
	std::cout << "qmag " << q1.magnitude() << std::endl;
	std::cout << "qinv " << q1.inverse() << std::endl;
}

void testMath() {
	using namespace fractal;
	using namespace fmath;
	using namespace fphysics;
	fmath::Vector3 a(2, 5, 1);
	fmath::Vector3 b(3, 4, 3);
	Quaternion q1 = Quaternion(15, a.getNormilizedVector());
	Quaternion q2 = Quaternion(30, b.getNormilizedVector());
	fmath::Vector3 c(5, 2, 1);
	fmath::Vector3 d(3, 7, 3);
	Point3 pp(2, 5, 1);
	Point3 pp2(3, 4, 4);
	float angle1 = 15;
	float angle2 = 30;
	Matrix4 projectionMatrix = Matrix4::scale(pp) * q1.toMatrix() * Matrix4::translate(c);
	Matrix4 projectionMatrix2 = Matrix4::scale(pp2) * q2.toMatrix() * Matrix4::translate(d);
	Matrix4 projectionMatrix3;
	Transform tx  = Transform(c, Quaternion(angle1, a), pp);
	Transform tx2 = Transform(d, Quaternion(angle2, b), pp2);
	Matrix4 tx3;
	projectionMatrix3 = projectionMatrix * projectionMatrix2;
	tx3 = tx * tx2;
	projectionMatrix3.print();
	tx3.print();


	//quaternionTest();

	Plane plane1(1, 2, 3, 4);
	Plane plane2(2, 4, 6, 5);
	if (plane1 == plane2) {

		std::cout << "p = p ? ";
	}
}