#include "../include/Deck.h"
#include <random>
#include <ctime>

Deck::Deck() {
    // Initialize the deck
    std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    for (const auto& suit : suits) {
        for (int rank = 1; rank <= 13; ++rank) {
            cards.push_back({suit, rank});
        }
    }

    // Shuffle the deck using std::shuffle
    std::random_device rd;  // Obtain a random number seed
    std::mt19937 g(rd());   // Seed the random number generator
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::drawCard() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

void Deck::addToDiscardPile(const Card& card) {
    discardPile.push_back(card);
}

const Card& Deck::getTopDiscard() const {
    return discardPile.back();
}

int Deck::cardsRemaining() const {
    return cards.size();
}