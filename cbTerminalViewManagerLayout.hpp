/***************************************************************
 * Name:      cbTerminalViewManagerLayout
 * Purpose:   Implements the cbTerminalViewManagerBase
 *            interface to make the cbTerminalView panel
 *            managed by the wxAui layout.
 * Author:    Jerome ANTOINE
 * Created:   2007-07-19
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/

#ifndef CB_TERMINAL_VIEW_MANAGER_LAYOUT_H
#define CB_TERMINAL_VIEW_MANAGER_LAYOUT_H

#include "cbTerminalViewManagerBase.hpp"

class cbTerminalViewManagerLayout : public cbTerminalViewManagerBase
{
public:
    cbTerminalViewManagerLayout(cbTerminalView* pcbTerminalView)
        : cbTerminalViewManagerBase(pcbTerminalView)
    {}
    ~cbTerminalViewManagerLayout() override;

    eManagerTypes GetManagerType() override { return TypeLayout; }
    void AddViewToManager() override;
    void RemoveViewFromManager() override;
    bool ShowView(uint32_t flags) override;
    bool IsViewShown() override;
    void Raise() override;
};

#endif // CB_TERMINAL_VIEW_MANAGER_LAYOUT_H
