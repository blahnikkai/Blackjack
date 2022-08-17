//
// Created by Kai Blahnik on 7/6/22.
//

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <vector>
#include <string>
#include <stdexcept>
#include "Deck.h"
#include "Card.h"
#include "Input.h"

using std::vector, std::string, std::cout;

const int STARTING_MONEY = 1000;

class Player {

public:

    explicit Player(string n) {
        name = std::move(n);
    }

    void addCard(const Card & card) {
        hand.push_back(card);
    }

    vector<Card> discardHand() {
        auto temp = hand;
        hand.clear();
        return temp;
    }

    int getHandValue() {
        int total = 0;
        for(const Card card: hand) {
            total += card.getValue();
        }
        if(total > 21) {
            int ind = findHighAce();
            if(ind != -1) {
                hand[ind].setHigh(false);
                return getHandValue();
            }
        }
        return total;
    }

    int findHighAce() const {
        for(int i = 0; i < hand.size(); ++i)
            if(isHighAce(hand[i]))
                return i;
        return -1;
    }

    int compare(Player & other) {
        if(other.getHandValue() > 21)
            return 1;
        if(getHandValue() > 21)
            return -1;
        if(getHandValue() > other.getHandValue())
            return 1;
        if(getHandValue() < other.getHandValue())
            return -1;
        return 0;
    }

    virtual int turnDecision() {
        enterContinue();
        if(getHandValue() < 17) return 1;
        else return 0;
    }

    friend std::ostream & operator<<(std::ostream & strm, Player & p) {
        string value = std::to_string(p.getHandValue());
        if(p.hole)
            value = "Unknown";
        strm << p.name << ": " << value;
        for(int i = 0; i < p.hand.size(); ++i) {
            if(p.hole && i == 0)
                strm << "\n\t" << "X HOLE CARD X";
            else
                strm << "\n\t" << p.hand[i];
        }
        return strm;
    }

    const string & getName() const {return name;}
    void setHole(bool h) {hole = h;}


private:
    bool hole{};
    string name;
    vector<Card> hand;
};

class Bettor : public Player {

public:
    explicit Bettor(string n) : Player(std::move(n)) {
        money = STARTING_MONEY;
        bet = -1;
    };

    virtual void betDecision() {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, money);
        bet = distr(gen);
    }

    int getBet() const {return bet;}
    int getMoney() const {return money;}
    void setMoney(int m) {money = m;}

protected:
    int money;
    int bet;
};

class Human : public Bettor {

public:

    explicit Human(string n) : Bettor(std::move(n)) {};

    void betDecision() override {
        cout << "How much do you want to bet?\n";
        string input = userInput();
        int b = -1;
        try {
            b = std::stoi(input);
        }
        catch(std::invalid_argument & e) {
            cout << "Your bet must be an integer\n";
            return betDecision();
        }
        if(b > getMoney()) {
            cout << "You cannot bet more than your current money\n";
            return betDecision();
        }
        if(b <= 0) {
            cout << "Your bet must be a positive integer\n";
            return betDecision();
        }
        bet = b;
    }

    int turnDecision() override {
        cout << "Hit or stand? Type all lowercase\n";
        string input = userInput();
        if(input == "stand") return 0;
        if(input == "hit") return 1;
        else return turnDecision();
    }
};

#endif //POKER_PLAYER_H
