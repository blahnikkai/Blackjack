cmake_minimum_required(VERSION 3.22)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(Blackjack main.cpp Card.h Deck.h Player.h Game.h Input.h)
