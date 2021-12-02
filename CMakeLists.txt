cmake_minimum_required(VERSION 3.16)

project(tetris-sdl
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)
find_package(fmt REQUIRED)
pkg_check_modules(SDL2TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_check_modules(SDL2MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    PkgConfig::SDL2TTF
    PkgConfig::SDL2MIXER
    fmt::fmt
)

file(COPY res DESTINATION .)
