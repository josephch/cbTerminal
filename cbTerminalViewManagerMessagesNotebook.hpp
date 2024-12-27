/***************************************************************
 * Name:      cbTerminalViewManagerMessagesNotebook
 * Purpose:   Implements the cbTerminalViewManagerBase
 *            interface to make the cbTerminalView panel
 *            managed by the Messages notebook.
 * Author:    Jerome ANTOINE
 * Created:   2007-07-19
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/


#ifndef CB_TERMINAL_VIEW_MANAGER_MESSAGES_NOTEBOOK_H
#define CB_TERMINAL_VIEW_MANAGER_MESSAGES_NOTEBOOK_H

#include <wx/version.h> 

#include "cbTerminalViewManagerBase.hpp"

class wxBitmap;
#if wxCHECK_VERSION(3, 1, 6)
class wxBitmapBundle;
#endif
class wxWindow;
class cbTerminalView;
class cbTerminalLogger;

class cbTerminalViewManagerMessagesNotebook : public cbTerminalViewManagerBase
{
public:
    cbTerminalViewManagerMessagesNotebook(cbTerminalView* pcbTerminalView)
        : cbTerminalViewManagerBase(pcbTerminalView), m_Bitmap(nullptr)
    {}
    ~cbTerminalViewManagerMessagesNotebook() override;

    eManagerTypes GetManagerType() override { return TypeMessagesNotebook; }
    void AddViewToManager() override;
    void RemoveViewFromManager() override;
    bool ShowView(uint32_t flags) override;
    bool IsViewShown() override;
    void Raise() override;
private:
#if wxCHECK_VERSION(3, 1, 6)
    wxBitmapBundle *m_Bitmap;
#else
    wxBitmap *m_Bitmap;
#endif
};

#endif // CB_TERMINAL_VIEW_MANAGER_MESSAGES_NOTEBOOK_H
