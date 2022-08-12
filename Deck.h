//
// Created by Kai Blahnik on 7/6/22.
//

#ifndef POKER_DECK_H
#define POKER_DECK_H

#include <vector>
#include <random>
#include <string>
#include "Card.h"

using std::vector, std::string;

class Deck {

public:

    explicit Deck(string n) {
        name = std::move(n);
    }

    void fill() {
        for(int s = 0; s <= 3; s++) {
            for(int r = 2; r <= 14; ++r) {
                cards.emplace_back(r, s);
            }
        }
    }

    void shuffle() {
        std::random_device device;
        std::mt19937 rng(device());
        std::uniform_int_distribution<std::mt19937::result_type> card_dist(0, cards.size() - 1);

        for(int card1 = 0; card1 < cards.size(); ++card1) {
            unsigned int card2 = card_dist(rng);
            while(card2 == card1) {
                card2 = card_dist(rng);
            }
            Card temp = cards[card1];
            cards[card1] = cards[card2];
            cards[card2] = temp;
        }
    }

    Card dealCard(Deck & discard) {
        if(cards.empty()) {
            if(discard.cards.empty())
                throw std::runtime_error("Ran out of cards");
            addCards(discard.cards);
            discard.cards.clear();
        }
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    void addCards(vector<Card> newCards) {
        cards.insert(cards.end(), newCards.begin(), newCards.end());
    }

    friend std::ostream & operator<<(std::ostream & strm, const Deck & deck) {
        strm << deck.name << " has the following cards: ";
        for(Card card : deck.cards) {
            strm << "\n\t" << card;
        }
        return strm;
    }

    const vector<Card> & getCards() const {return cards;}

private:
    string name;
    vector<Card> cards;
};

#endif //POKER_DECK_H
