#pragma once

#include "events.hpp"

#include <SDL2/SDL.h>

#include <map>

struct Camera {
};

struct Circle {
    float x = 0.f;
    float y = 0.f;
    float radius = 0.f;
};

class SdlInit {
public:
    SdlInit(uint32_t flags);
    ~SdlInit();

private:
    uint32_t _flags = 0;
};

class View : public evening::Subscriber {
public:
    View();

    void update(double delta);
    void present();

    bool processEvents();

private:
    SdlInit _sdlInit = SdlInit(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    Camera _camera;
    std::map<Id, Circle> _circles;
};
