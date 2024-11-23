#ifndef CARD_H
#define CARD_H

#include <string>

struct Card {
    std::string suit;  // Card suit (e.g., "Hearts", "Diamonds")
    int rank;          // Card rank (1-13, where 1 = Ace, 11-13 = J/Q/K)
};

#endif // CARD_H