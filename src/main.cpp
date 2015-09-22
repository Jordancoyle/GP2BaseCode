#include "Common.h"

int main(int argc, char * arg[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "error SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}

    return 0;
}
