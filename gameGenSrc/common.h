#ifndef COMMON_GAME_GEN_H_
#define COMMON_GAME_GEN_H_

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/tglbtn.h>
#include <wx/xml/xml.h>
#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>


enum {
    ID_DRAW_SQUARE_TOGGLE = 1,
    ID_SAVE_BTN,
    ID_LOAD_BTN,
    ID_EDIT_TOGGLE,
    ID_OBJECTS_LIST,
    ID_OBJECT_X_TEXT,
    ID_OBJECT_IMAGE_BUTTON
};

class MainFrame;

class CustomBufferedPaintDC : public wxPaintDC {
public:
    CustomBufferedPaintDC(wxWindow* window)
        : wxPaintDC(window), m_buffer(window->GetSize()) {
        m_bufferDC.SelectObject(m_buffer);
        DoDraw(window->GetSize());
    }

    ~CustomBufferedPaintDC() {
        Blit(0, 0, m_buffer.GetSize().GetWidth(), m_buffer.GetSize().GetHeight(), &m_bufferDC, 0, 0);
    }

    wxDC& GetBufferDC() { return m_bufferDC; }

private:
    void DoDraw(const wxSize& size) {
        m_buffer.Create(size);
        m_bufferDC.SelectObject(m_buffer);
    }

    wxBitmap m_buffer;
    wxMemoryDC m_bufferDC;
};

#endif