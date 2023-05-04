#include "drawObjectsPanel.h"




void DrawObjectPanel::EnableDrawObjects(bool enable) 
{
    m_drawObjectsEnabled = enable;
}

void DrawObjectPanel::EnableEditObjects(bool enable)
{
    m_editObjectsEnabled = enable;
}

void DrawObjectPanel::AssignImageToSelectedObject(const wxString &imagePath)
{
    if (m_selectedObject) {
        // Add code here to assign an image to the selected object
        // You may need to modify the data structure used to store objects to store image information as well
    }
}

std::vector<InteractiveObject> DrawObjectPanel::GetObjects()
{
    return m_objects;
}

void DrawObjectPanel::DeleteSelectedObject()
{
    if (m_selectedObject) {
        m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), *m_selectedObject), m_objects.end());
        m_selectedObject = nullptr;
        Refresh();
    }
}

void DrawObjectPanel::LoadBackgroundImage(const wxString &path)
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


DrawObjectPanel::DrawObjectPanel(wxWindow* parent, std::function<void(void)> OnUpdateObjectsList)
    : wxPanel(parent), m_drawObjectsEnabled(false), m_editObjectsEnabled(false),
      m_drawingObject(false), m_draggingObject(false), m_selectedObject(nullptr),
      OnUpdateObjectsList(OnUpdateObjectsList) {
    
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, &DrawObjectPanel::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawObjectPanel::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &DrawObjectPanel::OnLeftUp, this);
    Bind(wxEVT_MOTION, &DrawObjectPanel::OnMouseMove, this);
    Bind(wxEVT_SIZE, &DrawObjectPanel::OnSize, this);

    // In DrawSquarePanel constructor:
    Bind(wxEVT_MOTION, &DrawObjectPanel::OnMouseMotion, this);



}

void DrawObjectPanel::OnPaint(wxPaintEvent& event) {
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



    for (const wxRect &rect : m_objects) {
        DrawObject(bufferDC, rect);
    }

    if (m_drawingObject) {
        wxRect rect(m_startPoint, m_endPoint);
        DrawObject(bufferDC, rect);
    }
    
}

void DrawObjectPanel::DrawObject(wxDC &dc, const wxRect &rect)
{
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(rect);
}



wxRect *DrawObjectPanel::GetObjectAtPoint(const wxPoint &point)
{
    for (auto &rect : m_objects) {
        if (rect.Contains(point)) {
            return &rect;
        }
    }
    return nullptr;
}

void DrawObjectPanel::OnLeftDown(wxMouseEvent& event) {
    if (m_drawObjectsEnabled) {
        m_drawingObject = true;
        m_startPoint = event.GetPosition();
        m_endPoint = m_startPoint;
    } else if (m_editObjectsEnabled) {
        m_selectedObject = GetObjectAtPoint(event.GetPosition());
        if (m_selectedObject) {
            m_draggingObject = true;
            m_startPoint = event.GetPosition();
        }
    }
}

void DrawObjectPanel::OnLeftUp(wxMouseEvent& event) {
    if (m_drawingObject) {
        m_endPoint = event.GetPosition();

        int width = m_endPoint.x - m_startPoint.x;
        int height = m_endPoint.y - m_startPoint.y;

        InteractiveObject objeto(
            1,                           // ID
            "../assets/sprites/magnifying_glass.png",         // Image path
            "../assets/sprites/magnifying_glass.png",         // cursor path
            m_startPoint.x, m_startPoint.y,                      // x, y coordinates
            width, height,                    // Width, height
            0,                           // Cursor ID
            nullptr,              // onClick callback
            nullptr,              // onHover callback
            nullptr             // onUseItem callback
        );

        m_objects.push_back(objeto);
        m_drawingObject = false;
        Refresh();
        if (OnUpdateObjectsList)
        {
            OnUpdateObjectsList();
        }
    } else if (m_draggingObject) {
        m_draggingObject = false;
    }
}

