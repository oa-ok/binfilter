/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: evntconf.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:36:09 $
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
#ifndef _SFX_EVENTCONF_HXX
#define _SFX_EVENTCONF_HXX

#if _SOLAR__PRIVATE

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif

#endif

#define _SVSTDARR_USHORTS
#include <bf_svtools/svstdarr.hxx>      // SvUShorts
#include <bf_sfx2/cfgitem.hxx>
#include <bf_sfx2/event.hxx>

#include <bf_sfx2/sfxsids.hrc>
#ifdef ITEMID_MACRO
#undef ITEMID_MACRO
#endif
#define ITEMID_MACRO SID_ATTR_MACROITEM
#include <bf_svtools/macitem.hxx>
namespace binfilter {

class SfxMacroInfo;
class SfxMacroTabPage;
class SfxMacroInfoArr_Impl;
class SfxEventConfigItem_Impl;
class SfxEventInfoArr_Impl;
class SfxObjectShell;

#define SFX_NO_EVENT USHRT_MAX

#if _SOLAR__PRIVATE
struct SfxEvent_Impl
{
    String                      aEventName;
    USHORT                      nEventId;

    SfxEvent_Impl(const String& rName, USHORT nId) :
        aEventName(rName),
        nEventId(nId)
    {}
};

SV_DECL_PTRARR(SfxEventArr_Impl, SfxEvent_Impl*, 5, 5)//STRIP008 ;

// -----------------------------------------------------------------------

#define PROP_EVENT_TYPE     "EventType"
#define PROP_LIBRARY        "Library"
#define PROP_SCRIPT         "Script"
#define PROP_SCRIPT_URL     "URL"
#define PROP_MACRO_NAME     "MacroName"
#define STAR_BASIC          "StarBasic"
#define JAVA_SCRIPT         "JavaScript"

// -----------------------------------------------------------------------
#else
typedef SvPtrarr SfxEventArr_Impl;
#endif

class SfxEventConfiguration
{
friend class SfxEventConfigItem_Impl;

    SfxMacroInfoArr_Impl*   pArr;
    SfxEventArr_Impl*       pEventArr;
    SfxEventConfigItem_Impl* pAppEventConfig;
    SfxEventConfigItem_Impl* pDocEventConfig;
    sal_Bool                bIgnoreConfigure;

public:
                            SfxEventConfiguration();
                            ~SfxEventConfiguration();

    void                    RegisterEvent(USHORT nId, const String& rName);
    String                  GetEventName(USHORT nId) const;
    USHORT                  GetEventId(const String& rName) const;
    USHORT                  GetEventCount() const
                            { return pEventArr->Count()-1; }
    const SvxMacro*         GetMacroForEventId( USHORT nEventId, SfxObjectShell *pObjSh );
    void                    ConfigureEvent(USHORT nId, const SvxMacro&,
                                SfxObjectShell* pObjSh);
    void                    ConfigureEvent(USHORT nId, const String& rMacro,
                                SfxObjectShell* pObjSh);

    const SfxMacroInfo*     GetMacroInfo(USHORT nEventId, SfxObjectShell* pObjSh) const;

    void                    AddEvents( SfxMacroTabPage* ) const;
    SvxMacroTableDtor*      GetAppEventTable();
    SvxMacroTableDtor*      GetDocEventTable(SfxObjectShell*);
    void                    SetAppEventTable( const SvxMacroTableDtor& );
    void                    SetDocEventTable( SfxObjectShell*, const SvxMacroTableDtor& );

    static void             RegisterEvent( USHORT nId, const String& rName,
                                           const String& rMacroName );

    static BOOL             Import( SvStream& rInStream, SvStream* pOutStream, SfxObjectShell* pDoc=NULL );
    static BOOL             Export( SvStream* pInStream, SvStream& rOutStream, SfxObjectShell* pDoc=NULL );

#if _SOLAR__PRIVATE
    SfxEventConfigItem_Impl*    GetAppEventConfig_Impl();
    const SfxEvent_Impl*        GetEvent_Impl(USHORT nPos) const
                                    { return (*pEventArr)[nPos+1]; }
    BOOL                        Warn_Impl( SfxObjectShell *pDoc, const SvxMacro* pMacro );
    void                        PropagateEvents_Impl( SfxObjectShell *pDoc,
                                                      const SvxMacroTableDtor& rTable );
    void                        PropagateEvent_Impl( SfxObjectShell *pDoc,
                                                     USHORT nId,
                                                     const SvxMacro* pMacro );
    static ::rtl::OUString      GetEventName_Impl( ULONG nID );
    static ULONG                GetEventId_Impl( const ::rtl::OUString& rEventName );
    ::com::sun::star::uno::Any  CreateEventData_Impl( const SvxMacro *pMacro );

    static ULONG                GetPos_Impl( USHORT nID, sal_Bool &rFound );
    static ULONG                GetPos_Impl( const String& rName, sal_Bool &rFound );
#endif
};

#if _SOLAR__PRIVATE
class SfxEventConfigItem_Impl : public SfxConfigItem
{
friend class SfxEventConfiguration;

    SvxMacroTableDtor       aMacroTable;
    SfxEventConfiguration   *pEvConfig;
    SfxObjectShell          *pObjShell;
    BOOL                    bWarning;
    BOOL                    bAlwaysWarning;
    BOOL                    bInitialized;

    void                    ConstructMacroTable();
    int                     Load(SvStream&);
    BOOL                    Store(SvStream&);
    BOOL                    LoadXML(SvStream&);
    BOOL                    StoreXML(SvStream&);

public:
                            SfxEventConfigItem_Impl( USHORT,
                                SfxEventConfiguration*,
                                SfxObjectShell* pObjSh = NULL );
                            ~SfxEventConfigItem_Impl();

    void                    Init( SfxConfigManager* );
    virtual int             Load(SotStorage&);
    virtual BOOL            Store(SotStorage&);
    virtual String          GetStreamName() const;
    virtual void            UseDefault();
    void                    ConfigureEvent( USHORT nPos, SvxMacro* );
};

#endif

}//end of namespace binfilter
#endif
