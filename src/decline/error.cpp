#include "error.hpp"

#include "build-info.hpp"

#include <SDL2/SDL.h>

#include <filesystem>
#include <ostream>

namespace {

class FormatLocation {
public:
    FormatLocation(SourceLocation location)
        : _location(location)
    { }

    friend std::ostream& operator<<(
        std::ostream& output, const FormatLocation& fl)
    {
        auto readablePath =
            std::filesystem::proximate(fl._location.file_name(), SOURCE_ROOT);
        return output << readablePath.string() << ":" <<
            fl._location.line() << ":" << fl._location.column() << ":" <<
            " \"" << fl._location.function_name() << "\": ";
    }

private:
    SourceLocation _location;
};

std::string locationString(SourceLocation location)
{
    auto stream = std::ostringstream{};
    stream << FormatLocation{location};
    return stream.str();
}

} // namespace

Error::Error(SourceLocation location)
    : _message(locationString(location))
{ }

void check(bool condition, SourceLocation location)
{
    if (!condition) {
        throw Error{std::move(location)};
    }
}

SdlError::SdlError(SourceLocation location)
{
    auto stream = std::ostringstream{};
    stream << FormatLocation{location} << SDL_GetError();
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
