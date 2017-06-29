#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

enum class GameState {PLAY,EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void CreateJuliaSet();
	void CreateMandelbrot();
	
	double MapToReal(int x, int width, double minR, double maxR);
	double MapToImaginary(int y, int height, double minI, double maxI);
	int getMandelbrot(double cr, double ci, int maxIteration);

	SDL_Window* _window;
	int _screenWidth, _screenHeight;
	GameState _gameState;
};

