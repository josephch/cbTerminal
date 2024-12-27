/***************************************************************
 * Name:      cbTerminalViewManagerLayout
 * Purpose:   Implements the cbTerminalViewManagerBase
 *            interface to make the cbTerminalView panel
 *            managed by the layout.
 * Author:    Jerome ANTOINE
 * Created:   2007-07-19
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/


#include <sdk.h> // Code::Blocks SDK
#ifndef CB_PRECOMP
    #include "globals.h"
    #include "manager.h"
    #include "sdk_events.h"
#endif

#include "cbTerminalViewManagerLayout.hpp"
#include "cbTerminalView.hpp"

cbTerminalViewManagerLayout::~cbTerminalViewManagerLayout()
{
}

void cbTerminalViewManagerLayout::AddViewToManager()
{
    if ( m_IsManaged == false )
    {
        // Docking event creation
        CodeBlocksDockEvent evt(cbEVT_ADD_DOCK_WINDOW);
        evt.name = _T("cbTerminal");
        evt.title = _("Terminal");
        evt.pWindow = (wxWindow*)m_pcbTerminalView;
        evt.desiredSize.Set(800, 200);
        evt.floatingSize.Set(600, 200);
        evt.minimumSize.Set( 30, 40 );
        evt.stretch = true;
        evt.dockSide = CodeBlocksDockEvent::dsBottom;
        evt.shown = true;

        // Adds view to layout manager
        Manager::Get()->ProcessEvent(evt);

        m_IsManaged = true;
        m_IsShown   = true;
    }
}

void cbTerminalViewManagerLayout::RemoveViewFromManager()
{
    if ( m_IsManaged == true )
    {
        // Undocking event creation
        CodeBlocksDockEvent evt(cbEVT_REMOVE_DOCK_WINDOW);
        evt.pWindow = (wxWindow*)m_pcbTerminalView;
        evt.shown = false;

        // Removes view from layout manager
        Manager::Get()->ProcessEvent(evt);

        m_IsManaged = false;
        m_IsShown   = false;

        // We need to delete this to make it behave like the notebook.
        delete m_pcbTerminalView;
        m_pcbTerminalView = nullptr;
    }
}


bool cbTerminalViewManagerLayout::ShowView(uint32_t flags)
{
    const bool show = ((flags & ShowViewFlags::Show) == ShowViewFlags::Show);
    if ((m_IsManaged == false) || (show == IsViewShown()))
        return false;

    wxWindow *focused = nullptr;
    if ((flags & ShowViewFlags::PreserveFocus) == ShowViewFlags::PreserveFocus)
        focused = wxWindow::FindFocus();

    CodeBlocksDockEvent evt(show ? cbEVT_SHOW_DOCK_WINDOW : cbEVT_HIDE_DOCK_WINDOW);
    evt.pWindow = (wxWindow*)m_pcbTerminalView;
    evt.shown = show;
    Manager::Get()->ProcessEvent(evt);

    if (focused)
        focused->SetFocus();

    m_IsShown = show;

    return true;
}


bool cbTerminalViewManagerLayout::IsViewShown()
{
    // m_IsShown is not sufficient because user can close the view with the close cross
    // so we use IsWindowReallyShown to give correct result.
    return m_IsShown && IsWindowReallyShown((wxWindow*)m_pcbTerminalView);
}


void cbTerminalViewManagerLayout::Raise()
{
    m_pcbTerminalView->GetParent()->Raise();
}
