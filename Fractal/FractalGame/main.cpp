#include <iostream>
#include <Fractal\include\core\systems\Engine.h>
#include "Game.h"

//> const, define = all upper case ex: PI, RADIUS_TO_DEGEE
//> Class = all first letter of all words upper case  ex: MyClass
//> function = first letter lower case, the rest of the first letter upper case ex: void myName() {}
//> private = m_myPrivate. <-- that set up
//> public =  first letter lower case, the rest of the first letter upper case ex : int myInt;

int main(int argc, char* argv[]) {

	fractal::fcore::Engine* engine = new fractal::fcore::Engine(new Game());
	engine->run();
	delete engine;

	return 0;
}