cmake_minimum_required(VERSION 3.25)
project(PA2_PACMAN)

set(CMAKE_CXX_STANDARD 17)

add_executable(PA2_PACMAN src/main.cpp src/CPacManGame.cpp src/CPacManGame.h src/CUIMenu.cpp src/CUIMenu.h  src/CGhost.cpp src/CGhost.h src/CMove.cpp src/CMove.h src/CPrint.cpp src/CPrint.h  src/exceptions.cpp src/exceptions.h src/ConfigurationManagement.cpp src/ConfigurationManagement.h)
