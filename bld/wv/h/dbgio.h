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
* Description:  Debugger file I/O layer interface.
*
****************************************************************************/


#include "sysdef.h"

typedef int             handle;

typedef unsigned_8 seek_method; enum {
    DIO_SEEK_ORG,
    DIO_SEEK_CUR,
    DIO_SEEK_END
};

typedef unsigned_8 open_access; enum {
    OP_READ         = 0x01,
    OP_WRITE        = 0x02,
    OP_CREATE       = 0x04,
    OP_TRUNC        = 0x08,
    OP_APPEND       = 0x10,
    OP_EXEC         = 0x10, // only valid with OP_CREATE - ran out of bits
    OP_REMOTE       = 0x20,
    OP_LOCAL        = 0x40,
    OP_SEARCH       = 0x80
};

#define NIL_HANDLE      ((handle)-1)

#define ERR_RETURN      ((unsigned)-1)

#define STD_IN          0
#define STD_OUT         1
#define STD_ERR         2

extern unsigned         ReadStream( handle, void *, unsigned );
extern unsigned         ReadText( handle, void *, unsigned );

extern unsigned         WriteStream( handle, const void *, unsigned );
extern unsigned         WriteNL( handle );
extern unsigned         WriteText( handle, const void *, unsigned );

extern unsigned long    SeekStream( handle, long, seek_method );

extern handle           FileOpen( char const *, open_access );
extern error_idx        FileClose( handle );
extern error_idx        FileRemove( char const *, open_access );
extern const char       *FileLoc( char const *, open_access * );
extern open_access      FileHandleInfo( handle );
extern sys_handle       GetSystemHandle( handle );

extern char             *SysErrMsg( error_idx, char *buff );
extern error_idx        StashErrCode( sys_error, open_access );
extern error_idx        GetLastErr( void );
extern sys_error        GetSystemErrCode( error_idx );

extern const char       *SkipPathInfo( char const *, open_access );
extern const char       *ExtPointer( char const *, open_access );
extern char             *AppendPathDelim( char *, open_access );
extern unsigned         MakeFileName( char *result, const char *name, const char *ext, open_access loc );
extern const char       *RealFName( char const *name, open_access *loc );
extern bool             IsAbsolutePath( const char *path );
extern char             *AppendPathDelim( char *path, open_access loc );
extern const char       *ExtPointer( char const *path, open_access loc );
extern handle           LclStringToFullName( const char *name, unsigned len, char *full );
extern handle           FullPathOpen( const char *name, unsigned name_len, const char *ext, char *result, unsigned max_result );
extern handle           LocalFullPathOpen( const char *name, unsigned name_len, const char *ext, char *result, unsigned max_result );
extern handle           PathOpen( const char *name, unsigned name_len, const char *ext );
extern handle           LocalPathOpen( const char *name, unsigned name_len, const char *ext );

extern bool             FindWritable( char const *, char * );
#if !defined( BUILD_RFX )
extern bool             FindWritable( char const *src, char *dst );
#endif

extern void             WriteToPgmScreen( const void *buff, unsigned len );
extern void             SysFileInit( void );
#if !defined( BUILD_RFX )
extern void             PathFini( void );
#endif
extern void             PathInit( void );
