#pragma once

#include <string>

enum class WindowType {
    Fullscreen,
    BorderlessWindowed,
    Windowed,
};

struct Config {
    WindowType windowType = WindowType::Windowed;
    std::string windowTitle = "Decline";
    int windowWidth = 1980;
    int windowHeight = 1080;
    int fps = 60;
};

const Config& config();
