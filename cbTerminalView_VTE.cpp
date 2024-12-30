/***************************************************************
 * Name:      cbTerminalView
 * Purpose:   This class implements the panel that is added to
 *            Code::Blocks Message notebook or C::B layout.
 * Author:    Jerome ANTOINE
 * Created:   2007-10-08
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/

#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/display.h>
#include <wx/statline.h>
#ifndef CB_PRECOMP
    #include <wx/combobox.h>
    #include <wx/menu.h>
    #include <wx/sizer.h>
    #include <wx/splitter.h>
    #include <wx/statbox.h>
    #include <wx/stattext.h>
    #include <wx/settings.h>
    #include <wx/toolbar.h>
#endif

#include "cbTerminal.hpp"
#include "cbTerminalView.hpp"
#include <wx/nativewin.h>
#include <vte/vte.h>

class VteNativeWindow : public wxNativeWindow
{
public:
    VteNativeWindow(wxWindow* parent, wxWindowID winid, VteTerminal* vteTerminal) :
        wxNativeWindow(parent, winid, GTK_WIDGET(vteTerminal))
        , m_vteTerminal(vteTerminal)
    {
        g_signal_connect(GTK_WIDGET(vteTerminal), "button-press-event",
                         G_CALLBACK (handleButtonPressEvent), this);
    }

private:
    static gboolean handleButtonPressEvent(GtkWidget *widget,
                                           GdkEventButton *event, VteNativeWindow *vteNativeWindow)
    {
        fprintf(stderr, "%s:%d event->button %d event->type %d\n", __FUNCTION__, __LINE__, event->button, event->type);
        if (event->button == 3)
        {
            if (GTK_WIDGET_CLASS(VTE_TERMINAL_GET_CLASS(widget))->
                    button_press_event(widget, event))
            {
                abort();
                return TRUE;
            }
            if (event->type == GDK_BUTTON_PRESS)
            {
                vteNativeWindow->OnRightMouseDown();
            }
        }
        return FALSE;
    }

    void OnRightMouseDown()
    {
        wxPoint pos = ScreenToClient(wxGetMousePosition());
        wxMenu menu;
        menu.Append(wxID_COPY, "Copy\tc");
        menu.Append(wxID_PASTE, "Paste\tp");

        menu.Bind(wxEVT_MENU, &VteNativeWindow::OnCopy, this, wxID_COPY);
        menu.Bind(wxEVT_MENU, &VteNativeWindow::OnPaste, this, wxID_PASTE);

        PopupMenu(&menu, pos);
    }

    void OnCopy(wxCommandEvent& event)
    {
        vte_terminal_copy_clipboard_format(m_vteTerminal, VTE_FORMAT_TEXT);
    }

    void OnPaste(wxCommandEvent& event)
    {
        vte_terminal_paste_clipboard(m_vteTerminal);
    }

    VteTerminal *m_vteTerminal;
};

cbTerminalView::cbTerminalView(cbTerminal& terminalPlugin) :
    wxPanel(Manager::Get()->GetAppWindow()),
    m_cbTerminalPlugin(terminalPlugin)
{
    VteTerminal* vteTerminal = VTE_TERMINAL(vte_terminal_new());
    if (!vteTerminal)
    {
        fprintf(stderr, "Could not create VTE terminal\n");
        return;
    }
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    char* bash_args[] = { "/bin/bash", NULL }; //NOLINT
#if 0 //FIXME for async, codeblocks hangs on startup.
    vte_terminal_spawn_async(m_vte, VTE_PTY_DEFAULT, NULL, bash_args, NULL,
                             (GSpawnFlags)0, NULL, NULL, NULL, -1, NULL, NULL, NULL);
#else
     vte_terminal_spawn_sync(vteTerminal, VTE_PTY_DEFAULT, NULL, bash_args, NULL,  //NOLINT
                             (GSpawnFlags)0, NULL, NULL, NULL, NULL, NULL );
#endif
    wxNativeWindow* nativeWindow = new VteNativeWindow(this, wxID_ANY, vteTerminal);
    sizer->Add(nativeWindow, 1, wxEXPAND);
    SetSizer(sizer);
}

cbTerminalView::~cbTerminalView() = default;
