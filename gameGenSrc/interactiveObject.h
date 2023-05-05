#ifndef INTERACTIVE_OBJECT_H_
#define INTERACTIVE_OBJECT_H_


#include <wx/wx.h>
#include <functional>
#include <vector>
#include <string>

class InteractiveObject : public wxRect
{
public:
    using CallbackFunction = std::function<void(InteractiveObject &)>;

    InteractiveObject(int id, const wxString &imagePath, const wxString &cursorPath, int x, int y, int width, int height,
                    int cursorId, CallbackFunction onClick, CallbackFunction onHover, CallbackFunction onUseItem)
        : wxRect(x, y, width, height),
        m_id(id),
        m_imagePath(imagePath),
        m_cursorPath(cursorPath),
        m_cursorId(cursorId),
        m_onClick(onClick),
        m_onHover(onHover),
        m_onUseItem(onUseItem)
    {
    }



    // Accessor methods for the class variables
    int GetId() const { return m_id; }
     wxString &GetImagePath()  { return m_imagePath; }
    const wxString &GetCursorPath() const { return m_cursorPath; }
    void setCursorPath( wxString &path)  { m_cursorPath = path; }
    int GetCursorId() const { return m_cursorId; }

    void Click() { m_onClick(*this); }
    void Hover() { m_onHover(*this); }
    void UseItem() { m_onUseItem(*this); }



    std::vector<std::string> m_onClickActions;
    std::vector<std::string> m_onHoverActions;
    std::vector<std::string> m_onUseItemActions;


private:
    int m_id;
    wxString m_imagePath;
    wxString m_cursorPath;
    int m_cursorId;
    CallbackFunction m_onClick;
    CallbackFunction m_onHover;
    CallbackFunction m_onUseItem;
};

#endif