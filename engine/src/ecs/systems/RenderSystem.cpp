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

    // #TODO: Make window parameters configurable
    window = SDL_CreateWindow("Another Game Engine", 800, 600, 0);
    if (!window)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            ("Failed to create SDL window: " + std::string(SDL_GetError())).c_str(),
            nullptr);
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            ("Failed to create SDL renderer: " + std::string(SDL_GetError())).c_str(),
            window);


        throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
    }
}

void RenderSystem::update()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // #TODO: Render textures here

    SDL_RenderPresent(renderer);
}

void RenderSystem::shutdown()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
