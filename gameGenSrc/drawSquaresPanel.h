#ifndef DRAW_SQUARES_PANEL_H_
#define DRAW_SQUARES_PANEL_H_

#include "common.h"

class DrawSquarePanel : public wxPanel {
public:
    DrawSquarePanel(wxWindow* parent, std::function<void()> OnUpdateSquaresList);

    void EnableDrawSquares(bool enable);
    void SaveSquaresToXML(const wxString &path);
    void LoadSquaresFromXML(const wxString &path);
    void LoadBackgroundImage(const wxString &path);

    void EnableEditSquares(bool enable);
    void DeleteSelectedSquare();
    void AssignImageToSelectedSquare(const wxString &imagePath);
    std::vector<wxRect> GetSquares();



private:
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnSize(wxSizeEvent &event);

    
    void DrawSquare(wxDC &dc, const wxRect &rect);
    wxRect *GetSquareAtPoint(const wxPoint &point);

    std::vector<wxRect> m_squares;
    wxBitmap m_backgroundBitmap;
    
    bool m_drawSquaresEnabled;
    bool m_editSquaresEnabled;
    bool m_drawingSquare;
    bool m_draggingSquare;
    wxPoint m_startPoint;
    wxPoint m_endPoint;

    wxRect *m_selectedSquare;

    std::function<void()> OnUpdateSquaresList;

};

#endif
