/***************************************************************
 * Name:      cbTerminal
 * Purpose:   cbTerminal Code::Blocks plugin
 *            Most of the interactions with C::B are handled here.
 * Author:    Jerome ANTOINE
 * Created:   2007-10-08
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/

#include <sdk.h> // Code::Blocks SDK
#ifndef CB_PRECOMP
    #include <wx/combobox.h>
    #include <wx/menu.h>
    #include <wx/toolbar.h>
    #include <wx/xrc/xmlres.h>
#endif

#include "cbTerminal.hpp"
#include "cbTerminalView.hpp"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<cbTerminal> reg(_T("cbTerminal"));
}

// constructor
cbTerminal::cbTerminal()
             :m_pcbTerminalView(nullptr),
              m_pViewManager(nullptr)
{
}

// destructor
cbTerminal::~cbTerminal()
{
}

void cbTerminal::OnAttach()
{
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...

    #if LOGGING
     wxLog::EnableLogging(true);
     m_pLog = new wxLogWindow(Manager::Get()->GetAppWindow(), _T(" cbTerminal Plugin"), true, false);
     wxLog::SetActiveTarget( m_pLog);
     m_pLog->Flush();
     m_pLog->GetFrame()->SetSize(20,30,600,300);
     LOGIT( _T("cbTerminal Plugin Logging Started"));
    #endif
    m_pcbTerminalView = new cbTerminalView(*this);
    m_pViewManager = cbTerminalViewManagerBase::BuildcbTerminalViewManagerBase(m_pcbTerminalView, true, cbTerminalViewManagerBase::TypeMessagesNotebook);
}

void cbTerminal::OnRelease(bool /*appShutDown*/)
{
    if (m_pcbTerminalView != nullptr)
    {
        m_pViewManager->RemoveViewFromManager();
        m_pcbTerminalView = nullptr;
    }

    delete m_pViewManager;
    m_pViewManager = nullptr;
}

