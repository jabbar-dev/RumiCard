#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "GameManager.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    GameManager gameManager;

    wxListBox* playerHandBox;
    wxStaticText* playerScoreText;
    wxStaticText* computerScoreText;
    wxStaticText* statusText;

    wxButton* pickCardButton;
    wxButton* showdownButton;

    void OnPickCard(wxCommandEvent& event);
    void OnShowdown(wxCommandEvent& event);
    void UpdateView();

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINFRAME_H