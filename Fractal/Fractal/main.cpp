#include <iostream>
#include <FractalMath\Vector.h>
#include <FractalMath\Matrix.h>

#include <SDL\SDL.h>
#include <GL\glew.h>

using namespace fractal;

int main(int argc, char* argv[]) {
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

	//test of sdl

	SDL_Init(SDL_INIT_EVERYTHING);
	//set it to use "two" windows making the game smoother
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	Uint32 flags = SDL_WINDOW_OPENGL;
	flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glewInit();
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool running = true;
	while (running) {
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_Event evnt;
		while (SDL_PollEvent(&evnt)) {
			switch (evnt.type) {
				case SDL_QUIT:
				// Exit the game here!
				std::cout << "quit!" << std::endl;
				running = false;
				//return false; //should be removed
				break;
			}
		}

		SDL_GL_SwapWindow(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	//end of sdl test


	getchar();

	return 0;
}