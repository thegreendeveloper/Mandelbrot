#include "MainGame.h"
#include <iostream>
#include <string>

void fatalError(std::string errString) {
	std::cout << errString << std::endl;
	std::cout << "Enter any key to quit....";
	int tmp;
	std::cin >> tmp;
	SDL_QUIT;
	exit(1);
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
}


MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL window could not be created!");
	}
	SDL_GLContext context = SDL_GL_CreateContext(_window);
	if (context == nullptr) {
		fatalError("SDL_CONTEXT could not be created!");
	}

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
}

void MainGame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
		default:
			break;
		}
	}
}


void MainGame::CreateJuliaSet() {

	double constantReal = -0.1, constantImagin = 0.651;
	
	double oldReal = 0, newReal = 0, oldImagin = 0, newImagin = 0;

	int maxIterations = 500;

	for (int y = 0; y < _screenHeight; y++) {
		for (int x = 0; x < _screenWidth; x++) {

			/*Julia Set*/
			newReal = 1.5 * (x - _screenWidth / 2) / (0.5 *_screenWidth);
			newImagin = (y - _screenHeight / 2) / (0.5 * _screenHeight);

			int i = 0;
			for (i = 0; i < maxIterations; i++) {

				oldReal = newReal;
				oldImagin = newImagin;

				/*Julia*/
				newReal = oldReal * oldReal - oldImagin * oldImagin + constantReal;
				newImagin = 2 * oldReal * oldImagin + constantImagin;

				if ((newReal * newReal + newImagin * newImagin) > 4) break;
			}

			glBegin(GL_POINTS);
			glColor3f(((int)(i * std::sinf(i)) % 256) / 255.0, (i ^ 2 % 256) / 255.0, (i % 256) / 255.0);
			glVertex2f(x, y);
			glEnd();
		}
	}

}

void MainGame::CreateMandelbrot() {

	double minReal = -1.5, maxReal = 0.7, minImagin = -1.0, maxImagine = 1.0;

	int maxIterations = 400;

	for (int y = 0; y < _screenHeight; y++) {
		for (int x = 0; x < _screenWidth; x++) {
			double cr = MapToReal(x, _screenWidth, minReal, maxReal);
			double ci = MapToImaginary(y, _screenHeight, minImagin, maxImagine);
			
			int n = getMandelbrot(cr, ci, maxIterations);

			glBegin(GL_POINTS);
			glColor3f(((int)(n * std::sinf(n)) % 256) / 255.0, ((n*n) % 256) / 255.0, (n % 256) / 255.0);
			glVertex2f(x, y);
			glEnd();
		}


	}
}

double MainGame::MapToReal(int x, int width, double minR, double maxR) {
	double range = maxR - minR;
	return x * (range / width) + minR;
}

double MainGame::MapToImaginary(int y, int height, double minI, double maxI) {
	double range = maxI - minI;
	return y * (range / height) + minI;
}

int MainGame::getMandelbrot(double cr, double ci, int maxIteration) {
	int i = 0;

	double zr = 0.0, zi = 0.0;
	while (i < maxIteration && zr * zr + zi * zi < 4.0) {
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0* zr * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}


void MainGame::gameLoop() {
	//while (_gameState != GameState::EXIT) {
	processInput();
	drawGame();
	//}

}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_COLOR_ARRAY);

	glOrtho(0.f, _screenWidth, _screenHeight, 0.f, 0.f, 1.f);

	CreateJuliaSet();
	//CreateMandelbrot();
	SDL_GL_SwapWindow(_window);
}

