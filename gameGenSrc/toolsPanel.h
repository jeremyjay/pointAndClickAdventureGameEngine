#ifndef TOOLS_PANEL_H_
#define TOOLS_PANEL_H_

#include "common.h"
#include <functional>
#include "interactiveObject.h"

class DrawToolsPanel : public wxPanel {
public:
    DrawToolsPanel(wxWindow* parent,
        std::function<void(wxCommandEvent &event)> OnDrawObjectsToggle,
        std::function<void(wxCommandEvent &event)> OnSaveButtonClick,
        std::function<void(wxCommandEvent &event)> OnLoadButtonClick,
        std::function<void(wxCommandEvent &event)> OnEditToggle,
        std::function<void(wxCommandEvent &event)> OnObectsListSelected,
        std::function<void(wxCommandEvent &event)> OnObjectImageButtonClicked
    );

    wxToggleButton *editToggleButton;
    wxToggleButton *drawObjectsButton;
    wxChoice *m_objectsList;
    wxBitmapButton* m_objectImageButton;
    wxBoxSizer *objectDetailsSizer;
    wxBoxSizer *xyHorizontalSizer;
    wxBoxSizer *whHorizontalSizer;
    wxBoxSizer *onClickSizer;
    wxBoxSizer *onHoverSizer;
    wxBoxSizer *onUseItemSizer;

    InteractiveObject * m_selectedObject = nullptr;


void ughTest(wxCommandEvent &event);
void ugthest(wxCommandEvent &event);
void UpdateObjectDetailsVisibility();

void OnAddButtonClick(wxCommandEvent &event, wxChoice *choiceCtrl);
void OnDeleteButtonClick(wxCommandEvent &event, wxChoice *choiceCtrl);

std::vector<std::string>& GetActionsForType(wxChoice* targetChoice);


    //maybe move to private
    wxTextCtrl *m_objectXText;
    wxTextCtrl *m_objectYText;
    wxTextCtrl *m_objectWidthText;
    wxTextCtrl *m_objectHeightText;
    wxChoice *m_objectOnClickChoice;
    wxChoice *m_objectOnHoverChoice;
    wxChoice *m_objectOnUseItemChoice;

private:


    std::function<void(wxCommandEvent &event)> OnDrawObjectsToggle;
    std::function<void(wxCommandEvent &event)> OnSaveButtonClick;
    std::function<void(wxCommandEvent &event)> OnLoadButtonClick;
    std::function<void(wxCommandEvent &event)> OnEditToggle;
    std::function<void(wxCommandEvent &event)> OnObjectsListSelected;
    std::function<void(wxCommandEvent &event)> OnObjectImageButtonClicked;

};


#endif
