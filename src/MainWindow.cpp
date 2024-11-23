#include "../include/MainWindow.h"
#include "../include/ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    gameManager.initializeGame();
    updateGameView();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateGameView() {
    // Update player's hand view
    ui->playerHandList->clear();
    for (const auto& card : gameManager.player.getHand()) {
        ui->playerHandList->addItem(gameManager.getCardDescription(card));
    }

    // Update discard pile
    if (gameManager.deck.cardsRemaining() > 0) {
        ui->discardPileLabel->setText("Top Discard: " +
                                      gameManager.getCardDescription(gameManager.deck.getTopDiscard()));
    } else {
        ui->discardPileLabel->setText("Discard Pile is Empty");
    }

    // Update scores
    ui->playerScoreLabel->setText("Player Score: " + QString::number(gameManager.playerScore));
    ui->computerScoreLabel->setText("Computer Score: " + QString::number(gameManager.computerScore));
}

void MainWindow::on_replaceButton_clicked() {
    // Get selected card to replace
    int selectedIndex = ui->playerHandList->currentRow();
    if (selectedIndex < 0 || selectedIndex >= gameManager.player.getHand().size()) {
        QMessageBox::warning(this, "Invalid Selection", "Please select a card to replace.");
        return;
    }

    gameManager.playerReplaceCard(selectedIndex);
    gameManager.computerReplaceCard();

    updateGameView();
}

void MainWindow::on_showdownButton_clicked() {
    int playerValue = gameManager.calculatePlayerValue();
    int computerValue = gameManager.calculateComputerValue();

    QString message;
    if (playerValue < computerValue) {
        message = "You win the showdown!";
        gameManager.computerScore += computerValue;
    } else {
        message = "Computer wins the showdown!";
        gameManager.playerScore += playerValue;
    }

    displayWinner(message);
    gameManager.initializeGame();
    updateGameView();
}

void MainWindow::displayWinner(const QString& message) {
    QMessageBox::information(this, "Showdown Result", message +
                             "\n\nPlayer Hand Value: " + QString::number(gameManager.calculatePlayerValue()) +
                             "\nComputer Hand Value: " + QString::number(gameManager.calculateComputerValue()));
}