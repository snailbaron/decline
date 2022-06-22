#include "config.hpp"
#include "error.hpp"

#include <build-info.hpp>

#include <tempo.hpp>

#include <SDL2/SDL.h>

#include <exception>
#include <sstream>
#include <string>

int main()
{
    sdlCheck(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS));

    SDL_Window* window = sdlCheck(SDL_CreateWindow(
        config().windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config().windowWidth,
        config().windowHeight,
        (config().windowType == WindowType::Fullscreen ?
                SDL_WINDOW_FULLSCREEN : 0) |
            (config().windowType == WindowType::BorderlessWindowed ?
                SDL_WINDOW_FULLSCREEN_DESKTOP : 0)));

    SDL_Renderer* renderer = sdlCheck(SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED));

    bool done = false;
    auto frameTimer = tempo::FrameTimer{config().fps};
    while (!done) {
        auto event = SDL_Event{};
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
        }

        int framesPassed = frameTimer();
        if (framesPassed > 0) {
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_Quit();
}
