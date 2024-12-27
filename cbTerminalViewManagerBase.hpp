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

#ifndef CB_TERMINAL_VIEW_MANAGER_BASE_H
#define CB_TERMINAL_VIEW_MANAGER_BASE_H

#include <stdint.h>

class cbTerminalView;

class cbTerminalViewManagerBase
{
public:
    enum eManagerTypes
    {
        TypeMessagesNotebook = 0,
        TypeLayout
    };

    /** BuildcbTerminalViewManagerBase
      * Builds a cbTerminalViewManagerMessagesNotebook or a cbTerminalViewManagerAui pointer depending
      * on managerType.
      * @return cbTerminalViewManagerBase*
      */
    static cbTerminalViewManagerBase* BuildcbTerminalViewManagerBase(cbTerminalView* pView,
                                                                         bool              addViewToManager,
                                                                         eManagerTypes     managerType);

    /** Destructor. */
    virtual ~cbTerminalViewManagerBase() {}

    eManagerTypes virtual GetManagerType() = 0;

    /** By default, view is not managed by the manager.
      * This method adds view to manager if not already managed
      * and given in constructor.
      * No parameters because only m_pcbTerminalView is managed.
      */
    virtual void AddViewToManager() = 0;

    /** By default, view is not managed by the manager.
      * This method removes view from manager if managed.
      * No parameters because only m_pcbTerminalView is managed
      * and given in constructor.
      * m_pcbTerminalView is not modified.
      */
    virtual void RemoveViewFromManager() = 0;

    enum ShowViewFlags : uint32_t
    {
        None = 0,
        Show = 1, ///< Shows the view
        PreserveFocus = 2 ///< Tries to preserve the focus after the show operation.
    };

    /** Return true if success. Fails if view is not managed.
      * @param flags Specifies the behaviour of the call. @sa ShowViewFlags
      * @return true if success.
      */
    virtual bool ShowView(uint32_t flags) = 0;

    /** Return true if view is visible.
      * @return true if view is visible.
      */
    virtual bool IsViewShown() = 0;

    /** Try to rise the panel the view is in */
    virtual void Raise() = 0;

protected:
    /** Constructor. */
    cbTerminalViewManagerBase(cbTerminalView* pcbTerminalView)
        : m_pcbTerminalView(pcbTerminalView)
        , m_IsManaged(false)
        , m_IsShown(false)
    {
    }

    cbTerminalView* m_pcbTerminalView;
    bool              m_IsManaged;
    bool              m_IsShown;
};

#endif // CB_TERMINAL_VIEW_MANAGER_BASE_H
