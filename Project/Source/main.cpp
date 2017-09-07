#include <iostream>
#include "GameApp.h"
#include "SFML\System.hpp"

int main()
{
	try
	{
		GameApp game;
		game.Run();
	}
	catch (std::exception& e)
	{
		//DEV::printLine("Exception caught: " + pl::stringFrom(e));
		std::cout << "\nEXCEPTION:" << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}