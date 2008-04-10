/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sdvcbrw.hxx,v $
 * $Revision: 1.5 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _SDVCBRW_HXX
#define _SDVCBRW_HXX
/*
#ifndef _SVX_VCBRW_HXX //autogen
#include <bf_svx/vcbrw.hxx>
#endif
*/
#ifndef _SFXBRDCST_HXX //autogen
#include <bf_svtools/brdcst.hxx>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <bf_svtools/lstner.hxx>
#endif
namespace binfilter {

class SdrView;

/*************************************************************************
|*
|* Klasse fuer Browser
|*
\************************************************************************/
class SdVCBrowser : public VCBrowser //, public SfxListener, public SfxBroadcaster
{
protected:
    SdrView*    pView;
    BOOL        bUpdate;

    BOOL    Close();

    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                         const SfxHint& rHint, const TypeId& rHintType );
    void         Modify();


public:
    SdVCBrowser( Window* pParent );

    void Update( SdrView* pView );
};




} //namespace binfilter
#endif      // _SDVCBRW_HXX
