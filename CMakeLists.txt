cmake_minimum_required(VERSION 3.23)

# Define project
project(
        Beans
        VERSION 1.0
        LANGUAGES CXX
)

# Set CMAKE variables
set(CMAKE_CXX_STANDARD 14)

add_executable(Beans main.cpp Cards/Card.h Chain.cpp Chain.h Cards/Blue.h Cards/Chili.h Cards/Stink.h Cards/Green.h Cards/Soy.h Cards/Black.h Cards/Red.h Cards/Garden.h Structures/Chain.cpp Structures/Chain.h Structures/Deck.h)