cmake_minimum_required(VERSION 3.20)
project(2048)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/SFML3")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(2048 main.cpp
        GameLogic.cpp
        GameLogic.h
        Bot.cpp
        Bot.h
        GameUI.cpp
        GameUI.h
        GameController.cpp
        GameController.h)

target_link_libraries(2048 PRIVATE SFML::Graphics SFML::Window SFML::System)