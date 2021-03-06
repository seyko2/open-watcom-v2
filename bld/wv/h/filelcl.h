/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2015-2015 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  Local file functions declaration
*
****************************************************************************/


extern error_idx        LocalErase( char const * );
extern void             LocalErrMsg( sys_error, char * );
extern unsigned         LocalRead( sys_handle, void *, unsigned );
extern unsigned         LocalWrite( sys_handle, const void *, unsigned );
extern unsigned long    LocalSeek( sys_handle, unsigned long, seek_method );
extern sys_handle       LocalOpen( char const *, open_access );
extern error_idx        LocalClose( sys_handle );
extern sys_handle       LocalHandleSys( handle );
extern long             LocalGetFileDate( const char *name );
extern bool             LocalSetFileDate( const char *name, long date );

extern file_components  LclFile;
extern char             LclPathSep;
