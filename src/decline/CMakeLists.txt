add_executable(decline
    config.cpp
    error.cpp
    events.cpp
    main.cpp
    view.cpp
    world.cpp
)

target_link_libraries(decline PRIVATE
    SDL2::SDL2-static

    evening
    tempo
    thing

    build-info
)
