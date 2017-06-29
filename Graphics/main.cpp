#include "MainGame.h"
#include <iostream>

int main(int argc, char** argv) {
	MainGame mainGame;
	mainGame.run();

	std::cout << "awaiting keyboard input" << std::endl;
	int t;
	std::cin >> t;
	return 0;
}