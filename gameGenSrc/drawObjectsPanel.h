#ifndef DRAW_SQUARES_PANEL_H_
#define DRAW_SQUARES_PANEL_H_

#include "common.h"
#include "interactiveObject.h"

class DrawObjectPanel : public wxPanel {
public:
    DrawObjectPanel(wxWindow* parent, std::function<void()> OnUpdateObjectsList, std::function<void(int)> OnObjectClicked);

    void EnableDrawObjects(bool enable);
    void SaveObjectsToXML(const wxString &path);
    void LoadObjectsFromXML(const wxString &path);
    void LoadBackgroundImage(const wxString &path);

    void EnableEditObjects(bool enable);
    void DeleteSelectedObject();
    void AssignImageToSelectedObject(const wxString &imagePath);

    std::vector<InteractiveObject> GetObjects();
    // std::vector<wxRect> GetObjects();

    std::vector<InteractiveObject> m_objects;


private:
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnSize(wxSizeEvent &event);

    
    void DrawObject(wxDC &dc, const wxRect &rect);
    wxRect *GetObjectAtPoint(const wxPoint &point);

    void OnMouseMotion(wxMouseEvent &event);



    wxBitmap m_backgroundBitmap;
    
    bool m_drawObjectsEnabled;
    bool m_editObjectsEnabled;
    bool m_drawingObject;
    bool m_draggingObject;
    wxPoint m_startPoint;
    wxPoint m_endPoint;

    wxRect *m_selectedObject;

    std::function<void()> OnUpdateObjectsList;
    std::function<void(int)> OnObjectClicked;

};

#endif
