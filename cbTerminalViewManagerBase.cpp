/***************************************************************
 * Name:      cbTerminalViewManagerBase
 * Purpose:   cbTerminalViewManagerBase is an interface to the
 *            different graphical classes that can manage the view.
 * Author:    Jerome ANTOINE
 * Created:   2007-07-19
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/

#include "cbTerminalViewManagerBase.hpp"
#include "cbTerminalViewManagerMessagesNotebook.hpp"
#include "cbTerminalViewManagerLayout.hpp"

cbTerminalViewManagerBase* cbTerminalViewManagerBase::BuildcbTerminalViewManagerBase(
                                                                            cbTerminalView* pView,
                                                                            bool              addViewToManager,
                                                                            eManagerTypes     managerType)
{
    cbTerminalViewManagerBase* pMgr = 0;

    if ( managerType == TypeMessagesNotebook )
    {
        pMgr = new cbTerminalViewManagerMessagesNotebook(pView);
    }
    else
    {
        // cbTerminalViewManagerLayout is the default view manager
        // No error management on managerType
        pMgr = new cbTerminalViewManagerLayout(pView);
    }
    if ( addViewToManager == true )
    {
        pMgr->AddViewToManager();
    }
    return pMgr;
}
