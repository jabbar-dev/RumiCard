#include "../include/GameManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

GameManager::GameManager() {
    // Ask the user for the game limit and penalty
    std::cout << "Enter the game score limit (e.g., 200): ";
    std::cin >> gameLimit;

    std::cout << "Enter the penalty for an incorrect showdown (e.g., 30): ";
    std::cin >> penalty;

    // Initialize the deck and deal 4 cards to each player
    for (int i = 0; i < 4; ++i) {
        player.drawCard(deck.drawCard());
        computer.drawCard(deck.drawCard());
    }
}

void GameManager::playGame() {
    while (playerScore < gameLimit && computerScore < gameLimit) {
        // Display player's hand
        std::cout << "\nYour hand:\n";
        int index = 0;
        for (const auto& card : player.getHand()) {
            std::cout << ++index << ": " << card.rank << " of " << card.suit << "\n";
        }

        // Display total hand value
        std::cout << "Your total hand value: " << player.calculateHandValue() << "\n";

        // Player's turn
        playerTurn();

        // Display computer's total hand value
        std::cout << "Computer's total hand value: " << computer.calculateHandValue() << "\n";

        // Computer's turn
        computerTurn();

        // Check if the game is over
        if (playerScore >= gameLimit || computerScore >= gameLimit) {
            break;
        }
    }

    // Determine the loser
    if (playerScore >= gameLimit) {
        std::cout << "\nYou reached the score limit of " << gameLimit << "! You lose!\n";
    } else if (computerScore >= gameLimit) {
        std::cout << "\nThe computer reached the score limit of " << gameLimit << "! You win!\n";
    }
}

void GameManager::playerTurn() {
    std::cout << "\nPlayer's Turn:\n";
    std::cout << "1. Pick a new card and replace one in your hand\n";
    std::cout << "2. Call a showdown\n";
    std::cout << "Enter your choice (1 or 2): ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Replace a card from the deck
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
    } else if (choice == 2) {
        // Player decides to call a showdown
        showdown();
        return;
    } else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void GameManager::computerTurn() {
    std::cout << "\nComputer's Turn:\n";

    // Display a random funny comment
    displayFunnyComment();

    // Basic logic: Computer always replaces a card
    int replaceIndex = std::rand() % computer.getHand().size();
    deck.addToDiscardPile(computer.getHand()[replaceIndex]);
    computer.getHand()[replaceIndex] = deck.drawCard();

    std::cout << "Computer replaces a card.\n";
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
    } else if (playerValue > computerValue) {
        std::cout << "Computer wins this round, and you get a penalty of " << penalty << " points!\n";
        playerScore += playerValue + penalty;
    } else {
        std::cout << "It's a tie! Both scores remain unchanged.\n";
    }

    std::cout << "Current Scores:\n";
    std::cout << "Player: " << playerScore << "\n";
    std::cout << "Computer: " << computerScore << "\n";

    // Check if the game is over
    if (playerScore >= gameLimit) {
        std::cout << "\nYou reached the score limit of " << gameLimit << "! You lose!\n";
    } else if (computerScore >= gameLimit) {
        std::cout << "\nThe computer reached the score limit of " << gameLimit << "! You win!\n";
    }

    // Restart hands for the next round
    player.getHand().clear();
    computer.getHand().clear();
    for (int i = 0; i < 4; ++i) {
        player.drawCard(deck.drawCard());
        computer.drawCard(deck.drawCard());
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