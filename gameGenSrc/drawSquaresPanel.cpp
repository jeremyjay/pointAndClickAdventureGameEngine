#include "drawSquaresPanel.h"




void DrawSquarePanel::EnableDrawSquares(bool enable) 
{
    m_drawSquaresEnabled = enable;
}

void DrawSquarePanel::EnableEditSquares(bool enable)
{
    m_editSquaresEnabled = enable;
}

void DrawSquarePanel::AssignImageToSelectedSquare(const wxString &imagePath)
{
    if (m_selectedSquare) {
        // Add code here to assign an image to the selected square
        // You may need to modify the data structure used to store squares to store image information as well
    }
}

std::vector<wxRect> DrawSquarePanel::GetSquares()
{
    return m_squares;
}

void DrawSquarePanel::DeleteSelectedSquare()
{
    if (m_selectedSquare) {
        m_squares.erase(std::remove(m_squares.begin(), m_squares.end(), *m_selectedSquare), m_squares.end());
        m_selectedSquare = nullptr;
        Refresh();
    }
}

void DrawSquarePanel::LoadBackgroundImage(const wxString &path)
{
    wxImage image;
    if (!image.LoadFile(path, wxBITMAP_TYPE_PNG))
    {
        wxLogError("Failed to load image from file %s", path);
    }
    else
    {
        // Get the size of the panel
        wxSize panelSize = GetClientSize();

        // Scale the image to fit the panel
        image = image.Scale(panelSize.GetWidth(), panelSize.GetHeight(), wxIMAGE_QUALITY_HIGH);

        // Convert the wxImage to wxBitmap
        m_backgroundBitmap = wxBitmap(image);

        // Refresh the panel to show the loaded and scaled image
        Refresh();
    }
}


DrawSquarePanel::DrawSquarePanel(wxWindow* parent, std::function<void(void)> OnUpdateSquaresList)
    : wxPanel(parent), m_drawSquaresEnabled(false), m_editSquaresEnabled(false),
      m_drawingSquare(false), m_draggingSquare(false), m_selectedSquare(nullptr),
      OnUpdateSquaresList(OnUpdateSquaresList) {
    
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, &DrawSquarePanel::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawSquarePanel::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawSquarePanel::OnLeftUp, this);
    Bind(wxEVT_MOTION, &DrawSquarePanel::OnMouseMove, this);
    Bind(wxEVT_SIZE, &DrawSquarePanel::OnSize, this);
}

void DrawSquarePanel::OnPaint(wxPaintEvent& event) {
    CustomBufferedPaintDC dc(this);
    wxDC& bufferDC = dc.GetBufferDC();
    bufferDC.Clear();

    // Draw the background image
    // This section is not matching
    bufferDC.DrawBitmap(m_backgroundBitmap, 0, 0, true);
  
    // if (m_backgroundBitmap.IsOk()) {
    //     dc.DrawBitmap(m_backgroundBitmap, 0, 0, true);
    // }
    // else {
    //     dc.SetBackground(*wxWHITE_BRUSH);
    //     dc.Clear();
    // }



    for (const wxRect &rect : m_squares) {
        DrawSquare(bufferDC, rect);
    }

    if (m_drawingSquare) {
        wxRect rect(m_startPoint, m_endPoint);
        DrawSquare(bufferDC, rect);
    }
    
}

void DrawSquarePanel::DrawSquare(wxDC &dc, const wxRect &rect)
{
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(rect);
}



wxRect *DrawSquarePanel::GetSquareAtPoint(const wxPoint &point)
{
    for (auto &rect : m_squares) {
        if (rect.Contains(point)) {
            return &rect;
        }
    }
    return nullptr;
}

void DrawSquarePanel::OnLeftDown(wxMouseEvent& event) {
    if (m_drawSquaresEnabled) {
        m_drawingSquare = true;
        m_startPoint = event.GetPosition();
        m_endPoint = m_startPoint;
    } else if (m_editSquaresEnabled) {
        m_selectedSquare = GetSquareAtPoint(event.GetPosition());
        if (m_selectedSquare) {
            m_draggingSquare = true;
            m_startPoint = event.GetPosition();
        }
    }
}

void DrawSquarePanel::OnLeftUp(wxMouseEvent& event) {
    if (m_drawingSquare) {
        m_endPoint = event.GetPosition();
        wxRect rect(m_startPoint, m_endPoint);
        m_squares.push_back(rect);
        m_drawingSquare = false;
        Refresh();
        if (OnUpdateSquaresList)
        {
            OnUpdateSquaresList();
        }
    } else if (m_draggingSquare) {
        m_draggingSquare = false;
    }
}

void DrawSquarePanel::OnMouseMove(wxMouseEvent& event) 
{
    if (m_drawingSquare) {
        m_endPoint = event.GetPosition();
        Refresh();
    } else if (m_draggingSquare && m_selectedSquare) {
        wxPoint delta = event.GetPosition() - m_startPoint;
        m_startPoint = event.GetPosition();
        m_selectedSquare->Offset(delta);
        Refresh();
    }
}

void DrawSquarePanel::OnSize(wxSizeEvent &event)
{
    wxSize panelSize = GetSize();

    // Only load and scale the image if the panel size is valid
    if (panelSize.GetWidth() > 0 && panelSize.GetHeight() > 0) {
        //TODO: Add error checking here!!
        LoadBackgroundImage("../assets/rooms/couch.png");
    }

    event.Skip();
}


void DrawSquarePanel::SaveSquaresToXML(const wxString &path) {
    wxXmlDocument doc;
    wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, "squares");
    doc.SetRoot(root);

    for (const auto &square : m_squares) {
        wxXmlNode *squareNode = new wxXmlNode(wxXML_ELEMENT_NODE, "square");

        squareNode->AddAttribute("x", wxString::Format("%d", square.x));
        squareNode->AddAttribute("y", wxString::Format("%d", square.y));
        squareNode->AddAttribute("width", wxString::Format("%d", square.width));
        squareNode->AddAttribute("height", wxString::Format("%d", square.height));

        root->AddChild(squareNode);
    }

    if (!doc.Save(path)) {
        wxMessageBox("Failed to save the XML file.", "Error", wxICON_ERROR | wxOK);
    } else {
        wxMessageBox("XML file saved successfully.", "Success", wxICON_INFORMATION | wxOK);
    }
}

void DrawSquarePanel::LoadSquaresFromXML(const wxString &path) {
    wxXmlDocument doc;

    if (!doc.Load(path)) {
        wxMessageBox("Failed to load the XML file.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    wxXmlNode *root = doc.GetRoot();
    if (root->GetName() != "squares") {
        wxMessageBox("Invalid XML file format.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    m_squares.clear();
    wxXmlNode *squareNode = root->GetChildren();
    while (squareNode) {
        if (squareNode->GetName() == "square") {
            int x = wxAtoi(squareNode->GetAttribute("x", "0"));
            int y = wxAtoi(squareNode->GetAttribute("y", "0"));
            int width = wxAtoi(squareNode->GetAttribute("width", "0"));
            int height = wxAtoi(squareNode->GetAttribute("height", "0"));

            m_squares.push_back(wxRect(x, y, width, height));
            if (OnUpdateSquaresList)
            {
                OnUpdateSquaresList();
            }
        }
        squareNode = squareNode->GetNext();
    }

    Refresh();
}