//
// Created by Kai Blahnik on 7/6/22.
//

#ifndef POKER_CARD_H
#define POKER_CARD_H

#include <iostream>
#include <array>
#include <string>

const std::array<std::string, 4> SUITS = {
    "spades",
    "clubs",
    "hearts",
    "diamonds"
};

const std::array<std::string, 13> RANK_STRINGS = {
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King",
    "Ace"
};

class Card {

public:

    Card(int r, int s) {
        if(r < 2 || r > 14)
            throw std::invalid_argument( "Card rank is out of possible range" );
        rank = r;
        suit = s;
        high = r == 14;
    }

    int getValue() const {
        if(rank <= 10) return rank;
        else if(rank == 14 && high) return 11;
        else if(rank == 14 && !high) return 1;
        else return 10;
    }

    friend std::ostream & operator<<(std::ostream & strm, const Card & card) {
        strm << "[" << card.getValue() << "] "
            << RANK_STRINGS[card.rank - 2]
            << " of " << SUITS[card.suit];
        return strm;
    }

    int getRank() const {
        return rank;
    }

    bool getHigh() const {
        return high;
    }

    void setHigh(bool h) {
        high = h;
    }

private:
    int rank;
    int suit;
    bool high;
};

bool isHighAce(const Card & c) {
    return c.getRank() == 14 && c.getHigh();
}

#endif //POKER_CARD_H
