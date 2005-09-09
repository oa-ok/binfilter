/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: progress.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:33:13 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef _SFX_PROGRESS_HXX
#define _SFX_PROGRESS_HXX

#include <tools/solar.h>

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
class String;
namespace binfilter {

class SfxObjectShell;
class SfxStatusBarManager;
class INetHint;
class SvDispatch;
struct SfxProgress_Impl;
struct PlugInLoadStatus;
struct SvProgressArg;

//=======================================================================

class SfxProgress
{
    SfxProgress_Impl*       pImp;
    ULONG                   nVal;
    BOOL                    bSuspended;

public:
#if SUPD>=349
                            SfxProgress( SfxObjectShell* pObjSh,
                                         const String& rText,
                                         ULONG nRange, BOOL bAllDocs = FALSE,
                                         BOOL bWait = TRUE );
#else
                            SfxProgress( SfxObjectShell* pObjSh,
                                         const String& rText,
                                         ULONG nRange, BOOL bAllDocs = FALSE );
#endif
    virtual                 ~SfxProgress();

    virtual void            SetText( const String& rText );
//STRIP001  BOOL                    SetStateText( ULONG nVal, const String &rVal, ULONG nNewRange = 0 );
    virtual BOOL            SetState( ULONG nVal, ULONG nNewRange = 0 );
    ULONG                   GetState() const { return nVal; }

    void                    Resume();
    void                    Suspend();
    BOOL                    IsSuspended() const { return bSuspended; }

    void                    Lock();
//STRIP001  void                    UnLock();
    void                    Reschedule();

    void                    Stop();

//STRIP001  void                    SetWaitMode( BOOL bWait );
//STRIP001  BOOL                    GetWaitMode() const;

    static SfxProgress*     GetActiveProgress( SfxObjectShell *pDocSh = 0 );
//STRIP001  static void             EnterLock();
//STRIP001  static void             LeaveLock();

#if _SOLAR__PRIVATE
    DECL_STATIC_LINK( SfxProgress, SetStateHdl, PlugInLoadStatus* );
    DECL_STATIC_LINK( SfxProgress, DefaultBindingProgress, SvProgressArg* );
    FASTBOOL                StatusBarManagerGone_Impl(SfxStatusBarManager*pStb);
//STRIP001  const String&           GetStateText_Impl() const;
#endif
};

}//end of namespace binfilter
#endif