void DrawObjectPanel::OnMouseMove(wxMouseEvent& event) 
{
    if (m_drawingObject) {
        m_endPoint = event.GetPosition();
        Refresh();
    } else if (m_draggingObject && m_selectedObject) {
        wxPoint delta = event.GetPosition() - m_startPoint;
        m_startPoint = event.GetPosition();
        m_selectedObject->Offset(delta);
        Refresh();
    }
}

void DrawObjectPanel::OnSize(wxSizeEvent &event)
{
    wxSize panelSize = GetSize();

    // Only load and scale the image if the panel size is valid
    if (panelSize.GetWidth() > 0 && panelSize.GetHeight() > 0) {
        //TODO: Add error checking here!!
        LoadBackgroundImage("../assets/rooms/couch.png");
    }

    event.Skip();
}


void DrawObjectPanel::SaveObjectsToXML(const wxString &path) {
    wxXmlDocument doc;
    wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, "objects");
    doc.SetRoot(root);

    for (const auto &object : m_objects) {
        wxXmlNode *objectNode = new wxXmlNode(wxXML_ELEMENT_NODE, "object");

        objectNode->AddAttribute("x", wxString::Format("%d", object.x));
        objectNode->AddAttribute("y", wxString::Format("%d", object.y));
        objectNode->AddAttribute("width", wxString::Format("%d", object.width));
        objectNode->AddAttribute("height", wxString::Format("%d", object.height));

        root->AddChild(objectNode);
    }

    if (!doc.Save(path)) {
        wxMessageBox("Failed to save the XML file.", "Error", wxICON_ERROR | wxOK);
    } else {
        wxMessageBox("XML file saved successfully.", "Success", wxICON_INFORMATION | wxOK);
    }
}

void DrawObjectPanel::LoadObjectsFromXML(const wxString &path) {
    wxXmlDocument doc;

    if (!doc.Load(path)) {
        wxMessageBox("Failed to load the XML file.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    wxXmlNode *root = doc.GetRoot();
    if (root->GetName() != "objects") {
        wxMessageBox("Invalid XML file format.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    m_objects.clear();
    wxXmlNode *objectNode = root->GetChildren();
    while (objectNode) {
        if (objectNode->GetName() == "object") {
            int x = wxAtoi(objectNode->GetAttribute("x", "0"));
            int y = wxAtoi(objectNode->GetAttribute("y", "0"));
            int width = wxAtoi(objectNode->GetAttribute("width", "0"));
            int height = wxAtoi(objectNode->GetAttribute("height", "0"));

            // m_objects.push_back(wxRect(x, y, width, height));
            //TODO: use real image path
            m_objects.push_back(InteractiveObject(1, "path/to/image.png", "path/to/image/png", x, y, width, height, 0, nullptr, nullptr, nullptr));
            if (OnUpdateObjectsList)
            {
                OnUpdateObjectsList();
            }
        }
        objectNode = objectNode->GetNext();
    }

    Refresh();
}



// In DrawSquarePanel.cpp, add the following definition:
void DrawObjectPanel::OnMouseMotion(wxMouseEvent &event)
{
    wxPoint mousePosition = event.GetPosition();
    bool isMouseOverObject = false;
    wxString path;

    for (const auto &object : m_objects)
    {
        if (object.Contains(mousePosition))
        {
            isMouseOverObject = true;
            path = object.GetCursorPath();
            break;
        }
    }

    if (isMouseOverObject)
    {


    // In MainFrame constructor:
        // wxImage cursorImage;
        // cursorImage.LoadFile("../assets/sprites/magnifying_glass.png");

        wxImage cursorImage(path);
        cursorImage.Rescale(50, 50, wxIMAGE_QUALITY_HIGH);
        wxCursor m_customCursor = wxCursor(cursorImage);
        SetCursor(m_customCursor);

        // SetCursor(m_mainFrame->m_customCursor);
    }
    else
    {
        SetCursor(wxCursor(wxCURSOR_ARROW));
    }

    event.Skip();
}
