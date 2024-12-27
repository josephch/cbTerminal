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


#include <sdk.h> // Code::Blocks SDK
#ifndef CB_PRECOMP
    #include "configmanager.h"
    #include "manager.h"
#endif

#include "cbTerminalView.hpp"
#include "cbTerminalViewManagerMessagesNotebook.hpp"


cbTerminalViewManagerMessagesNotebook::~cbTerminalViewManagerMessagesNotebook()
{
    delete m_Bitmap;
}


void cbTerminalViewManagerMessagesNotebook::AddViewToManager()
{
    if ( m_IsManaged == false )
    {
        // Creates log image
        wxString prefix(ConfigManager::GetDataFolder()+"/resources.zip#zip:/images/");
#if wxCHECK_VERSION(3, 1, 6)
        m_Bitmap = new wxBitmapBundle(cbLoadBitmapBundleFromSVG(prefix+"svg/findf.svg", wxSize(16, 16)));
#else
        const int uiSize = Manager::Get()->GetImageSize(Manager::UIComponent::InfoPaneNotebooks);
        prefix << wxString::Format("%dx%d/", uiSize, uiSize);
        m_Bitmap = new wxBitmap(cbLoadBitmap(prefix+"findf.png", wxBITMAP_TYPE_PNG));
#endif

        // Adds log to C::B Messages notebook
        CodeBlocksLogEvent evtShow(cbEVT_ADD_LOG_WINDOW, m_pcbTerminalView,
                                   wxString(_T("Terminal")), m_Bitmap);
        Manager::Get()->ProcessEvent(evtShow);

        CodeBlocksLogEvent evtSwitch(cbEVT_SWITCH_TO_LOG_WINDOW, m_pcbTerminalView);
        Manager::Get()->ProcessEvent(evtSwitch);

        // Status update
        m_IsManaged = true;
        m_IsShown   = true;
    }
}

void cbTerminalViewManagerMessagesNotebook::RemoveViewFromManager()
{
    if ( m_IsManaged == true )
    {
        // Status update
        m_IsManaged = false;
        m_IsShown   = false;

        // Removes cbTerminal panel from C::B Messages notebook
        // Reparent call to avoid m_pcbTerminalView deletion
        CodeBlocksLogEvent evt(cbEVT_REMOVE_LOG_WINDOW, m_pcbTerminalView);
        Manager::Get()->ProcessEvent(evt);
        m_pcbTerminalView = nullptr;
        delete m_Bitmap;
        m_Bitmap = nullptr;
    }
}


bool cbTerminalViewManagerMessagesNotebook::ShowView(uint32_t flags)
{
    // m_IsManaged is updated in called methods
    const bool show = ((flags & ShowViewFlags::Show) == ShowViewFlags::Show);
    if (show)
    {
        if (m_IsManaged == true)
        {
            wxWindow *focused = nullptr;
            if ((flags & ShowViewFlags::PreserveFocus) == ShowViewFlags::PreserveFocus)
                focused = wxWindow::FindFocus();
            CodeBlocksLogEvent evtShow(cbEVT_SHOW_LOG_MANAGER);
            Manager::Get()->ProcessEvent(evtShow);
            CodeBlocksLogEvent evtSwitch(cbEVT_SWITCH_TO_LOG_WINDOW, m_pcbTerminalView);
            Manager::Get()->ProcessEvent(evtSwitch);
            m_IsShown = true;

            if (focused)
                focused->SetFocus();
        }
        else
        {
            AddViewToManager();
        }
    }
    else
    {
        RemoveViewFromManager();
    }

    return true;
}


bool cbTerminalViewManagerMessagesNotebook::IsViewShown()
{
    return m_IsShown && IsWindowReallyShown((wxWindow*)m_pcbTerminalView);
}


void cbTerminalViewManagerMessagesNotebook::Raise()
{
    m_pcbTerminalView->GetParent()->GetParent()->Raise();
}
