/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sc_forbiuno.cxx,v $
 * $Revision: 1.7 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <bf_svx/forbiddencharacterstable.hxx>

#include "forbiuno.hxx"
#include "docsh.hxx"
namespace binfilter {

using namespace ::com::sun::star;

//------------------------------------------------------------------------

vos::ORef<SvxForbiddenCharactersTable> lcl_GetForbidden( ScDocShell* pDocSh )
{
    vos::ORef<SvxForbiddenCharactersTable> xRet;
    if ( pDocSh )
    {
        ScDocument* pDoc = pDocSh->GetDocument();
        xRet = pDoc->GetForbiddenCharacters();
        if ( !xRet.isValid() )
        {
            //  create an empty SvxForbiddenCharactersTable for SvxUnoForbiddenCharsTable,
            //  so changes can be stored.

            xRet = new SvxForbiddenCharactersTable( pDoc->GetServiceManager() );
            pDoc->SetForbiddenCharacters( xRet );
        }
    }
    return xRet;
}

ScForbiddenCharsObj::ScForbiddenCharsObj( ScDocShell* pDocSh ) :
    SvxUnoForbiddenCharsTable( lcl_GetForbidden( pDocSh ) ),
    pDocShell( pDocSh )
{
    if (pDocShell)
        pDocShell->GetDocument()->AddUnoObject(*this);
}

ScForbiddenCharsObj::~ScForbiddenCharsObj()
{
    if (pDocShell)
        pDocShell->GetDocument()->RemoveUnoObject(*this);
}

void ScForbiddenCharsObj::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
{
    if ( rHint.ISA( SfxSimpleHint ) &&
            ((const SfxSimpleHint&)rHint).GetId() == SFX_HINT_DYING )
    {
        pDocShell = NULL;       // document gone
    }
}

void ScForbiddenCharsObj::onChange()
{
    if (pDocShell)
    {
        pDocShell->GetDocument()->SetForbiddenCharacters( mxForbiddenChars );
        pDocShell->PostPaintGridAll();
        pDocShell->SetDocumentModified();
    }
}

}
