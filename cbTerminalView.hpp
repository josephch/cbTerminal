/***************************************************************
 * Name:      cbTerminalView
 * Purpose:   This class implements the panel that is added to
 *            Code::Blocks Message notebook or layout.
 * Author:    Jerome ANTOINE
 * Created:   2007-10-08
 * Copyright: Jerome ANTOINE
 * Copyright: Christo Joseph
 * License:   GPL
 **************************************************************/

#ifndef CB_TERMINAL_VIEW_H
#define CB_TERMINAL_VIEW_H

#include <wx/panel.h>
#include <vte/vte.h>

class cbTerminal;
class cbTerminalView: public wxPanel {

private:
    friend class cbTerminal;
    cbTerminal&       m_cbTerminalPlugin;
    VteTerminal* m_vte;
public:
    cbTerminalView(cbTerminal& );
    ~cbTerminalView();
};
#endif // CB_TERMINAL_VIEW_H
