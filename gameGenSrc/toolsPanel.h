#ifndef TOOLS_PANEL_H_
#define TOOLS_PANEL_H_

#include "common.h"
#include <functional>

class DrawToolsPanel : public wxPanel {
public:
    DrawToolsPanel(wxWindow* parent,
        std::function<void(wxCommandEvent &event)> OnDrawSquaresToggle,
        std::function<void(wxCommandEvent &event)> OnSaveButtonClick,
        std::function<void(wxCommandEvent &event)> OnLoadButtonClick,
        std::function<void(wxCommandEvent &event)> OnEditToggle
    );

    wxToggleButton *editToggleButton;
    wxToggleButton *drawSquaresButton;
    wxChoice *m_squaresList;

private:


    std::function<void(wxCommandEvent &event)> OnDrawSquaresToggle;
    std::function<void(wxCommandEvent &event)> OnSaveButtonClick;
    std::function<void(wxCommandEvent &event)> OnLoadButtonClick;
    std::function<void(wxCommandEvent &event)> OnEditToggle;

};


#endif
