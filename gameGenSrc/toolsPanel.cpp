#include "toolsPanel.h"

DrawToolsPanel::DrawToolsPanel(wxWindow* parent,
        std::function<void(wxCommandEvent &event)> OnDrawObjectsToggle,
        std::function<void(wxCommandEvent &event)> OnSaveButtonClick,
        std::function<void(wxCommandEvent &event)> OnLoadButtonClick,
        std::function<void(wxCommandEvent &event)> OnEditToggle,
        std::function<void(wxCommandEvent &event)> OnObjectsListSelected,
        std::function<void(wxCommandEvent &event)> OnObjectImageButtonClicked
        )
    : wxPanel(parent), OnDrawObjectsToggle(OnDrawObjectsToggle), OnSaveButtonClick(OnSaveButtonClick),
      OnLoadButtonClick(OnLoadButtonClick), OnEditToggle(OnEditToggle), OnObjectsListSelected(OnObjectsListSelected),
      OnObjectImageButtonClicked(OnObjectImageButtonClicked) {


    wxBoxSizer *toolsSizer = new wxBoxSizer(wxVERTICAL);
    toolsSizer->Add(new wxStaticText(this, wxID_ANY, "View Creation"), 0, wxALL, 5);

    wxBoxSizer *saveLoadHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton *saveButton = new wxButton(this, wxID_ANY, "Save");
    saveLoadHorizontalSizer->Add(saveButton, 0, wxALL, 10);
    wxButton *loadButton = new wxButton(this, wxID_ANY, "Load");
    saveLoadHorizontalSizer->Add(loadButton, 0, wxALL, 10);
    toolsSizer->Add(saveLoadHorizontalSizer, 0, wxALL, 10);
    

    wxBoxSizer *drawEditHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    drawObjectsButton = new wxToggleButton(this, wxID_ANY, "Draw Objects");
    drawEditHorizontalSizer->Add(drawObjectsButton, 0, wxALL, 10);
    editToggleButton = new wxToggleButton(this, ID_EDIT_TOGGLE, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0);
    drawEditHorizontalSizer->Add(editToggleButton, 0, wxALL, 10);
    toolsSizer->Add(drawEditHorizontalSizer, 0, wxALL, 10);

    
    m_objectsList = new wxChoice(this, ID_OBJECTS_LIST);
    toolsSizer->Add(m_objectsList, 0, wxALL, 5);




    wxBoxSizer *objectDetailsSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *xyHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    m_objectXText = new wxTextCtrl(this, ID_OBJECT_X_TEXT, "", wxDefaultPosition, wxSize(40, -1), 0);
    xyHorizontalSizer->Add(new wxStaticText(this, wxID_ANY, "X:"), 0, wxALL, 5);
    xyHorizontalSizer->Add(m_objectXText, 0, wxALL, 5);
    m_objectYText = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(40, -1), 0);
    xyHorizontalSizer->Add(new wxStaticText(this, wxID_ANY, "Y:"), 0, wxALL, 5);
    xyHorizontalSizer->Add(m_objectYText, 0, wxALL, 5);
    objectDetailsSizer->Add(xyHorizontalSizer, 0, wxALL, 5);

    wxBoxSizer *whHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    m_objectWidthText = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(40, -1), 0);
    whHorizontalSizer->Add(new wxStaticText(this, wxID_ANY, "Width:"), 0, wxALL, 5);
    whHorizontalSizer->Add(m_objectWidthText, 0, wxALL, 5);
    m_objectHeightText = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(40, -1), 0);
    whHorizontalSizer->Add(new wxStaticText(this, wxID_ANY, "Height:"), 0, wxALL, 5);
    whHorizontalSizer->Add(m_objectHeightText, 0, wxALL, 5);
    objectDetailsSizer->Add(whHorizontalSizer, 0, wxALL, 5);

    objectDetailsSizer->Add(new wxStaticText(this, wxID_ANY, "Cursor Image:"), 0, wxALL, 5);
   
   

//TODO: need bad path handler
// Load the image using wxBitmap
wxBitmap imageBitmap("../assets/sprites/magnifying_glass.png", wxBITMAP_TYPE_PNG);

// Create the wxStaticBitmap control and scale the image to 50x50 pixels
wxImage image = imageBitmap.ConvertToImage();
wxImage scaledImage = image.Scale(50, 50);
wxBitmap scaledBitmap(scaledImage);
    m_objectImageButton = new wxBitmapButton(this, ID_OBJECT_IMAGE_BUTTON, scaledBitmap, wxDefaultPosition, wxDefaultSize, 0);


   
    objectDetailsSizer->Add(m_objectImageButton, 0, wxALL, 5);

    m_objectOnClickChoice = new wxChoice(this, wxID_ANY);
    objectDetailsSizer->Add(new wxStaticText(this, wxID_ANY, "OnClick:"), 0, wxALL, 5);
    objectDetailsSizer->Add(m_objectOnClickChoice, 0, wxALL, 5);

    m_objectOnHoverChoice = new wxChoice(this, wxID_ANY);
    objectDetailsSizer->Add(new wxStaticText(this, wxID_ANY, "OnHover:"), 0, wxALL, 5);
    objectDetailsSizer->Add(m_objectOnHoverChoice, 0, wxALL, 5);

    m_objectOnUseItemChoice = new wxChoice(this, wxID_ANY);
    objectDetailsSizer->Add(new wxStaticText(this, wxID_ANY, "OnUseItem:"), 0, wxALL, 5);
    objectDetailsSizer->Add(m_objectOnUseItemChoice, 0, wxALL, 5);

    toolsSizer->Add(objectDetailsSizer, 0, wxALL, 5);
    
    this->SetSizer(toolsSizer);

    Bind(wxEVT_TOGGLEBUTTON, [OnDrawObjectsToggle](wxCommandEvent &event) { OnDrawObjectsToggle(event); }, drawObjectsButton->GetId());
    Bind(wxEVT_BUTTON, [OnSaveButtonClick](wxCommandEvent &event) { OnSaveButtonClick(event); }, saveButton->GetId());
    Bind(wxEVT_BUTTON, [OnLoadButtonClick](wxCommandEvent &event) { OnLoadButtonClick(event); }, loadButton->GetId());
    Bind(wxEVT_TOGGLEBUTTON, [OnEditToggle](wxCommandEvent &event) { OnEditToggle(event); }, editToggleButton->GetId());
    

    Bind(wxEVT_CHOICE, &DrawToolsPanel::ughTest, this, ID_OBJECTS_LIST);
    // Bind(wxEVT_CHOICE, [OnObjectsListSelected](wxCommandEvent &event) { OnObjectsListSelected(event); }, this, ID_OBJECTS_LIST);

    // OnObjectsListSelected
    Bind(wxEVT_BUTTON, &DrawToolsPanel::ugthest, this, ID_OBJECT_IMAGE_BUTTON);


}

void DrawToolsPanel::ughTest(wxCommandEvent &event) {
    std::cout << "this is working" << std::endl;
    OnObjectsListSelected(event);
}

void DrawToolsPanel::ugthest(wxCommandEvent& event)
{
    OnObjectImageButtonClicked(event);
}

