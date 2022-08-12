cmake_minimum_required(VERSION 3.22)
project(Poker)

set(CMAKE_CXX_STANDARD 23)

add_executable(Poker main.cpp Card.h Deck.h Player.h Game.h Input.h)
