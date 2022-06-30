#pragma once

#include <exception>
#include <ostream>
#include <sstream>

#ifdef __clang__
    #include <experimental/source_location>
    using SourceLocation = std::experimental::source_location;
#else
    #include <source_location>
    using SourceLocation = std::source_location;
#endif

template <class T>
concept Streamable = requires (std::ostream& s, T x) { s << x; };

class Error : public std::exception {
public:
    Error(SourceLocation location = SourceLocation::current());

    template <Streamable T>
    Error& operator<<(T&& value) &
    {
        updateMessage(std::forward<T>(value));
        return *this;
    }

    template <Streamable T>
    Error&& operator<<(T&& value) &&
    {
        updateMessage(std::forward<T>(value));
        return std::move(*this);
    }

    const char* what() const noexcept override
    {
        return _message.c_str();
    }

private:
    template <Streamable T>
    void updateMessage(T&& value)
    {
        auto stream = std::ostringstream{std::move(_message)};
        stream << std::forward<T>(value);
        _message = std::move(stream).str();
    }

    std::string _message;
};

void check(bool condition, SourceLocation location = SourceLocation::current());

class SdlError : public std::exception {
public:
    SdlError(SourceLocation location = SourceLocation::current());
    const char* what() const noexcept override;

private:
    std::string _message;
};

void sdlCheck(int code, SourceLocation location = SourceLocation::current());

template <class T>
T* sdlCheck(T* ptr, SourceLocation location = SourceLocation::current())
{
    if (!ptr) {
        throw SdlError{std::move(location)};
    }
    return ptr;
}
