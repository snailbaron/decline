add_executable(decline
    config.cpp
    error.cpp
    main.cpp
)
target_link_libraries(decline PRIVATE
    SDL2::SDL2-static

    tempo

    build-info
)
