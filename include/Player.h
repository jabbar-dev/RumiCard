#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player {
public:
    Player();
    void drawCard(const Card& card);
    void discardCard(int index);
    int calculateHandValue() const;

    const std::vector<Card>& getHand() const; // Existing const function
    std::vector<Card>& getHand();            // New non-const function

private:
    std::vector<Card> hand;
};

#endif // PLAYER_H