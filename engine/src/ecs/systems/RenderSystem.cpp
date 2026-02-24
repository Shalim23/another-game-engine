module;

#include <SDL3/SDL.h>
#include <SDL3/SDL_messagebox.h>

module render_system;

import std;

void RenderSystem::init()
{
    if(SDL_WasInit(SDL_INIT_VIDEO))
    {
        SDL_assert(false && "SDL video subsystem already initialized");
        return;
    }

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR, 
            "Error", 
            ("Failed to initialize SDL video subsystem: " + std::string(SDL_GetError())).c_str(), 
            nullptr);

        throw std::runtime_error("Failed to initialize SDL video subsystem: " + std::string(SDL_GetError()));
    }
}

void RenderSystem::update()
{
}

void RenderSystem::shutdown()
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
