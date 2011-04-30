/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#include <horiornt.hxx>

#include "txtatr.hxx"  // SwINetFmt


#include <pagedesc.hxx> // SwPageDesc

#include "itrpaint.hxx"
#include "pormulti.hxx"
namespace binfilter {

/*************************************************************************
 *                  IsUnderlineBreak
 *
 * Returns, if we have an underline breaking situation
 * Adding some more conditions here means you also have to change them
 * in SwTxtPainter::CheckSpecialUnderline
 *************************************************************************/
/*N*/ sal_Bool IsUnderlineBreak( const SwLinePortion& rPor, const SwFont& rFnt )
/*N*/ {
/*N*/     return UNDERLINE_NONE == rFnt.GetUnderline() ||
/*N*/            rPor.IsFlyPortion() || rPor.IsFlyCntPortion() ||
/*N*/            rPor.IsBreakPortion() || rPor.IsMarginPortion() ||
/*N*/            rPor.IsHolePortion() ||
/*N*/           ( rPor.IsMultiPortion() && ! ((SwMultiPortion&)rPor).IsBidi() ) ||
/*N*/            rFnt.GetEscapement() < 0 || rFnt.IsWordLineMode() ||
/*N*/            SVX_CASEMAP_KAPITAELCHEN == rFnt.GetCaseMap();
/*N*/ }

/*************************************************************************
 *                  SwTxtPainter::CtorInit()
 *************************************************************************/
/*N*/ void SwTxtPainter::CtorInit( SwTxtFrm *pFrm1, SwTxtPaintInfo *pNewInf )
/*N*/ {
/*N*/   SwTxtCursor::CtorInit( pFrm1, pNewInf );
/*N*/   pInf = pNewInf;
/*N*/   SwFont *pFnt2 = GetFnt();
/*N*/   GetInfo().SetFont( pFnt2 );
/*N*/ #ifdef DBG_UTIL
/*N*/   if( ALIGN_BASELINE != pFnt2->GetAlign() )
/*N*/   {
/*?*/       OSL_ENSURE( ALIGN_BASELINE == pFnt2->GetAlign(),
/*?*/               "+SwTxtPainter::CTOR: font alignment revolution" );
/*?*/       pFnt2->SetAlign( ALIGN_BASELINE );
/*N*/   }
/*N*/ #endif
/*N*/   bPaintDrop = sal_False;
/*N*/ }

/*************************************************************************
 *                    SwTxtPainter::DrawTextLine()
 *
 * Es gibt zwei Moeglichkeiten bei transparenten Font auszugeben:
 * 1) DrawRect auf die ganze Zeile und die DrawText hinterher
 *    (objektiv schnell, subjektiv langsam).
 * 2) Fuer jede Portion ein DrawRect mit anschliessendem DrawText
 *    ausgefuehrt (objektiv langsam, subjektiv schnell).
 * Da der User in der Regel subjektiv urteilt, wird die 2. Methode
 * als Default eingestellt.
 *************************************************************************/

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
