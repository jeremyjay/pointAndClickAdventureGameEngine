#include "common.h"
#include "drawObjectsPanel.h"
#include "toolsPanel.h"
#include <functional>



class MainFrame : public wxFrame
{
public:
    MainFrame();
    void UpdateObjectsList();

private:
    void OnDrawObjectsToggle(wxCommandEvent &event);
    void OnSaveButtonClick(wxCommandEvent &event);
    void OnLoadButtonClick(wxCommandEvent &event);
    void OnEditToggle(wxCommandEvent &event);

    DrawObjectPanel *m_drawObjectPanel;
    DrawToolsPanel *m_drawToolsPanel;

    // wxToggleButton *drawObjectsButton;
    // wxToggleButton *editToggleButton;
    // wxChoice *m_objectsList;
};

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Draw Objects", wxDefaultPosition, wxSize(800, 600))
{
    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY);
    // wxPanel *toolsPanel = new wxPanel(splitter, wxID_ANY);
    m_drawToolsPanel = new DrawToolsPanel(splitter, 
        std::bind(&MainFrame::OnDrawObjectsToggle, this, std::placeholders::_1),
        std::bind(&MainFrame::OnSaveButtonClick, this, std::placeholders::_1),
        std::bind(&MainFrame::OnLoadButtonClick, this, std::placeholders::_1),
        std::bind(&MainFrame::OnEditToggle, this, std::placeholders::_1)
    );

    m_drawObjectPanel = new DrawObjectPanel(splitter, 
        std::bind(&MainFrame::UpdateObjectsList, this)
    );



    splitter->SplitVertically(m_drawToolsPanel, m_drawObjectPanel, this->GetSize().GetWidth() / 3);



}

void MainFrame::UpdateObjectsList()
{
    m_drawToolsPanel->m_objectsList->Clear();

    int index = 0;
    for (const auto &object : m_drawObjectPanel->GetObjects())
    {
        m_drawToolsPanel->m_objectsList->Append(wxString::Format("Object %d", index));
        index++;
    }
    std::cout << "update objects list in main" << std::endl;
}


void MainFrame::OnDrawObjectsToggle(wxCommandEvent &event)
{   
    m_drawObjectPanel->EnableDrawObjects(event.IsChecked());
    if (event.IsChecked()) {
        m_drawToolsPanel->editToggleButton->SetValue(false);
        m_drawObjectPanel->EnableEditObjects(false);
    }
}

void MainFrame::OnEditToggle(wxCommandEvent &event)
{
    m_drawObjectPanel->EnableEditObjects(event.IsChecked());
    if (event.IsChecked()) {
        m_drawToolsPanel->drawObjectsButton->SetValue(false);
        m_drawObjectPanel->EnableDrawObjects(false);
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

    m_drawObjectPanel->SaveObjectsToXML(path);
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

    m_drawObjectPanel->LoadObjectsFromXML(path);
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
