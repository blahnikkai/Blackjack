#include <cassert>
#include "Game.h"

int simpleCompare(int a, int b) {
    if(b > 21)
        return 1;
    if(a > 21)
        return -1;
    if(a > b)
        return 1;
    if(a < b)
        return -1;
    return 0;
}

void testCompare() {
    assert(simpleCompare(12, 20) == -1);
    assert(simpleCompare(19, 4) == 1);
    assert(simpleCompare(21, 21) == 0);
    assert(simpleCompare(22, 20) == -1);
    assert(simpleCompare(25, 27) == 1);
    assert(simpleCompare(5, 20) == -1);
    assert(simpleCompare(12, 12) == 0);
    assert(simpleCompare(19, 29) == 1);
    assert(simpleCompare(25, 25) == 1);
}

void testHighAce() {
    Player bob = Player("Bob");
    //Ace
    bob.addCard(Card(14, 0));
    bob.addCard(Card(5, 1));
    assert(bob.getHandValue() == 16);
    bob.addCard(Card(6, 1));
    assert(bob.getHandValue() == 12);
}

int main() {
    Game game{5};
    game.playGame();

    return 0;
}

//TODO
//double down
//split pairs
//input problems, pressing enter twice, printing instructions twice?
//change addCards so that it automatically moves the vector instead of copying it
//user input filtering for negatives and non integer, you lose when 0
//find better way of doing bettors and players
//change recursion?