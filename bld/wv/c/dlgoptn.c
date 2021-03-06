/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/

#include "dbgdefn.h"
#include "dbgdata.h"
#include "dbgwind.h"
#include "guidlg.h"
#include "dbgerr.h"
#include "dlgoptn.h"
#include "dbgscan.h"
#include "trapglbl.h"
#include "dbglkup.h"
#include "dlgexpr.h"


static void GetDlgStatus( gui_window *gui )
{
    long        tmp;
    unsigned    old;

    old = NewCurrRadix( 10 );
    _SwitchSet( SW_AUTO_SAVE_CONFIG, GUIIsChecked( gui, CTL_OPT_AUTO ) );
    _SwitchSet( SW_BELL, GUIIsChecked( gui, CTL_OPT_BELL ) );
    _SwitchSet( SW_IMPLICIT, GUIIsChecked( gui, CTL_OPT_IMPLICIT ) );
    _SwitchSet( SW_RECURSE_CHECK, GUIIsChecked( gui, CTL_OPT_RECURSE ) );
    _SwitchSet( SW_FLIP, GUIIsChecked( gui, CTL_OPT_FLIP ) );
    _SwitchSet( SW_DONT_EXPAND_HEX, GUIIsChecked( gui, CTL_OPT_NOHEX ) );
    LookCaseSet( !GUIIsChecked( gui, CTL_OPT_CASE ) );
    if( DlgGetLong( gui, CTL_OPT_RADIX, &tmp ) ) {
        DefaultRadixSet( tmp );
        old = NewCurrRadix( 10 );
    }
    if( DlgGetLong( gui, CTL_OPT_DCLICK, &tmp ) ) {
        WndSetDClick( tmp );
    }
    NewCurrRadix( old );

    SetCapabilitiesExactBreakpointSupport( GUIIsChecked( gui, CTL_OPT_BR_ON_WRITE ), TRUE );
}


static void SetDlgStatus( gui_window *gui )
{
    unsigned    old;

    old = NewCurrRadix( 10 );
    GUISetChecked( gui, CTL_OPT_AUTO, _IsOn( SW_AUTO_SAVE_CONFIG ) );
    GUISetChecked( gui, CTL_OPT_BELL, _IsOn( SW_BELL ) );
    GUISetChecked( gui, CTL_OPT_IMPLICIT, _IsOn( SW_IMPLICIT ) );
    GUISetChecked( gui, CTL_OPT_RECURSE, _IsOn( SW_RECURSE_CHECK ) );
    GUISetChecked( gui, CTL_OPT_FLIP, _IsOn( SW_FLIP ) );
    GUISetChecked( gui, CTL_OPT_CASE, _IsOn( SW_CASE_IGNORE ) );
    DlgSetLong( gui, CTL_OPT_RADIX, old );
    DlgSetLong( gui, CTL_OPT_DCLICK, WndGetDClick() );
    NewCurrRadix( old );
    GUIEnableControl( gui, CTL_OPT_BR_ON_WRITE, IsExactBreakpointsSupported() );
    GUISetChecked( gui, CTL_OPT_NOHEX, _IsOn( SW_DONT_EXPAND_HEX ) );
    if( IsExactBreakpointsSupported() ) {
        GUISetChecked( gui, CTL_OPT_BR_ON_WRITE, _IsOn( SW_BREAK_ON_WRITE ) );
    } else {
        GUISetChecked( gui, CTL_OPT_BR_ON_WRITE, FALSE );
    }
}


OVL_EXTERN bool OptSetEvent( gui_window *gui, gui_event gui_ev, void *param )
{
    gui_ctl_id      id;
    dlg_window_set  *optset;

    optset = GUIGetExtra( gui );
    switch( gui_ev ) {
    case GUI_INIT_DIALOG:
        SetDlgStatus( gui );
        GUISetFocus( gui, CTL_OPT_RADIX );
        return( true );
    case GUI_CONTROL_CLICKED :
        GUI_GETID( param, id );
        switch( id ) {
        case CTL_OPT_OK:
            optset->cancel = false;
            GetDlgStatus( gui );
            GUICloseDialog( gui );
            break;
        case CTL_OPT_CANCEL:
            optset->cancel = true;
            GUICloseDialog( gui );
            break;
        case CTL_OPT_DEFAULTS:
            SetDlgStatus( gui );
            break;
        }
        return( true );
    }
    return( false );
}


extern  bool    DlgOptSet( void )
{
    dlg_window_set      optset;

    optset.cancel = true;
    ResDlgOpen( &OptSetEvent, &optset, GUI_MAKEINTRESOURCE( DIALOG_OPTION ) );
    return( !optset.cancel );
}
