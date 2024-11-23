#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Deck.h"
#include "Player.h"

class GameManager {
public:
    GameManager();
    void playGame(); // Main game loop

private:
    Deck deck;
    Player player;
    Player computer;
    int playerScore = 0;
    int computerScore = 0;

    void playerTurn();
    void computerTurn();
    void showdown();
    void displayFunnyComment(); // Random funny comments from the computer
};

#endif // GAMEMANAGER_H