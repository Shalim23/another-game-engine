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
    bool running = true;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                running = false;
                break;
            }
        }
    }

    return running;
}
