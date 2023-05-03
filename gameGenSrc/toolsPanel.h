#ifndef TOOLS_PANEL_H_
#define TOOLS_PANEL_H_

#include "common.h"
#include <functional>

class DrawToolsPanel : public wxPanel {
public:
    DrawToolsPanel(wxWindow* parent,
        std::function<void(wxCommandEvent &event)> OnDrawObjectsToggle,
        std::function<void(wxCommandEvent &event)> OnSaveButtonClick,
        std::function<void(wxCommandEvent &event)> OnLoadButtonClick,
        std::function<void(wxCommandEvent &event)> OnEditToggle
    );

    wxToggleButton *editToggleButton;
    wxToggleButton *drawObjectsButton;
    wxChoice *m_objectsList;

private:


    std::function<void(wxCommandEvent &event)> OnDrawObjectsToggle;
    std::function<void(wxCommandEvent &event)> OnSaveButtonClick;
    std::function<void(wxCommandEvent &event)> OnLoadButtonClick;
    std::function<void(wxCommandEvent &event)> OnEditToggle;

};


#endif
