#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <string>

class Deck {
public:
    Deck(); // Constructor to initialize and shuffle the deck
    Card drawCard(); // Draws a card from the deck
    void addToDiscardPile(const Card& card);
    const Card& getTopDiscard() const;
    int cardsRemaining() const;

private:
    std::vector<Card> cards;
    std::vector<Card> discardPile;
    void shuffle(); // Shuffle the deck
};

#endif // DECK_H