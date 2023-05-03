#include "common.h"
#include "drawSquaresPanel.h"
#include "toolsPanel.h"
#include <functional>



class MainFrame : public wxFrame
{
public:
    MainFrame();
    void UpdateSquaresList();

private:
    void OnDrawSquaresToggle(wxCommandEvent &event);
    void OnSaveButtonClick(wxCommandEvent &event);
    void OnLoadButtonClick(wxCommandEvent &event);
    void OnEditToggle(wxCommandEvent &event);

    DrawSquarePanel *m_drawSquarePanel;
    DrawToolsPanel *m_drawToolsPanel;

    // wxToggleButton *drawSquaresButton;
    // wxToggleButton *editToggleButton;
    // wxChoice *m_squaresList;
};

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Draw Squares", wxDefaultPosition, wxSize(800, 600))
{
    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY);
    // wxPanel *toolsPanel = new wxPanel(splitter, wxID_ANY);
    m_drawToolsPanel = new DrawToolsPanel(splitter, 
        std::bind(&MainFrame::OnDrawSquaresToggle, this, std::placeholders::_1),
        std::bind(&MainFrame::OnSaveButtonClick, this, std::placeholders::_1),
        std::bind(&MainFrame::OnLoadButtonClick, this, std::placeholders::_1),
        std::bind(&MainFrame::OnEditToggle, this, std::placeholders::_1)
    );

    m_drawSquarePanel = new DrawSquarePanel(splitter, 
        std::bind(&MainFrame::UpdateSquaresList, this)
    );



    splitter->SplitVertically(m_drawToolsPanel, m_drawSquarePanel, this->GetSize().GetWidth() / 3);



}

void MainFrame::UpdateSquaresList()
{
    m_drawToolsPanel->m_squaresList->Clear();

    int index = 0;
    for (const auto &square : m_drawSquarePanel->GetSquares())
    {
        m_drawToolsPanel->m_squaresList->Append(wxString::Format("Square %d", index));
        index++;
    }
    std::cout << "update squares list in main" << std::endl;
}


void MainFrame::OnDrawSquaresToggle(wxCommandEvent &event)
{   
    m_drawSquarePanel->EnableDrawSquares(event.IsChecked());
    if (event.IsChecked()) {
        m_drawToolsPanel->editToggleButton->SetValue(false);
        m_drawSquarePanel->EnableEditSquares(false);
    }
}

void MainFrame::OnEditToggle(wxCommandEvent &event)
{
    m_drawSquarePanel->EnableEditSquares(event.IsChecked());
    if (event.IsChecked()) {
        m_drawToolsPanel->drawSquaresButton->SetValue(false);
        m_drawSquarePanel->EnableDrawSquares(false);
    }
}


void MainFrame::OnSaveButtonClick(wxCommandEvent &event) {
    wxFileDialog saveFileDialog(this, "Save XML file", "", "",
                                 "XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = saveFileDialog.GetPath();

    if (path.IsEmpty()) {
        wxMessageBox("Please select a valid file path.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    m_drawSquarePanel->SaveSquaresToXML(path);
}

void MainFrame::OnLoadButtonClick(wxCommandEvent &event) {
    wxFileDialog loadFileDialog(this, "Load XML file", "", "",
                                 "XML files (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (loadFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = loadFileDialog.GetPath();

    if (path.IsEmpty()) {
        wxMessageBox("Please select a valid file path.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    m_drawSquarePanel->LoadSquaresFromXML(path);
}


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    MainFrame *mainFrame = new MainFrame();
    mainFrame->Show(true);
    return true;
}
