#include "error.hpp"

#include "build-info.hpp"

#include <SDL2/SDL.h>

#include <filesystem>

SdlError::SdlError(SourceLocation location)
{
    auto stream = std::ostringstream{};
    auto readablePath =
        std::filesystem::proximate(location.file_name(), SOURCE_ROOT);
    stream << readablePath.string() << ":" <<
        location.line() << ":" <<
        location.column() << ":" <<
        " \"" << location.function_name() << "\": " <<
        SDL_GetError();
    _message = std::move(stream).str();
}

const char* SdlError::what() const noexcept
{
    return _message.c_str();
}

void sdlCheck(int code, SourceLocation location)
{
    if (code != 0) {
        throw SdlError{std::move(location)};
    }
}
