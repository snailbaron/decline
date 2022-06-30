#include "view.hpp"

#include "config.hpp"
#include "error.hpp"

#include <vector>

SdlInit::SdlInit(uint32_t flags)
    : _flags(flags)
{
    sdlCheck(SDL_InitSubSystem(_flags));
}

SdlInit::~SdlInit()
{
    SDL_QuitSubSystem(_flags);
}

View::View()
{
    _window = sdlCheck(SDL_CreateWindow(
        config().windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config().windowWidth,
        config().windowHeight,
        (config().windowType == WindowType::Fullscreen ?
                SDL_WINDOW_FULLSCREEN : 0) |
            (config().windowType == WindowType::BorderlessWindowed ?
                SDL_WINDOW_FULLSCREEN_DESKTOP : 0)));

    _renderer = sdlCheck(SDL_CreateRenderer(
        _window, -1, SDL_RENDERER_ACCELERATED));

    subscribe<event::Create>(events, [this] (const auto& e) {
        _circles[e.id] = {
            .x = e.x,
            .y = e.y,
            .radius = e.radius,
        };
    });
}

bool View::processEvents()
{
    auto event = SDL_Event{};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

void View::update(double delta)
{
    (void)delta;
}

void View::present()
{
    SDL_RenderClear(_renderer);

    static const float isqrt2 = 1.f / std::sqrt(2.f);
    std::vector<SDL_Vertex> vs;
    for (const auto& [id, circle] : _circles) {
        float x = 0.f;
        float y = circle.radius;
        for (int i = 0; i < 8; i++) {
            vs.push_back({.position = {.x = circle.x + x, .y = circle.y + y}});

            float xx = isqrt2 * x - isqrt2 * y;
            y = isqrt2 * x + isqrt2 * y;
            x = xx;
        }
    }
    sdlCheck(SDL_RenderGeometry(
        _renderer, nullptr, vs.data(), vs.size(), nullptr, 0));

    SDL_RenderPresent(_renderer);
}
