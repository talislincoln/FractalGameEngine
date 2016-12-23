#include <FractalMath\Quaternion.h>

int main() {
	using namespace fractal;
	using namespace fmath;

	Quaternion q1 = Quaternion::fromEuler(10.0f, 5.0f, 90.0f);
	q1.print();
	Quaternion q2 = Quaternion::fromEuler(7.0f, -80.0f, 360.0f);
	q2.print();

	printf("q1 * q2 = %f\n", q1 * q2);
	printf("q1 . q2 = %f\n", q1.dot( q2));

	std::cout << "q1 to matrix:\n" << q1.toMatrix() << std::endl;
	std::cout << "|q1| = " << q1.magnitude() << std::endl;
	std::cout << "normalizing q1... " << q1.normalize() << std::endl;
	std::cout << "|q1| = " << q1.magnitude() << std::endl;

	float angle = q1.getAngleBetween(q2);
	printf("\nAngle between two quaternions: %f\n", angle);

	std::cout << "\nq2 inverse:\n" << q2.inverse() << std::endl;

	getchar();
	

	return 0;
}