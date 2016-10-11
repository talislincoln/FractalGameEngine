
#include <iostream>
#include "Channel.h"

struct MyEvent { int value; };
struct MyHandler {
	void operator()(const MyEvent& evt) {
		std::cout << "Evt: " << evt.value << "\n";
	}
};

struct MyIntHandler {
	void operator()(const int& i) {
		std::cout << "[int]: " << i << "\n";
	}
};

int main() {
	using namespace fractal;
	using namespace fevent;

	MyEvent a{ 123 };
	MyHandler b, c;
	MyIntHandler d, e, f;

	Channel::addHandler<MyEvent>(&b);
	Channel::addHandler<MyEvent>(&c);

	Channel::broadcast(a);
	Channel::broadcast(MyEvent{ 456 });
	Channel::broadcast(a);

	Channel::removeHandler<MyEvent>(&b);
	Channel::broadcast(MyEvent{ 789 });

	Channel::broadcast(111);

	Channel::addHandler<int>(&d);
	Channel::addHandler<int>(&e);
	Channel::addHandler<int>(&f);

	Channel::broadcast(222);

	Channel::removeHandler<int>(&e);

	Channel::broadcast(333);

	getchar();
	return 0;
}