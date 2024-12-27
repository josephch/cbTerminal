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

#ifndef CB_TERMINAL_H
#define CB_TERMINAL_H

#include <wx/string.h>
#include <wx/splitter.h>

#include <cbplugin.h> // for "class cbPlugin"
#include <globals.h> // for "ModuleType"

#include "cbTerminalViewManagerBase.hpp"

class wxWindow;
class wxMenu;
class wxMenuBar;
class wxToolBar;
class wxLogWindow;
class wxComboBox;
class FileTreeData;
class wxCommandEvent;
class wxUpdateUIEvent;

class cbConfigurationPanel;
class cbProject;

class cbTerminalView;


class cbTerminal : public cbPlugin
{
public:
    /** Constructor. */
    cbTerminal();

    /** Destructor. */
    virtual ~cbTerminal() override;

    /** Return the plugin's configuration priority.
      * This is a number (default is 50) that is used to sort plugins
      * in configuration dialogs. Lower numbers mean the plugin's
      * configuration is put higher in the list.
      */
    virtual int GetConfigurationPriority() const override { return 50; }

    /** Return the configuration group for this plugin. Default is cgUnknown.
      * Notice that you can logically OR more than one configuration groups,
      * so you could set it, for example, as "cgCompiler | cgContribPlugin".
      */
    virtual int GetConfigurationGroup() const override { return cgEditor; }

protected:
    /** Any descendent plugin should override this virtual method and
      * perform any necessary initialization. This method is called by
      * Code::Blocks (PluginManager actually) when the plugin has been
      * loaded and should attach in Code::Blocks. When Code::Blocks
      * starts up, it finds and <em>loads</em> all plugins but <em>does
      * not</em> activate (attaches) them. It then activates all plugins
      * that the user has selected to be activated on start-up.\n
      * This means that a plugin might be loaded but <b>not</b> activated...\n
      * Think of this method as the actual constructor...
      */
    void OnAttach() override;

    /** Any descendent plugin should override this virtual method and
      * perform any necessary de-initialization. This method is called by
      * Code::Blocks (PluginManager actually) when the plugin has been
      * loaded, attached and should de-attach from Code::Blocks.\n
      * Think of this method as the actual destructor...
      * @param appShutDown If true, the application is shutting down. In this
      *         case *don't* use Manager::Get()->Get...() functions or the
      *         behaviour is undefined...
      */
    void OnRelease(bool appShutDown) override;

    cbTerminalView*                    m_pcbTerminalView;         // Panel added to Messages notebook
    cbTerminalViewManagerBase*         m_pViewManager;              // View manager. Used to add, remove, show and hide view.
 
};

#endif // CB_TERMINAL_H
