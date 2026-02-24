module;

#include <SDL3/SDL.h>

module engine;

Engine::~Engine()
{
    SDL_Quit();
}

void Engine::init()
{

}

bool Engine::runFrame()
{
    return true;
}
