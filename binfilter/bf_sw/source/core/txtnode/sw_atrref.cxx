/*************************************************************************
 *
 *  $RCSfile: sw_atrref.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:38:52 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _TXTRFMRK_HXX //autogen
#include <txtrfmrk.hxx>
#endif
#ifndef _FMTRFMRK_HXX //autogen
#include <fmtrfmrk.hxx>
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>
#endif


/****************************************************************************
 *
 *  class SwFmtRefMark
 *
 ****************************************************************************/

/*N*/ SwFmtRefMark::~SwFmtRefMark( )
/*N*/ {
/*N*/ }

/*N*/ SwFmtRefMark::SwFmtRefMark( const XubString& rName )
/*N*/   : SfxPoolItem( RES_TXTATR_REFMARK ),
/*N*/   aRefName( rName ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

/*N*/ SwFmtRefMark::SwFmtRefMark( const SwFmtRefMark& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_REFMARK ),
/*N*/   aRefName( rAttr.aRefName ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

int SwFmtRefMark::operator==( const SfxPoolItem& rAttr ) const
{
    {DBG_ASSERT(0, "STRIP");} return 0;//STRIP001   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001  return aRefName == ((SwFmtRefMark&)rAttr).aRefName;
}

/*N*/ SfxPoolItem* SwFmtRefMark::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtRefMark( *this );
/*N*/ }

/*************************************************************************
 *                      class SwTxtRefMark
 *************************************************************************/

// Attribut fuer Inhalts-/Positions-Referenzen im Text

/*N*/ SwTxtRefMark::SwTxtRefMark( const SwFmtRefMark& rAttr,
/*N*/                   xub_StrLen nStart, xub_StrLen* pEnde )
/*N*/   : SwTxtAttrEnd( rAttr, nStart, nStart ),
/*N*/   pEnd( 0 ),
/*N*/   pMyTxtNd( 0 )
/*N*/ {
/*N*/   ((SwFmtRefMark&)rAttr).pTxtAttr = this;
/*N*/   if( pEnde )
/*N*/   {
/*N*/       nEnd = *pEnde;
/*N*/       pEnd = &nEnd;
/*N*/   }
/*N*/   SetDontMergeAttr( TRUE );
/*N*/   SetDontMoveAttr( TRUE );
/*N*/   SetOverlapAllowedAttr( TRUE );
/*N*/ }

/*N*/ xub_StrLen* SwTxtRefMark::GetEnd()
/*N*/ {
/*N*/   return pEnd;
/*N*/ }

