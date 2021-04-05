cmake_minimum_required(VERSION 3.5)

project(tetris-sdl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(PkgConfig REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})

pkg_check_modules(SDL2TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
target_link_libraries(${PROJECT_NAME} PkgConfig::SDL2TTF)

pkg_check_modules(SDL2MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
target_link_libraries(${PROJECT_NAME} PkgConfig::SDL2MIXER)

find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

file(COPY res DESTINATION .)
