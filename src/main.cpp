#include <wx/wx.h>
#include "MainFrame.h"

class RumiApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(RumiApp);

bool RumiApp::OnInit() {
    MainFrame* frame = new MainFrame("Rumi Card Game");
    frame->Show(true);
    return true;
}