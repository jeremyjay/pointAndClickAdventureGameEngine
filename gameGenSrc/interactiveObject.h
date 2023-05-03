#include <wx/wx.h>
#include <functional>

class InteractiveObject : public wxRect
{
public:
    using CallbackFunction = std::function<void(InteractiveObject &)>;

    InteractiveObject(int id, const std::string &imagePath, int x, int y, int width, int height,
                      int cursorId, CallbackFunction onClick, CallbackFunction onHover, CallbackFunction onUseItem)
        : wxRect(x, y, width, height),
          m_id(id),
          m_imagePath(imagePath),
          m_cursorId(cursorId),
          m_onClick(onClick),
          m_onHover(onHover),
          m_onUseItem(onUseItem)
    {
    }

    // Accessor methods for the class variables
    int GetId() const { return m_id; }
    const std::string &GetImagePath() const { return m_imagePath; }
    int GetCursorId() const { return m_cursorId; }

    void Click() { m_onClick(*this); }
    void Hover() { m_onHover(*this); }
    void UseItem() { m_onUseItem(*this); }

private:
    int m_id;
    std::string m_imagePath;
    int m_cursorId;
    CallbackFunction m_onClick;
    CallbackFunction m_onHover;
    CallbackFunction m_onUseItem;
};
