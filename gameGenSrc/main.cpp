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
    void OnObjectsListSelected(wxCommandEvent &event);
    void OnObjectImageButtonClicked(wxCommandEvent& event);

    DrawObjectPanel *m_drawObjectPanel;
    DrawToolsPanel *m_drawToolsPanel;

    wxCursor m_customCursor;

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
        std::bind(&MainFrame::OnEditToggle, this, std::placeholders::_1),
        std::bind(&MainFrame::OnObjectsListSelected, this, std::placeholders::_1),
        std::bind(&MainFrame::OnObjectImageButtonClicked, this, std::placeholders::_1)
    );

    m_drawObjectPanel = new DrawObjectPanel(splitter, 
        std::bind(&MainFrame::UpdateObjectsList, this)
    );



    splitter->SplitVertically(m_drawToolsPanel, m_drawObjectPanel, this->GetSize().GetWidth() / 3);






    // // In MainFrame constructor:
    // wxImage cursorImage;
    // cursorImage.LoadFile("../assets/sprites/magnifying_glass.png");
    // m_customCursor = wxCursor(cursorImage);


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

    // int endIndex = m_drawToolsPanel->m_objectsList->GetSelEnd();
    int selectedIndex = m_drawToolsPanel->m_objectsList->GetCount() - 1;

    if (selectedIndex >= 0 && selectedIndex < m_drawObjectPanel->m_objects.size()) {
        m_drawToolsPanel->m_objectsList->SetSelection(selectedIndex);
        InteractiveObject &selectedObject = m_drawObjectPanel->m_objects[selectedIndex];
        m_drawToolsPanel->m_objectXText->SetValue(wxString::Format("%d", selectedObject.x));
        m_drawToolsPanel->m_objectYText->SetValue(wxString::Format("%d", selectedObject.y));
        m_drawToolsPanel->m_objectWidthText->SetValue(wxString::Format("%d", selectedObject.width));
        m_drawToolsPanel->m_objectHeightText->SetValue(wxString::Format("%d", selectedObject.height));
  
        std::cout << "x: " << selectedObject.x << std::endl;
        std::cout << "y: " << selectedObject.y << std::endl;
        std::cout << "width: " << selectedObject.width << std::endl;
        std::cout << "height: " << selectedObject.height << std::endl;
        std::cout << "cursorPath: " << selectedObject.GetCursorPath() << std::endl;



        // Load a new image based on the selected index, for example
        wxString imagePath = selectedObject.GetCursorPath();
        wxBitmap newImageBitmap(imagePath, wxBITMAP_TYPE_PNG);
        // Create the wxStaticBitmap control and scale the image to 50x50 pixels
        wxImage image = newImageBitmap.ConvertToImage();
        wxImage scaledImage = image.Scale(50, 50);
        wxBitmap scaledBitmap(scaledImage);
        // Set the new image to the wxStaticBitmap control
        m_drawToolsPanel->m_objectImageButton->SetBitmap(scaledBitmap);
        // Refresh the static bitmap to update the displayed image
        m_drawToolsPanel->m_objectImageButton->Refresh();
        // Update wxChoice controls with appropriate values
        // m_objectOnClickChoice->SetSelection(...);
        // m_objectOnHoverChoice->SetSelection(...);
        // m_objectOnUseItemChoice->SetSelection(...);  
  
    }

}

void MainFrame::OnObjectsListSelected(wxCommandEvent &event) {

    std::cout << "we're getting here" << std::endl;
    int selectedIndex = m_drawToolsPanel->m_objectsList->GetSelection();
    if (selectedIndex >= 0 && selectedIndex < m_drawObjectPanel->m_objects.size()) {
        InteractiveObject &selectedObject = m_drawObjectPanel->m_objects[selectedIndex];
        m_drawToolsPanel->m_objectXText->SetValue(wxString::Format("%d", selectedObject.x));
        m_drawToolsPanel->m_objectYText->SetValue(wxString::Format("%d", selectedObject.y));
        m_drawToolsPanel->m_objectWidthText->SetValue(wxString::Format("%d", selectedObject.width));
        m_drawToolsPanel->m_objectHeightText->SetValue(wxString::Format("%d", selectedObject.height));

        std::cout << "x: " << selectedObject.x << std::endl;
        std::cout << "y: " << selectedObject.y << std::endl;
        std::cout << "width: " << selectedObject.width << std::endl;
        std::cout << "height: " << selectedObject.height << std::endl;
        std::cout << "cursorPath: " << selectedObject.GetCursorPath() << std::endl;



        // Load a new image based on the selected index, for example
        wxString imagePath = selectedObject.GetCursorPath();
        wxBitmap newImageBitmap(imagePath, wxBITMAP_TYPE_PNG);
        // Create the wxStaticBitmap control and scale the image to 50x50 pixels
        wxImage image = newImageBitmap.ConvertToImage();
        wxImage scaledImage = image.Scale(50, 50);
        wxBitmap scaledBitmap(scaledImage);
        // Set the new image to the wxStaticBitmap control
        m_drawToolsPanel->m_objectImageButton->SetBitmap(scaledBitmap);
        // Refresh the static bitmap to update the displayed image
        m_drawToolsPanel->m_objectImageButton->Refresh();
        // Update wxChoice controls with appropriate values
        // m_objectOnClickChoice->SetSelection(...);
        // m_objectOnHoverChoice->SetSelection(...);
        // m_objectOnUseItemChoice->SetSelection(...);
    }
}

void MainFrame::OnObjectImageButtonClicked(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open image file"), "", "",
                                 "Image files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg",
                                 wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed their mind

    wxString imagePath = openFileDialog.GetPath();
    wxBitmap imageBitmap(imagePath, wxBITMAP_TYPE_ANY);

    // Scale the image
    wxImage image = imageBitmap.ConvertToImage();
    wxImage scaledImage = image.Scale(50, 50);
    wxBitmap scaledBitmap(scaledImage);

    // Set the scaled bitmap to the wxBitmapButton
    m_drawToolsPanel->m_objectImageButton->SetBitmap(scaledBitmap);



    // Update the interactive object cursorPath
    int selectedIndex = m_drawToolsPanel->m_objectsList->GetSelection();
    if (selectedIndex >= 0 && selectedIndex < m_drawObjectPanel->m_objects.size()) {
        InteractiveObject &selectedObject = m_drawObjectPanel->m_objects[selectedIndex];    
        selectedObject.setCursorPath(imagePath);
    }
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
