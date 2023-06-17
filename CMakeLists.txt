cmake_minimum_required(VERSION 3.25)
project(PA2_PACMAN)

set(CMAKE_CXX_STANDARD 17)

add_executable(PA2_PACMAN vascamat/src/main.cpp vascamat/src/CUIMenu.cpp vascamat/src/CUIMenu.h vascamat/src/CGhost.cpp vascamat/src/CGhost.h vascamat/src/CUtilities.cpp vascamat/src/CUtilities.h vascamat/src/CPrint.cpp vascamat/src/CPrint.h vascamat/src/ConfigurationManagement.cpp vascamat/src/ConfigurationManagement.h vascamat/src/main.h)
