#include "../include/Player.h"


Player::Player() {}

void Player::drawCard(const Card& card) {
    hand.push_back(card);
}

void Player::discardCard(int index) {
    if (index >= 0 && index < hand.size()) {
        hand.erase(hand.begin() + index);
    }
}

int Player::calculateHandValue() const {
    int total = 0;
    for (const auto& card : hand) {
        total += (card.rank > 10) ? 10 : card.rank;
    }
    return total;
}

const std::vector<Card>& Player::getHand() const {
    return hand;
}

std::vector<Card>& Player::getHand() { // Non-const version
    return hand;
}