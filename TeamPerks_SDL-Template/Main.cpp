#include "Engine.h"

int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	return Engine::Instance().Run(); // Invokes Run() of the engine and stays in the function until engine is done.
}