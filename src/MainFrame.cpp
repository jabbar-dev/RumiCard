#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(1001, MainFrame::OnPickCard)
    EVT_BUTTON(1002, MainFrame::OnShowdown)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
    gameManager = GameManager();

    wxPanel* panel = new wxPanel(this, -1);

    // Player hand display
    new wxStaticText(panel, wxID_ANY, "Your Hand:", wxPoint(10, 10));
    playerHandBox = new wxListBox(panel, wxID_ANY, wxPoint(10, 30), wxSize(200, 150));

    // Scores
    playerScoreText = new wxStaticText(panel, wxID_ANY, "Player Score: 0", wxPoint(220, 30));
    computerScoreText = new wxStaticText(panel, wxID_ANY, "Computer Score: 0", wxPoint(220, 60));

    // Game status
    statusText = new wxStaticText(panel, wxID_ANY, "Game Started!", wxPoint(10, 200), wxSize(400, 30));

    // Buttons
    pickCardButton = new wxButton(panel, 1001, "Pick a Card", wxPoint(10, 250));
    showdownButton = new wxButton(panel, 1002, "Showdown", wxPoint(120, 250));

    UpdateView();
}

void MainFrame::OnPickCard(wxCommandEvent& event) {
    gameManager.playerTurn();
    gameManager.computerTurn();
    UpdateView();

    if (gameManager.playerScore >= gameManager.gameLimit || gameManager.computerScore >= gameManager.gameLimit) {
        wxMessageBox("Game Over!");
        Close(true);
    }
}

void MainFrame::OnShowdown(wxCommandEvent& event) {
    gameManager.showdown();
    UpdateView();

    if (gameManager.playerScore >= gameManager.gameLimit || gameManager.computerScore >= gameManager.gameLimit) {
        wxMessageBox("Game Over!");
        Close(true);
    }
}

void MainFrame::UpdateView() {
    // Update player hand
    playerHandBox->Clear();
    for (const auto& card : gameManager.player.getHand()) {
        playerHandBox->Append(wxString::Format("%d of %s", card.rank, card.suit));
    }

    // Update scores
    playerScoreText->SetLabel(wxString::Format("Player Score: %d", gameManager.playerScore));
    computerScoreText->SetLabel(wxString::Format("Computer Score: %d", gameManager.computerScore));

    // Update status
    statusText->SetLabel("Game is ongoing...");
}