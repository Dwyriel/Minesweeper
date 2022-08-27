cmake_minimum_required(VERSION 3.23)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Minesweeper main.cpp Source/Window.cpp Source/Window.h Source/DButton.cpp Source/DButton.h)
target_link_libraries(Minesweeper
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

