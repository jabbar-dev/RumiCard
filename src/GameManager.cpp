#include "../include/GameManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

GameManager::GameManager() {
    // Initialize the deck and deal 4 cards to each player
    for (int i = 0; i < 4; ++i) {
        player.drawCard(deck.drawCard());
        computer.drawCard(deck.drawCard());
    }
}

void GameManager::playGame() {
    while (true) {
        // Display player's hand
        std::cout << "\nYour hand:\n";
        int index = 0;
        for (const auto& card : player.getHand()) {
            std::cout << ++index << ": " << card.rank << " of " << card.suit << "\n";
        }

        // Player's turn
        playerTurn();

        // Computer's turn
        computerTurn();

        // Ask if the player wants to call a showdown
        char choice;
        std::cout << "\nDo you want to call a showdown? (y/n): ";
        std::cin >> choice;
        if (choice == 'y') {
            showdown();
            break;
        }
    }
}

void GameManager::playerTurn() {
    std::cout << "\nPlayer's Turn:\n";
    std::cout << "1. Replace a card from the hidden deck\n";
    std::cout << "2. Keep your current hand\n";
    std::cout << "Enter your choice (1 or 2): ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Choose a card to replace (1-" << player.getHand().size() << "): ";
        int replaceIndex;
        std::cin >> replaceIndex;

        if (replaceIndex > 0 && replaceIndex <= player.getHand().size()) {
            Card newCard = deck.drawCard();
            deck.addToDiscardPile(player.getHand()[replaceIndex - 1]);
            player.getHand()[replaceIndex - 1] = newCard;

            std::cout << "You drew: " << newCard.rank << " of " << newCard.suit << "\n";
        } else {
            std::cout << "Invalid choice. Skipping replacement.\n";
        }
    } else {
        std::cout << "You decided to keep your hand.\n";
    }
}

void GameManager::computerTurn() {
    std::cout << "\nComputer's Turn:\n";

    // Display a random funny comment
    displayFunnyComment();

    // Basic logic: randomly decide to replace a card or keep the hand
    bool replace = (std::rand() % 2 == 0);
    if (replace) {
        int replaceIndex = std::rand() % computer.getHand().size();
        deck.addToDiscardPile(computer.getHand()[replaceIndex]);
        computer.getHand()[replaceIndex] = deck.drawCard(); // Uses the non-const getHand()

        std::cout << "Computer replaces a card.\n";
    } else {
        std::cout << "Computer decides to keep its hand.\n";
    }
}

void GameManager::showdown() {
    std::cout << "\nShowdown!\n";

    // Calculate hand values
    int playerValue = player.calculateHandValue();
    int computerValue = computer.calculateHandValue();

    std::cout << "Your hand value: " << playerValue << "\n";
    std::cout << "Computer's hand value: " << computerValue << "\n";

    // Determine winner
    if (playerValue < computerValue) {
        std::cout << "You win this round!\n";
        computerScore += computerValue;
    } else {
        std::cout << "Computer wins this round!\n";
        playerScore += playerValue;
    }

    std::cout << "Current Scores:\n";
    std::cout << "Player: " << playerScore << "\n";
    std::cout << "Computer: " << computerScore << "\n";

    // Check if the game is over
    if (playerScore >= 100) {
        std::cout << "Computer wins the game!\n";
    } else if (computerScore >= 100) {
        std::cout << "You win the game!\n";
    }
}

void GameManager::displayFunnyComment() {
    // Randomize a comment from the computer
    const std::vector<std::string> comments = {
        "Hmm, let me think...",
        "I am not sure, but this looks good!",
        "You might win this time, but don't get cocky!",
        "My cards are unbeatable! (or are they?)",
        "Are you nervous? You should be!",
    };

    int randomIndex = std::rand() % comments.size();
    std::cout << "Computer says: \"" << comments[randomIndex] << "\"\n";
}