#include "config.hpp"
#include "error.hpp"
#include "events.hpp"
#include "view.hpp"
#include "world.hpp"

#include <build-info.hpp>

#include <evening.hpp>
#include <tempo.hpp>

#include <SDL2/SDL.h>

#include <exception>
#include <sstream>
#include <string>

int main()
{
    auto world = World{};
    auto view = View{};

    bool done = false;
    auto frameTimer = tempo::FrameTimer{config().fps};
    while (!done) {
        done = view.processEvents();

        frameTimer.onFrameAndSleep([&] (int framesPassed, double delta) {
            for (int i = 0; i < framesPassed; i++) {
                world.update(delta);
            }
            view.update(delta * framesPassed);
            view.present();
        });
    }
}
