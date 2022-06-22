if(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    add_compile_options(/W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(build-info)
add_subdirectory(decline)
