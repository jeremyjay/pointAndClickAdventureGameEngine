#include "toolsPanel.h"

DrawToolsPanel::DrawToolsPanel(wxWindow* parent,
        std::function<void(wxCommandEvent &event)> OnDrawSquaresToggle,
        std::function<void(wxCommandEvent &event)> OnSaveButtonClick,
        std::function<void(wxCommandEvent &event)> OnLoadButtonClick,
        std::function<void(wxCommandEvent &event)> OnEditToggle)
    : wxPanel(parent), OnDrawSquaresToggle(OnDrawSquaresToggle), OnSaveButtonClick(OnSaveButtonClick),
      OnLoadButtonClick(OnLoadButtonClick), OnEditToggle(OnEditToggle) {


    wxBoxSizer *toolsSizer = new wxBoxSizer(wxVERTICAL);
    drawSquaresButton = new wxToggleButton(this, wxID_ANY, "Draw Squares");
    toolsSizer->Add(drawSquaresButton, 0, wxALL, 10);
    wxButton *saveButton = new wxButton(this, wxID_ANY, "Save");
    toolsSizer->Add(saveButton, 0, wxALL, 10);
    wxButton *loadButton = new wxButton(this, wxID_ANY, "Load");
    toolsSizer->Add(loadButton, 0, wxALL, 10);
    editToggleButton = new wxToggleButton(this, ID_EDIT_TOGGLE, wxT("Edit"), wxDefaultPosition, wxDefaultSize, 0);
    toolsSizer->Add(editToggleButton, 0, wxALL, 5);
    m_squaresList = new wxChoice(this, wxID_ANY);
    toolsSizer->Add(m_squaresList, 0, wxALL, 5);

    
    this->SetSizer(toolsSizer);

    Bind(wxEVT_TOGGLEBUTTON, [OnDrawSquaresToggle](wxCommandEvent &event) { OnDrawSquaresToggle(event); }, drawSquaresButton->GetId());
    Bind(wxEVT_BUTTON, [OnSaveButtonClick](wxCommandEvent &event) { OnSaveButtonClick(event); }, saveButton->GetId());
    Bind(wxEVT_BUTTON, [OnLoadButtonClick](wxCommandEvent &event) { OnLoadButtonClick(event); }, loadButton->GetId());
    Bind(wxEVT_TOGGLEBUTTON, [OnEditToggle](wxCommandEvent &event) { OnEditToggle(event); }, editToggleButton->GetId());


}