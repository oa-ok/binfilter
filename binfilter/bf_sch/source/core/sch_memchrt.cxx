/*************************************************************************
 *
 *  $RCSfile: sch_memchrt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:55:50 $
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

#ifndef _STREAM_HXX
// enable stream operators >>/<< for UniString (8 Bit !)
#ifndef ENABLE_STRING_STREAM_OPERATORS
#define ENABLE_STRING_STREAM_OPERATORS
#endif
#include <tools/stream.hxx>
#endif

#ifndef _ZFORLIST_HXX //autogen
#ifndef _ZFORLIST_DECLARE_TABLE
#define _ZFORLIST_DECLARE_TABLE
#endif
#include <svtools/zforlist.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif

#include <float.h>
#include <math.h>
#include "schiocmp.hxx"
#include "memchrt.hxx"

#include "schresid.hxx"
#include "glob.hrc"

#include <functional>
#include <algorithm>

// ========================================
// Helper objects
// ========================================

/** unary function that escapes backslashes and single quotes in a sal_Unicode
    array (which you can get from an OUString with getStr()) and puts the result
    into the OUStringBuffer given in the CTOR
 */
//STRIP001 class lcl_Escape : public ::std::unary_function< sal_Unicode, void >
//STRIP001 {
//STRIP001 public:
//STRIP001     lcl_Escape( ::rtl::OUStringBuffer & aResultBuffer ) : m_aResultBuffer( aResultBuffer ) {}
//STRIP001     void operator() ( sal_Unicode aChar )
//STRIP001     {
//STRIP001         static const sal_Unicode m_aQuote( '\'' );
//STRIP001         static const sal_Unicode m_aBackslash( '\\' );
//STRIP001
//STRIP001         if( aChar == m_aQuote ||
//STRIP001             aChar == m_aBackslash )
//STRIP001             m_aResultBuffer.append( m_aBackslash );
//STRIP001         m_aResultBuffer.append( aChar );
//STRIP001     }
//STRIP001
//STRIP001 private:
//STRIP001     ::rtl::OUStringBuffer & m_aResultBuffer;
//STRIP001 };

/** unary function that removes backslash escapes in a sal_Unicode array (which
    you can get from an OUString with getStr()) and puts the result into the
    OUStringBuffer given in the CTOR
 */
//STRIP001 class lcl_UnEscape : public ::std::unary_function< sal_Unicode, void >
//STRIP001 {
//STRIP001 public:
//STRIP001     lcl_UnEscape( ::rtl::OUStringBuffer & aResultBuffer ) : m_aResultBuffer( aResultBuffer ) {}
//STRIP001     void operator() ( sal_Unicode aChar )
//STRIP001     {
//STRIP001         static const sal_Unicode m_aBackslash( '\\' );
//STRIP001
//STRIP001         if( aChar != m_aBackslash )
//STRIP001             m_aResultBuffer.append( aChar );
//STRIP001     }
//STRIP001
//STRIP001 private:
//STRIP001     ::rtl::OUStringBuffer & m_aResultBuffer;
//STRIP001 };



#define MIN(a,b) ( ((a)<(b))? (a) : (b) )
/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

//STRIP001 SchMemChart::SchMemChart() :
//STRIP001  nTranslated(TRANS_NONE),
//STRIP001  nRefCount (0),
//STRIP001  mpColNameBuffer(NULL),
//STRIP001  mpRowNameBuffer(NULL),
//STRIP001  nRowCnt (0),
//STRIP001  nColCnt (0),
//STRIP001  eDataType(NUMBERFORMAT_NUMBER),
//STRIP001  pData (0),
//STRIP001  pColText (0),
//STRIP001  pRowText (0),
//STRIP001  myID (CHDATAID_MEMCHART_PLUS),
//STRIP001  mpNumFormatter(NULL),
//STRIP001  pRowNumFmtId(NULL),
//STRIP001  pColNumFmtId(NULL),
//STRIP001  pRowTable(NULL),
//STRIP001  pColTable(NULL),
//STRIP001  bReadOnly(FALSE),
//STRIP001  nLastSelInfoReturn(0)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchMemChart::SchMemChart(ChartDataId nMyID) :
/*N*/   nTranslated(TRANS_NONE),
/*N*/   nRefCount (0),
/*N*/   mpColNameBuffer(NULL),
/*N*/   mpRowNameBuffer(NULL),
/*N*/   nRowCnt (0),
/*N*/   nColCnt (0),
/*N*/   eDataType(NUMBERFORMAT_NUMBER),
/*N*/   pData (0),
/*N*/   pColText (0),
/*N*/   pRowText (0),
/*N*/   myID (nMyID),
/*N*/   mpNumFormatter(NULL),
/*N*/   pRowNumFmtId(NULL),
/*N*/   pColNumFmtId(NULL),
/*N*/   pRowTable(NULL),
/*N*/   pColTable(NULL),
/*N*/   bReadOnly(FALSE),
/*N*/   nLastSelInfoReturn(0)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ SchMemChart::SchMemChart(short nCols, short nRows) :
/*N*/   nTranslated(TRANS_NONE),
/*N*/   nRefCount (0),
/*N*/   mpColNameBuffer(NULL),
/*N*/   mpRowNameBuffer(NULL),
/*N*/   eDataType(NUMBERFORMAT_NUMBER),
/*N*/   pData (0),
/*N*/   pColText (0),
/*N*/   pRowText (0),
/*N*/   myID (CHDATAID_MEMCHART_PLUS),
/*N*/   mpNumFormatter(NULL),
/*N*/   pRowNumFmtId(NULL),
/*N*/   pColNumFmtId(NULL),
/*N*/   pRowTable(NULL),
/*N*/   pColTable(NULL),
/*N*/   bReadOnly(FALSE),
/*N*/   nLastSelInfoReturn(0)
/*N*/ {
/*N*/   nRowCnt = nRows;
/*N*/   nColCnt = nCols;
/*N*/   pData   = new double[nColCnt * nRowCnt];
/*N*/
/*N*/   pRowNumFmtId= new long [nRowCnt];
/*N*/   pColNumFmtId= new long [nColCnt];
/*N*/   InitNumFmt();
/*N*/
/*N*/   pRowTable   = new long [nRowCnt];
/*N*/   pColTable   = new long [nColCnt];
/*N*/   ResetTranslation(pRowTable,nRowCnt);
/*N*/   ResetTranslation(pColTable,nColCnt);
/*N*/
/*N*/   if (pData)
/*N*/   {
/*N*/       double *pFill = pData;
/*N*/
/*N*/       for (short i = 0; i < nColCnt; i++)
/*N*/           for (short j = 0; j < nRowCnt; j++)
/*N*/               *(pFill ++) = 0.0;
/*N*/   }
/*N*/
/*N*/   pColText = new String[nColCnt];
/*N*/   pRowText = new String[nRowCnt];
/*N*/ }
/*************************************************************************
|*
|* Kopiere alles ausser den numerischen Daten (d.h. Texte!)
|*
\************************************************************************/
/*N*/ void SchMemChart::SetNonNumericData(const SchMemChart &rMemChart)
/*N*/ {
/*N*/   aMainTitle  = rMemChart.aMainTitle;
/*N*/   aSubTitle   = rMemChart.aSubTitle;
/*N*/   aXAxisTitle = rMemChart.aXAxisTitle;
/*N*/   aYAxisTitle = rMemChart.aYAxisTitle;
/*N*/   aZAxisTitle = rMemChart.aZAxisTitle;
/*N*/   eDataType   = rMemChart.eDataType;
/*N*/   aSomeData1  = ((SchMemChart&) rMemChart).SomeData1 ();
/*N*/   aSomeData2  = ((SchMemChart&) rMemChart).SomeData2 ();
/*N*/   aSomeData3  = ((SchMemChart&) rMemChart).SomeData3 ();
/*N*/   aSomeData4  = ((SchMemChart&) rMemChart).SomeData4 ();
/*N*/
/*N*/   long nCols=MIN(nColCnt,rMemChart.nColCnt);
/*N*/   long nRows=MIN(nRowCnt,rMemChart.nRowCnt);
/*N*/
/*N*/   short i;
/*N*/   for (i = 0; i < nCols; i++)
/*N*/       pColText[i] = rMemChart.pColText[i];
/*N*/   for (i = 0; i < nRows; i++)
/*N*/       pRowText[i] = rMemChart.pRowText[i];
/*N*/
/*N*/     // copy chart range
/*N*/     SetChartRange( rMemChart.GetChartRange());
/*N*/ }
/*************************************************************************
|*
|* Kopier-Konstruktor
|*
\************************************************************************/

/*N*/ SchMemChart::SchMemChart(const SchMemChart& rMemChart) :
/*N*/   nTranslated(TRANS_NONE),
/*N*/   nRefCount (0),
/*N*/   mpColNameBuffer(NULL),
/*N*/   mpRowNameBuffer(NULL),
/*N*/   myID (CHDATAID_MEMCHART_PLUS),
/*N*/   mpNumFormatter(NULL),
/*N*/   pRowNumFmtId(NULL),
/*N*/   pColNumFmtId(NULL),
/*N*/   pRowTable(NULL),
/*N*/   pColTable(NULL)
/*N*/ {
/*N*/   nColCnt     = rMemChart.nColCnt;
/*N*/   nRowCnt     = rMemChart.nRowCnt;
/*N*/   aMainTitle  = rMemChart.aMainTitle;
/*N*/   aSubTitle   = rMemChart.aSubTitle;
/*N*/   aXAxisTitle = rMemChart.aXAxisTitle;
/*N*/   aYAxisTitle = rMemChart.aYAxisTitle;
/*N*/   aZAxisTitle = rMemChart.aZAxisTitle;
/*N*/   eDataType   = rMemChart.eDataType;
/*N*/   aSomeData1  = ((SchMemChart&) rMemChart).SomeData1 ();
/*N*/   aSomeData2  = ((SchMemChart&) rMemChart).SomeData2 ();
/*N*/   aSomeData3  = ((SchMemChart&) rMemChart).SomeData3 ();
/*N*/   aSomeData4  = ((SchMemChart&) rMemChart).SomeData4 ();
/*N*/   pData       = new double[nColCnt * nRowCnt];
/*N*/
/*N*/   pRowNumFmtId= new long [nRowCnt];
/*N*/   pColNumFmtId= new long [nColCnt];
/*N*/   pRowTable   = new long [nRowCnt];
/*N*/   pColTable   = new long [nColCnt];
/*N*/
/*N*/     aAppLink = rMemChart.aAppLink;
/*N*/   nLastSelInfoReturn = rMemChart.nLastSelInfoReturn;
/*N*/
/*N*/   nTranslated = rMemChart.nTranslated;
/*N*/   long i;
/*N*/   for(i=0;i<nColCnt;i++)
/*N*/   {
/*N*/       pColTable[i]    = rMemChart.pColTable[i];
/*N*/       pColNumFmtId[i] = rMemChart.pColNumFmtId[i];
/*N*/   }
/*N*/   for(i=0;i<nRowCnt;i++)
/*N*/   {
/*N*/       pRowTable[i]    = rMemChart.pRowTable[i];
/*N*/       pRowNumFmtId[i] = rMemChart.pRowNumFmtId[i];
/*N*/   }
/*N*/   mpNumFormatter=rMemChart.mpNumFormatter;
/*N*/
/*N*/   if (pData)
/*N*/   {
/*N*/       double *pDest   = pData;
/*N*/       double *pSource = rMemChart.pData;
/*N*/
/*N*/       for (short i = 0; i < nColCnt; i++)
/*N*/           for (short j = 0; j < nRowCnt; j++)
/*N*/               *(pDest ++) = *(pSource ++);
/*N*/   }
/*N*/
/*N*/   pColText = new String[nColCnt];
/*N*/
/*N*/   for (i = 0; i < nColCnt; i++)
/*N*/       pColText[i] = rMemChart.pColText[i];
/*N*/
/*N*/   pRowText = new String[nRowCnt];
/*N*/
/*N*/   for (i = 0; i < nRowCnt; i++)
/*N*/       pRowText[i] = rMemChart.pRowText[i];
/*N*/
/*N*/   bReadOnly = rMemChart.bReadOnly;            // bm #69410#
/*N*/
/*N*/   // copy address members
/*N*/   maCategoriesRangeAddress = rMemChart.maCategoriesRangeAddress;
/*N*/   maSeriesAddresses = rMemChart.maSeriesAddresses;
/*N*/
/*N*/     // copy chart range
/*N*/     SetChartRange( rMemChart.GetChartRange());
/*N*/ }

//STRIP001 long SchMemChart::GetTableIndexRow(long nRow) const
//STRIP001 {
//STRIP001  long nTmp=-1;
//STRIP001  if(nRow<nRowCnt && nRow>=0)
//STRIP001      for(long i=0;i<nRowCnt;i++)
//STRIP001          if(pRowTable[i]==nRow)
//STRIP001              nTmp=i;
//STRIP001  if(nTmp!=-1)
//STRIP001      nRow=nTmp;
//STRIP001
//STRIP001  return nRow;
//STRIP001 }
//STRIP001 long SchMemChart::GetTableIndexCol(long nCol) const
//STRIP001 {
//STRIP001  long nTmp=-1;
//STRIP001  if(nCol<nColCnt && nCol>=0)
//STRIP001      for(long i=0;i<nColCnt;i++)
//STRIP001          if(pColTable[i]==nCol)
//STRIP001              nTmp=i;
//STRIP001  if(nTmp!=-1)
//STRIP001      nCol=nTmp;
//STRIP001
//STRIP001  return nCol;
//STRIP001 }
/*N*/ long SchMemChart::SubmitSelection(const ChartSelectionInfo& aInfo)
/*N*/ {
/*N*/   ChartSelectionInfo aNewInfo=aInfo;
/*N*/
/*N*/   //aNewInfo der Translationstabelle anpassen
/*N*/   if(nTranslated == TRANS_ROW)
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 aNewInfo.nRow=GetTableIndexRow(aInfo.nRow);
/*N*/   else if(nTranslated == TRANS_COL)
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 aNewInfo.nCol=GetTableIndexCol(aInfo.nCol);
/*N*/
/*N*/   if(aNewInfo == aSelectionInfo || aNewInfo.nSelection==0)
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 return nLastSelInfoReturn; //reduzieren doppelter Selektionen bzw. speziell der Deselektion!
/*N*/   aSelectionInfo = aNewInfo;
/*N*/   if(aAppLink.IsSet())
/*N*/   {
/*?*/       return nLastSelInfoReturn=aAppLink.Call(&aSelectionInfo);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       return nLastSelInfoReturn=0;
/*N*/   }
/*N*/ }
//STRIP001 BOOL SchMemChart::TransCol(long nCol,BOOL bUp)
//STRIP001 {
//STRIP001  if(nTranslated==TRANS_ROW)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if(bUp)
//STRIP001  {
//STRIP001      if(nCol+1 >= nColCnt)
//STRIP001          return FALSE;
//STRIP001
//STRIP001      long tmp=pColTable[nCol];
//STRIP001      pColTable[nCol]=pColTable[nCol+1];
//STRIP001      pColTable[nCol+1]=tmp;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if(nCol-1 <= 0)
//STRIP001          return FALSE;
//STRIP001
//STRIP001      long tmp=pColTable[nCol];
//STRIP001      pColTable[nCol]=pColTable[nCol-1];
//STRIP001      pColTable[nCol-1]=tmp;
//STRIP001  }
//STRIP001  nTranslated=TRANS_COL;
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001 BOOL SchMemChart::TransRow(long nRow,BOOL bUp)
//STRIP001 {
//STRIP001  if(nTranslated==TRANS_COL)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if(bUp)
//STRIP001  {
//STRIP001      if(nRow+1 >= nRowCnt)
//STRIP001          return FALSE;
//STRIP001
//STRIP001      long tmp=pRowTable[nRow];
//STRIP001      pRowTable[nRow]=pRowTable[nRow+1];
//STRIP001      pRowTable[nRow+1]=tmp;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if(nRow-1 <= 0)
//STRIP001          return FALSE;
//STRIP001
//STRIP001      long tmp=pRowTable[nRow];
//STRIP001      pRowTable[nRow]=pRowTable[nRow-1];
//STRIP001      pRowTable[nRow-1]=tmp;
//STRIP001  }
//STRIP001  nTranslated=TRANS_ROW;
//STRIP001  return TRUE;
//STRIP001 }

//�berpr�ft, ob die Umordnung/Translation OK ist, Fehlerfall, wenn :
// a) Spaltenumordnung aber Reihen vertauscht (FALSE,TRANS_ERROR)
// b) Reihenumordnung aber Spalten vertauscht (FALSE,TRANS_ERROR)
// c) keine Umordnung, Reihen oder Spalten vertauscht (FALSE,TRANS_ERROR)
// d) Umordnungsflag gesetzt (auf TRANS_ROW,TRANS_COL oder TRANS_ERROR) aber
//      keine Umordnung (mehr) vorhanden (FALSE,TRANS_NONE)
// sonst wird TRUE zur�ckgegeben

/*N*/ BOOL SchMemChart::VerifyTranslation()
/*N*/ {
/*N*/   //Fehler ?
/*N*/   if(nTranslated!=TRANS_COL)
/*N*/   {
/*N*/       for(long nCol=0;nCol<nColCnt;nCol++)
/*N*/       {
/*N*/           if(pColTable[nCol]!=nCol)
/*N*/           {
/*?*/               //nTranslated=TRANS_ERROR;
/*?*/               if(nTranslated==TRANS_NONE)
/*?*/               {
/*?*/                   DBG_ERROR("SchMemChart::Correcting Translationmode");
/*?*/                   nTranslated=TRANS_COL;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   DBG_ERROR("fatal error in SchMemChart-translation");
/*?*/                   return FALSE;
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if(nTranslated!=TRANS_ROW)
/*N*/   {
/*N*/       for(long nRow=0;nRow<nRowCnt;nRow++)
/*N*/       {
/*N*/           if(pRowTable[nRow]!=nRow)
/*N*/           {
/*?*/               //nTranslated=TRANS_ERROR;
/*?*/               if(nTranslated==TRANS_NONE)
/*?*/               {
/*?*/                   DBG_ERROR("SchMemChart::Correcting Translationmode");
/*?*/                   nTranslated=TRANS_ROW;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   DBG_ERROR("fatal error in SchMemChart-translation");
/*?*/                   return FALSE;
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Sortierung besteht noch ?
/*N*/   if(nTranslated==TRANS_ROW)
/*N*/   {
/*?*/       for(long nRow=0;nRow<nRowCnt;nRow++)
/*?*/       {
/*?*/           if(pRowTable[nRow]!=nRow)
/*?*/               return TRUE;
/*?*/       }
/*N*/   }
/*N*/   if(nTranslated==TRANS_COL)
/*N*/   {
/*?*/       for(long nCol=0;nCol<nColCnt;nCol++)
/*?*/       {
/*?*/           if(pColTable[nCol]!=nCol)
/*?*/               return TRUE;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if(nTranslated!=TRANS_NONE)
/*N*/   {
/*?*/       nTranslated=TRANS_NONE;
/*?*/       return FALSE;
/*N*/   }
/*N*/   return TRUE;
/*N*/
/*N*/ }

/*N*/ double SchMemChart::GetTransData(long nCol,long nRow)
/*N*/ {
/*N*/   DBG_ASSERT(VerifyTranslation(), "Translation table corrupted in MemChart");
/*N*/   return GetData( (short)pColTable[nCol], (short)pRowTable[nRow]);
/*N*/ }
/*N*/ double SchMemChart::GetTransDataInPercent(long nCol, long nRow, BOOL bRowData) const
/*N*/ {
/*N*/   DBG_ASSERT(((SchMemChart*)this)->VerifyTranslation(), "Translation table corrupted in MemChart");
/*N*/   return GetDataInPercent( (short)pColTable[nCol], (short)pRowTable[nRow], bRowData);
/*N*/ }
/*N*/ const String& SchMemChart::GetTransColText(long nCol) const
/*N*/ {
/*N*/   DBG_ASSERT(((SchMemChart*)this)->VerifyTranslation(), "Translation table corrupted in MemChart");
/*N*/   return GetColText( (short)pColTable[nCol] );
/*N*/ }
/*N*/ const String& SchMemChart::GetTransRowText(long nRow) const
/*N*/ {
/*N*/   DBG_ASSERT(((SchMemChart*)this)->VerifyTranslation(), "Translation table corrupted in MemChart");
/*N*/   return GetRowText( (short)pRowTable[nRow] );
/*N*/ }
/*N*/ long SchMemChart::GetTransNumFormatIdRow(const long nRow) const
/*N*/ {
/*N*/   DBG_ASSERT(((SchMemChart*)this)->VerifyTranslation(), "Translation table corrupted in MemChart");
/*N*/   return ( nTranslated == TRANS_ROW )? pRowNumFmtId[ pRowTable[ nRow ]]: pRowNumFmtId[ nRow ];
/*N*/ }
/*N*/ long SchMemChart::GetTransNumFormatIdCol(const long nCol) const
/*N*/ {
/*N*/   DBG_ASSERT(((SchMemChart*)this)->VerifyTranslation(), "Translation table corrupted in MemChart");
/*N*/   return ( nTranslated == TRANS_COL ) ? pColNumFmtId[ pColTable[ nCol ]]: pColNumFmtId[ nCol ];
/*N*/ }


//STRIP001 BOOL SchMemChart::SwapRowTranslation(long n1,long n2)
//STRIP001 {
//STRIP001  if(nTranslated==TRANS_COL)
//STRIP001  {
//STRIP001      DBG_ERROR("Chart: Invalid Reorganisation of Chart attempted");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  if(!(n1>=0 && n2>=0 && n1<nRowCnt && n2<nRowCnt))
//STRIP001  {
//STRIP001      DBG_ERROR("Chart: Invalid Reorganisation of Chart attempted, index error");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  long nTmp=pRowTable[n1];
//STRIP001  pRowTable[n1]=pRowTable[n2];
//STRIP001  pRowTable[n2]=nTmp;
//STRIP001
//STRIP001  nTranslated=TRANS_ROW;
//STRIP001
//STRIP001  VerifyTranslation(); //evtl. wurde mit dieser Aktion die Umordnung aufgehoben!
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001 BOOL SchMemChart::SwapColTranslation(long n1,long n2)
//STRIP001 {
//STRIP001  if(!(n1>=0 && n2>=0 && n1<nColCnt && n2<nColCnt))
//STRIP001  {
//STRIP001      DBG_ERROR("Chart: Invalid Reorganisation of Chart attempted, index error");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if(nTranslated==TRANS_ROW)
//STRIP001  {
//STRIP001      DBG_ERROR("Chart: Invalid Reorganisation of Chart attempted");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  long nTmp=pColTable[n1];
//STRIP001  pColTable[n1]=pColTable[n2];
//STRIP001  pColTable[n2]=nTmp;
//STRIP001
//STRIP001     //   The last swap might have returned the permutation back to identity.
//STRIP001     //   Test this and set the flag nTranslated accordingly.
//STRIP001  nTranslated=TRANS_NONE;
//STRIP001  for (long nCol=0; nCol<nColCnt; nCol++)
//STRIP001      if (pColTable[nCol] != nCol)
//STRIP001         {
//STRIP001          //  There is at least one moved column.
//STRIP001          nTranslated=TRANS_COL;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001  DBG_ASSERT(((SchMemChart*)this)->VerifyTranslation(),"Translation table corrupted in MemChart");
//STRIP001  return TRUE;
//STRIP001 }
/*************************************************************************
|*
|* Wie GetData, aber in Prozentwerten
|* Optimierungsvorschlag: fTotal fuer jede Zeile und Spalte buffern,
|*                        dazu muessen alle Schnittstellen bekannt sein,
|*                        die Daten am MemChart veraendern koennen.
|*
\************************************************************************/
/*N*/ double SchMemChart::GetDataInPercent(const short nCol , const short nRow, const BOOL bRowData) const
/*N*/ {
/*N*/    double fTotal=0.0,fTemp,fData;
/*N*/    short i;
/*N*/
/*N*/    fData = GetData(nCol,nRow);
/*N*/
/*N*/    if(bRowData)
/*N*/    {
/*N*/      for(i=0;i<nRowCnt;i++)
/*N*/      {
/*N*/          fTemp=GetData(nCol,i);
/*N*/
/*N*/          if(fTemp != DBL_MIN)   fTotal += fabs(fTemp);
/*N*/      }
/*N*/    }
/*N*/    else
/*N*/    {
/*N*/      for(i=0;i<nColCnt;i++)
/*N*/      {
/*N*/          fTemp=GetData(i,nRow);
/*N*/
/*N*/          if(fTemp != DBL_MIN)   fTotal += fabs(fTemp);
/*N*/      }
/*N*/
/*N*/    }
/*N*/    return fTotal ? ( (fabs(fData) / fTotal) * 100.0 ) : DBL_MIN;
/*N*/ }

/*************************************************************************
|*
|* Inserter fuer SvStream zum Speichern
|*
\************************************************************************/

/*N*/ SvStream& operator << (SvStream& rOut, const SchMemChart& rMemChart)
/*N*/ {
/*N*/   CharSet aSysCharSet = static_cast< CharSet >( ::GetSOStoreTextEncoding( gsl_getSystemTextEncoding(),
/*N*/                                                                             (USHORT)rOut.GetVersion()) );
/*N*/   rOut.SetStreamCharSet( aSysCharSet );
/*N*/
/*N*/   //Version 1: Abspeichern der pRow,pColTable (long-array)
/*N*/   SchIOCompat aIO(rOut, STREAM_WRITE, 2);
/*N*/
/*N*/   rOut << (INT16)rMemChart.nColCnt;
/*N*/   rOut << (INT16)rMemChart.nRowCnt;
/*N*/
/*N*/   double *pOut = rMemChart.pData;
/*N*/
/*N*/   short i;
/*N*/   for (i = 0; i < rMemChart.nColCnt; i++)
/*N*/       for (short j = 0; j < rMemChart.nRowCnt; j++)
/*N*/           rOut << *(pOut ++);
/*N*/
/*N*/   rOut << (INT16)aSysCharSet;
/*N*/   rOut << rMemChart.aMainTitle;
/*N*/   rOut << rMemChart.aSubTitle;
/*N*/   rOut << rMemChart.aXAxisTitle;
/*N*/   rOut << rMemChart.aYAxisTitle;
/*N*/   rOut << rMemChart.aZAxisTitle;
/*N*/
/*N*/   for (i = 0; i < rMemChart.nColCnt; i++)
/*N*/       rOut << rMemChart.pColText[ i ];
/*N*/
/*N*/   for (i = 0; i < rMemChart.nRowCnt; i++)
/*N*/       rOut << rMemChart.pRowText[ i ];
/*N*/
/*N*/   rOut << (INT16)rMemChart.eDataType;
/*N*/
/*N*/   //IOVersion = 1
/*N*/   long nIndex;
/*N*/   for (nIndex = 0; nIndex < rMemChart.nColCnt; nIndex++)
/*N*/       rOut << rMemChart.pColTable[nIndex];
/*N*/
/*N*/   for (nIndex = 0; nIndex < rMemChart.nRowCnt; nIndex++)
/*N*/       rOut << rMemChart.pRowTable[nIndex];
/*N*/
/*N*/   //IOVersion = 2
/*N*/   rOut << rMemChart.nTranslated;
/*N*/
/*N*/
/*N*/   return rOut;
/*N*/ }

/*************************************************************************
|*
|* Extractor fuer SvStream zum Laden
|*
\************************************************************************/

/*N*/ SvStream& operator >> (SvStream& rIn, SchMemChart& rMemChart)
/*N*/ {
/*N*/   INT16 nInt16;
/*N*/
/*N*/   SchIOCompat aIO(rIn, STREAM_READ);
/*N*/
/*N*/   rIn >> nInt16; rMemChart.nColCnt = (short)nInt16;
/*N*/   rIn >> nInt16; rMemChart.nRowCnt = (short)nInt16;
/*N*/
/*N*/   rMemChart.pData = new double[rMemChart.nColCnt * rMemChart.nRowCnt];
/*N*/
/*N*/   double *pIn = rMemChart.pData;
/*N*/
/*N*/   short i;
/*N*/   for (i = 0; i < rMemChart.nColCnt; i++)
/*N*/       for (short j = 0; j < rMemChart.nRowCnt; j++)
/*N*/           rIn >> *(pIn ++);
/*N*/
/*N*/   INT16 nCharSet;
/*N*/   rIn >> nCharSet;
/*N*/
/*N*/   rtl_TextEncoding aCharSet = ::GetSOLoadTextEncoding( static_cast< rtl_TextEncoding >( nCharSet ),
/*N*/                                                          (USHORT)rIn.GetVersion());
/*N*/     rIn.SetStreamCharSet( aCharSet );
/*N*/
/*N*/   rIn >> rMemChart.aMainTitle;
/*N*/   rIn >> rMemChart.aSubTitle;
/*N*/   rIn >> rMemChart.aXAxisTitle;
/*N*/   rIn >> rMemChart.aYAxisTitle;
/*N*/   rIn >> rMemChart.aZAxisTitle;
/*N*/
/*N*/   rMemChart.pColText = new String[rMemChart.nColCnt];
/*N*/
/*N*/   for (i = 0; i < rMemChart.nColCnt; i++)
/*N*/   {
/*N*/       rIn >> rMemChart.pColText[ i ];
/*N*/   }
/*N*/
/*N*/   rMemChart.pRowText = new String[rMemChart.nRowCnt];
/*N*/
/*N*/   for (i = 0; i < rMemChart.nRowCnt; i++)
/*N*/   {
/*N*/       rIn >> rMemChart.pRowText[ i ];
/*N*/   }
/*N*/
/*N*/   rIn >> nInt16; rMemChart.eDataType = (short)nInt16;
/*N*/
/*N*/   rMemChart.pRowNumFmtId  = new long [rMemChart.nRowCnt];
/*N*/   rMemChart.pColNumFmtId  = new long [rMemChart.nColCnt];
/*N*/   rMemChart.pRowTable     = new long [rMemChart.nRowCnt];
/*N*/   rMemChart.pColTable     = new long [rMemChart.nColCnt];
/*N*/
/*N*/   if(aIO.GetVersion()>=1)
/*N*/   {
/*N*/       long i;
/*N*/       for (i = 0; i < rMemChart.nColCnt; i++)
/*N*/           rIn >> rMemChart.pColTable[i];
/*N*/
/*N*/       for (i = 0; i < rMemChart.nRowCnt; i++)
/*N*/           rIn >> rMemChart.pRowTable[i];
/*N*/
/*N*/       if(aIO.GetVersion()>=2)
/*N*/           rIn >> rMemChart.nTranslated;
/*N*/
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       rMemChart.ResetTranslation(rMemChart.pRowTable,rMemChart.nRowCnt);
/*?*/       rMemChart.ResetTranslation(rMemChart.pColTable,rMemChart.nColCnt);
/*N*/   }
/*N*/
/*N*/   rMemChart.InitNumFmt(); //ab IOVersion 2 (ToDo:)
/*N*/
/*N*/   return rIn;
/*N*/ }

/*************************************************************************
|*
|* QuickSort ueber Spalten
|*
\************************************************************************/

//STRIP001 void SchMemChart::QuickSortTableCols (long l,long r,long nRow)
//STRIP001 {
//STRIP001  if (r > l)
//STRIP001  {
//STRIP001      double v = *(pData + r * nRowCnt + nRow);
//STRIP001      long   i = l - 1;
//STRIP001      long   j = r;
//STRIP001
//STRIP001      while (TRUE)
//STRIP001      {
//STRIP001          while (*(pData + (++ i) * nRowCnt + nRow) < v)
//STRIP001              ;
//STRIP001          while (*(pData + (-- j) * nRowCnt + nRow) > v)
//STRIP001              ;
//STRIP001
//STRIP001          if (i >= j) break;
//STRIP001          else SwapCols (i, j);
//STRIP001      }
//STRIP001
//STRIP001      if (i != r) SwapCols (i, r);
//STRIP001      QuickSortTableCols (l, i - 1, nRow);
//STRIP001      QuickSortTableCols (i + 1, r, nRow);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* QuickSort ueber Zeilen
|*
\************************************************************************/

//STRIP001 void SchMemChart::QuickSortTableRows (long l,long r,long nCol)
//STRIP001 {
//STRIP001  if (r > l)
//STRIP001  {
//STRIP001      double v = *(pData + r + nCol * nRowCnt);
//STRIP001      long   i = l - 1;
//STRIP001      long   j = r;
//STRIP001
//STRIP001      while (TRUE)
//STRIP001      {
//STRIP001          while (*(pData + (++ i) + nCol * nRowCnt) < v)
//STRIP001              ;
//STRIP001          while (*(pData + (-- j) + nCol * nRowCnt) > v)
//STRIP001              ;
//STRIP001
//STRIP001          if (i >= j) break;
//STRIP001          else SwapRows (i, j);
//STRIP001      }
//STRIP001
//STRIP001      if (i != r) SwapRows (i, r);
//STRIP001      QuickSortTableRows (l, i - 1, nCol);
//STRIP001      QuickSortTableRows (i + 1, r, nCol);
//STRIP001  }
//STRIP001 }

/*N*/ void SchMemChart::InitNumFmt()
/*N*/ {
/*N*/   long i;
/*N*/   for(i=0;i<nColCnt;i++)
/*N*/       pColNumFmtId[i]=-1; //uninitialised!
/*N*/
/*N*/   for(i=0;i<nRowCnt;i++)
/*N*/       pRowNumFmtId[i]=-1;
/*N*/ }

/*************************************************************************
|*
|* QuickSort ueber Spalten
|*
\************************************************************************/

//STRIP001 void SchMemChart::QuickSortCols(long l,long r,long nRow)
//STRIP001 {
//STRIP001  if (r > l)
//STRIP001  {
//STRIP001      double v = *(pData + r * nRowCnt + nRow);
//STRIP001      long   i = l - 1;
//STRIP001      long   j = r;
//STRIP001
//STRIP001      while (TRUE)
//STRIP001      {
//STRIP001          while (*(pData + (++ i) * nRowCnt + nRow) < v)
//STRIP001              ;
//STRIP001          while (*(pData + (-- j) * nRowCnt + nRow) > v)
//STRIP001              ;
//STRIP001
//STRIP001          if (i >= j) break;
//STRIP001          else
//STRIP001          {
//STRIP001              double temp = *(pData + i * nRowCnt + nRow);
//STRIP001              *(pData + i * nRowCnt + nRow) = *(pData + j * nRowCnt + nRow);
//STRIP001              *(pData + j * nRowCnt + nRow) = temp;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (i != r)
//STRIP001      {
//STRIP001          double temp = *(pData + r * nRowCnt + nRow);
//STRIP001          *(pData + r * nRowCnt + nRow) = *(pData + i * nRowCnt + nRow);
//STRIP001          *(pData + i * nRowCnt + nRow) = temp;
//STRIP001      }
//STRIP001
//STRIP001      QuickSortCols (l, i - 1, nRow);
//STRIP001      QuickSortCols (i + 1, r, nRow);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* QuickSort ueber Zeilen
|*
\************************************************************************/

//STRIP001 void SchMemChart::QuickSortRows (long l,
//STRIP001                               long r,
//STRIP001                               long nCol)
//STRIP001 {
//STRIP001  if (r > l)
//STRIP001  {
//STRIP001      double v = *(pData + r + nCol * nRowCnt);
//STRIP001      long   i = l - 1;
//STRIP001      long   j = r;
//STRIP001
//STRIP001      while (TRUE)
//STRIP001      {
//STRIP001          while (*(pData + (++ i) + nCol * nRowCnt) < v)
//STRIP001              ;
//STRIP001          while (*(pData + (-- j) + nCol * nRowCnt) > v)
//STRIP001              ;
//STRIP001
//STRIP001          if (i >= j) break;
//STRIP001          else
//STRIP001          {
//STRIP001              double temp = *(pData + i + nCol * nRowCnt);
//STRIP001              *(pData + i + nCol * nRowCnt) = *(pData + j + nCol * nRowCnt);
//STRIP001              *(pData + j + nCol * nRowCnt) = temp;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (i != r)
//STRIP001      {
//STRIP001          double temp = *(pData + r + nCol * nRowCnt);
//STRIP001          *(pData + r + nCol * nRowCnt) = *(pData + i + nCol * nRowCnt);
//STRIP001          *(pData + i + nCol * nRowCnt) = temp;
//STRIP001      }
//STRIP001
//STRIP001      QuickSortRows (l, i - 1, nCol);
//STRIP001      QuickSortRows (i + 1, r, nCol);
//STRIP001  }
//STRIP001 }

/*N*/ String SchMemChart::GetDefaultColumnText( sal_Int32 nCol ) const
/*N*/ {
/*N*/   if( !mpColNameBuffer )
/*N*/   {
/*N*/       // initialize resource string
/*N*/       mpColNameBuffer = new String[ 2 ];
/*N*/       DBG_ASSERT( mpColNameBuffer, "couldn't create two strings!" );
/*N*/       String aResStr( SchResId( STR_COLUMN ));
/*N*/       xub_StrLen nPos = aResStr.SearchAscii( "$(N)" );
/*N*/       if( nPos != STRING_NOTFOUND )
/*N*/       {
/*N*/           mpColNameBuffer[ 0 ] = String( aResStr, 0, nPos );
/*N*/           mpColNameBuffer[ 1 ] = String( aResStr, nPos + sizeof( "$(N)" ) - 1, STRING_LEN );
/*N*/       }
/*N*/       else
/*?*/           mpColNameBuffer[ 0 ] = aResStr;
/*N*/   }
/*N*/
/*N*/   if( mpColNameBuffer )
/*N*/   {
/*N*/       String aResult( mpColNameBuffer[ 0 ] );
/*N*/       aResult.Append( String::CreateFromInt32( nCol + 1 ));
/*N*/       aResult.Append( mpColNameBuffer[ 1 ] );
/*N*/       return aResult;
/*N*/   }
/*N*/   else
/*?*/       return String();
/*N*/ }

/*N*/ String SchMemChart::GetDefaultRowText( sal_Int32 nRow ) const
/*N*/ {
/*N*/   if( !mpRowNameBuffer )
/*N*/   {
/*N*/       // initialize resource string
/*N*/       mpRowNameBuffer = new String[ 2 ];
/*N*/       DBG_ASSERT( mpRowNameBuffer, "couldn't create two strings!" );
/*N*/       String aResStr( SchResId( STR_ROW ));
/*N*/       xub_StrLen nPos = aResStr.SearchAscii( "$(N)" );
/*N*/       if( nPos != STRING_NOTFOUND )
/*N*/       {
/*N*/           mpRowNameBuffer[ 0 ] = String( aResStr, 0, nPos );
/*N*/           mpRowNameBuffer[ 1 ] = String( aResStr, nPos + sizeof( "$(N)" ) - 1, STRING_LEN );
/*N*/       }
/*N*/       else
/*?*/           mpRowNameBuffer[ 0 ] = aResStr;
/*N*/   }
/*N*/
/*N*/   if( mpRowNameBuffer )
/*N*/   {
/*N*/       String aResult( mpRowNameBuffer[ 0 ] );
/*N*/       aResult.Append( String::CreateFromInt32( nRow + 1 ));
/*N*/       aResult.Append( mpRowNameBuffer[ 1 ] );
/*N*/       return aResult;
/*N*/   }
/*N*/   else
/*?*/       return String();
/*N*/ }

using namespace com::sun::star;

// ========================================

/*N*/ ::rtl::OUStringBuffer SchMemChart::getXMLStringForCellAddress( const SchCellAddress& rCell )
/*N*/ {
/*N*/     ::rtl::OUStringBuffer aBuffer;
/*N*/     ::std::vector< SchSingleCell >::const_iterator aIter;
/*N*/     const ::std::vector< SchSingleCell >::const_iterator aEndIter = rCell.maCells.end();
/*N*/
/*N*/     for( aIter = rCell.maCells.begin(); aIter != aEndIter; aIter++ )
/*N*/     {
/*N*/         sal_Int32 nCol = aIter->mnColumn;
/*N*/         aBuffer.append( (sal_Unicode)'.' );
/*N*/         if( ! aIter->mbRelativeColumn )
/*N*/             aBuffer.append( (sal_Unicode)'$' );
/*N*/
/*N*/         // get A, B, C, ..., AA, AB, ... representation of column number
/*N*/         if( nCol < 26 )
/*N*/             aBuffer.append( (sal_Unicode)('A' + nCol) );
/*N*/         else if( nCol < 702 )
/*N*/         {
/*?*/             aBuffer.append( (sal_Unicode)('A' + nCol / 26 - 1 ));
/*?*/             aBuffer.append( (sal_Unicode)('A' + nCol % 26) );
/*N*/         }
/*N*/         else    // works for nCol <= 18,278
/*N*/         {
/*?*/             aBuffer.append( (sal_Unicode)('A' + nCol / 702 - 1 ));
/*?*/             aBuffer.append( (sal_Unicode)('A' + (nCol % 702) / 26 ));
/*?*/             aBuffer.append( (sal_Unicode)('A' + nCol % 26) );
/*N*/         }
/*N*/
/*N*/         // write row number as number
/*N*/         if( ! aIter->mbRelativeRow )
/*N*/             aBuffer.append( (sal_Unicode)'$' );
/*N*/         aBuffer.append( aIter->mnRow + (sal_Int32)1 );
/*N*/     }
/*N*/
/*N*/     return aBuffer;
/*N*/ }

//STRIP001 void SchMemChart::getSingleCellAddressFromXMLString(
//STRIP001     const ::rtl::OUString& rXMLString,
//STRIP001     sal_Int32 nStartPos, sal_Int32 nEndPos,
//STRIP001     SchSingleCell& rSingleCell )
//STRIP001 {
//STRIP001     // expect "\$?[a-zA-Z]+\$?[1-9][0-9]*"
//STRIP001     static const sal_Unicode aDollar( '$' );
//STRIP001     static const sal_Unicode aLetterA( 'A' );
//STRIP001
//STRIP001     ::rtl::OUString aCellStr = rXMLString.copy( nStartPos, nEndPos - nStartPos + 1 ).toAsciiUpperCase();
//STRIP001     const sal_Unicode* pStrArray = aCellStr.getStr();
//STRIP001     sal_Int32 nLength = aCellStr.getLength();
//STRIP001     sal_Int32 i = nLength - 1, nColumn = 0;
//STRIP001
//STRIP001     // parse number for row
//STRIP001     while( CharClass::isAsciiDigit( pStrArray[ i ] ) && i >= 0 )
//STRIP001         i--;
//STRIP001     rSingleCell.mnRow = (aCellStr.copy( i + 1 )).toInt32() - 1;
//STRIP001     // a dollar in XML means absolute (whereas in UI it means relative)
//STRIP001     if( pStrArray[ i ] == aDollar )
//STRIP001     {
//STRIP001         i--;
//STRIP001         rSingleCell.mbRelativeRow = sal_False;
//STRIP001     }
//STRIP001     else
//STRIP001         rSingleCell.mbRelativeRow = sal_True;
//STRIP001
//STRIP001     // parse rest for column
//STRIP001     sal_Int32 nPower = 1;
//STRIP001     while( CharClass::isAsciiAlpha( pStrArray[ i ] ))
//STRIP001     {
//STRIP001         nColumn += (pStrArray[ i ] - aLetterA + 1) * nPower;
//STRIP001         i--;
//STRIP001         nPower *= 26;
//STRIP001     }
//STRIP001     rSingleCell.mnColumn = nColumn - 1;
//STRIP001
//STRIP001     rSingleCell.mbRelativeColumn = sal_True;
//STRIP001     if( i >= 0 &&
//STRIP001         pStrArray[ i ] == aDollar )
//STRIP001         rSingleCell.mbRelativeColumn = sal_False;
//STRIP001 }

//STRIP001 bool SchMemChart::getCellAddressFromXMLString(
//STRIP001     const ::rtl::OUString& rXMLString,
//STRIP001     sal_Int32 nStartPos, sal_Int32 nEndPos,
//STRIP001     SchCellAddress& rOutCell,
//STRIP001     ::rtl::OUString& rOutTableName )
//STRIP001 {
//STRIP001     static const sal_Unicode aDot( '.' );
//STRIP001     static const sal_Unicode aQuote( '\'' );
//STRIP001     static const sal_Unicode aBackslash( '\\' );
//STRIP001
//STRIP001     sal_Int32 nNextDelimiterPos = nStartPos;
//STRIP001
//STRIP001     sal_Int32 nDelimiterPos = nStartPos;
//STRIP001     bool bInQuotation = false;
//STRIP001     // parse table name
//STRIP001     while( nDelimiterPos < nEndPos &&
//STRIP001            ( bInQuotation || rXMLString[ nDelimiterPos ] != aDot ))
//STRIP001     {
//STRIP001         // skip escaped characters (with backslash)
//STRIP001         if( rXMLString[ nDelimiterPos ] == aBackslash )
//STRIP001             ++nDelimiterPos;
//STRIP001         // toggle quotation mode when finding single quotes
//STRIP001         else if( rXMLString[ nDelimiterPos ] == aQuote )
//STRIP001             bInQuotation = ! bInQuotation;
//STRIP001
//STRIP001         ++nDelimiterPos;
//STRIP001     }
//STRIP001
//STRIP001     if( nDelimiterPos == -1 ||
//STRIP001         nDelimiterPos >= nEndPos )
//STRIP001     {
//STRIP001 #ifdef DBG_UTIL
//STRIP001         String aStr( rXMLString.copy( nStartPos, nEndPos - nStartPos + 1 ));
//STRIP001         ByteString aBstr( aStr, RTL_TEXTENCODING_ASCII_US );
//STRIP001         DBG_ERROR1( "Invalid Cell Address <%s> found in XML file", aBstr.GetBuffer());
//STRIP001 #endif
//STRIP001         return false;
//STRIP001     }
//STRIP001     if( nDelimiterPos > nStartPos )
//STRIP001     {
//STRIP001         // there is a table name before the address
//STRIP001
//STRIP001         ::rtl::OUStringBuffer aTableNameBuffer;
//STRIP001         const sal_Unicode * pTableName = rXMLString.getStr();
//STRIP001
//STRIP001         // remove escapes from table name
//STRIP001         ::std::for_each( pTableName + nStartPos,
//STRIP001                          pTableName + nDelimiterPos,
//STRIP001                          lcl_UnEscape( aTableNameBuffer ));
//STRIP001
//STRIP001         // unquote quoted table name
//STRIP001         const sal_Unicode * pBuf = aTableNameBuffer.getStr();
//STRIP001         if( pBuf[ 0 ] == aQuote &&
//STRIP001             pBuf[ aTableNameBuffer.getLength() - 1 ] == aQuote )
//STRIP001         {
//STRIP001             ::rtl::OUString aName = aTableNameBuffer.makeStringAndClear();
//STRIP001             rOutTableName = aName.copy( 1, aName.getLength() - 2 );
//STRIP001         }
//STRIP001         else
//STRIP001             rOutTableName = aTableNameBuffer.makeStringAndClear();
//STRIP001     }
//STRIP001
//STRIP001     for( sal_Int32 i = 0;
//STRIP001          nNextDelimiterPos < nEndPos;
//STRIP001          nDelimiterPos = nNextDelimiterPos, i++ )
//STRIP001     {
//STRIP001         nNextDelimiterPos = rXMLString.indexOf( aDot, nDelimiterPos + 1 );
//STRIP001         if( nNextDelimiterPos == -1 ||
//STRIP001             nNextDelimiterPos > nEndPos )
//STRIP001             nNextDelimiterPos = nEndPos + 1;
//STRIP001
//STRIP001         rOutCell.maCells.resize( i + 1 );
//STRIP001         getSingleCellAddressFromXMLString( rXMLString,
//STRIP001                                            nDelimiterPos + 1, nNextDelimiterPos - 1,
//STRIP001                                            rOutCell.maCells[ i ] );
//STRIP001     }
//STRIP001
//STRIP001     return true;
//STRIP001 }

/*N*/ bool SchMemChart::getCellRangeAddressFromXMLString(
/*N*/     const ::rtl::OUString& rXMLString,
/*N*/     sal_Int32 nStartPos, sal_Int32 nEndPos,
/*N*/     SchCellRangeAddress& rOutRange )
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     bool bResult = true;
//STRIP001     static const sal_Unicode aColon( ':' );
//STRIP001     static const sal_Unicode aQuote( '\'' );
//STRIP001     static const sal_Unicode aBackslash( '\\' );
//STRIP001
//STRIP001     sal_Int32 nDelimiterPos = nStartPos;
//STRIP001     bool bInQuotation = false;
//STRIP001     // parse table name
//STRIP001     while( nDelimiterPos < nEndPos &&
//STRIP001            ( bInQuotation || rXMLString[ nDelimiterPos ] != aColon ))
//STRIP001     {
//STRIP001         // skip escaped characters (with backslash)
//STRIP001         if( rXMLString[ nDelimiterPos ] == aBackslash )
//STRIP001             ++nDelimiterPos;
//STRIP001         // toggle quotation mode when finding single quotes
//STRIP001         else if( rXMLString[ nDelimiterPos ] == aQuote )
//STRIP001             bInQuotation = ! bInQuotation;
//STRIP001
//STRIP001         ++nDelimiterPos;
//STRIP001     }
//STRIP001
//STRIP001     if( nDelimiterPos <= nStartPos ||              // includes == and 'not found' (==-1)
//STRIP001         nDelimiterPos >= nEndPos )
//STRIP001     {
//STRIP001 #if OSL_DEBUG_LEVEL > 0
//STRIP001         String aStr( rXMLString.copy( nStartPos, nEndPos - nStartPos + 1 ));
//STRIP001         ByteString aBstr( aStr, RTL_TEXTENCODING_ASCII_US );
//STRIP001         DBG_ERROR1( "Invalid Cell Range <%s> found in XML file", aBstr.GetBuffer());
//STRIP001 #endif
//STRIP001         return false;
//STRIP001     }
//STRIP001     bResult = getCellAddressFromXMLString( rXMLString, nStartPos, nDelimiterPos - 1,
//STRIP001                                            rOutRange.maUpperLeft,
//STRIP001                                            rOutRange.msTableName );
//STRIP001     ::rtl::OUString sTableSecondName;
//STRIP001     if( bResult )
//STRIP001     {
//STRIP001         bResult = getCellAddressFromXMLString( rXMLString, nDelimiterPos + 1, nEndPos,
//STRIP001                                                rOutRange.maLowerRight,
//STRIP001                                                sTableSecondName );
//STRIP001     }
//STRIP001     DBG_ASSERT( sTableSecondName.getLength() == 0 ||
//STRIP001                 sTableSecondName.equals( rOutRange.msTableName ),
//STRIP001                 "Cell Range must be inside the same sheet" );
//STRIP001     return bResult;
/*N*/ }

/// interpret maChartRange and fill XML string with that
/*N*/ ::rtl::OUString SchMemChart::getXMLStringForChartRange()
/*N*/ {
/*N*/     static const sal_Unicode aSpace( ' ' );
/*N*/     static const sal_Unicode aQuote( '\'' );
/*N*/
/*N*/     ::rtl::OUStringBuffer aBuffer;
/*N*/     ::std::vector< SchCellRangeAddress >::iterator aIter;
/*N*/     const ::std::vector< SchCellRangeAddress >::iterator aEndIter = maChartRange.maRanges.end();
/*N*/
/*N*/     for( aIter = maChartRange.maRanges.begin(); aIter != aEndIter; /* increment done in body */ )
/*N*/     {
/*?*/         if( (aIter->msTableName).getLength())
/*?*/         {
/*?*/             bool bNeedsEscaping = ( aIter->msTableName.indexOf( aQuote ) > -1 );
/*?*/             bool bNeedsQuoting = bNeedsEscaping || ( aIter->msTableName.indexOf( aSpace ) > -1 );
/*?*/
/*?*/             // quote table name if it contains spaces or quotes
/*?*/             if( bNeedsQuoting )
/*?*/             {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                 // leading quote
//STRIP001 /*?*/                 aBuffer.append( aQuote );
//STRIP001 /*?*/
//STRIP001 /*?*/                 // escape existing quotes
//STRIP001 /*?*/                 if( bNeedsEscaping )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     const sal_Unicode * pTableNameBeg = aIter->msTableName.getStr();
//STRIP001 /*?*/
//STRIP001 /*?*/                     // append the quoted string at the buffer
//STRIP001 /*?*/                     ::std::for_each( pTableNameBeg,
//STRIP001 /*?*/                                      pTableNameBeg + aIter->msTableName.getLength(),
//STRIP001 /*?*/                                      lcl_Escape( aBuffer ) );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                     aBuffer.append( aIter->msTableName );
//STRIP001 /*?*/
//STRIP001 /*?*/                 // final quote
//STRIP001 /*?*/                 aBuffer.append( aQuote );
/*?*/             }
/*?*/             else
/*?*/                 aBuffer.append( aIter->msTableName );
/*?*/         }
/*?*/         aBuffer.append( getXMLStringForCellAddress( aIter->maUpperLeft ));
/*?*/
/*?*/         if( aIter->maLowerRight.maCells.size())
/*?*/         {
/*?*/             // we have a range (not a single cell)
/*?*/             aBuffer.append( sal_Unicode( ':' ));
/*?*/             aBuffer.append( getXMLStringForCellAddress( aIter->maLowerRight ));
/*?*/         }
/*?*/
/*?*/         aIter++;
/*?*/         // separator for more than one range
/*?*/         if( aIter != aEndIter )
/*?*/             aBuffer.append( sal_Unicode( ' ' ));
/*N*/     }
/*N*/
/*N*/     return aBuffer.makeStringAndClear();
/*N*/ }

/// parse String and put results into maChartRange
/*N*/ void SchMemChart::getChartRangeForXMLString( const ::rtl::OUString& rXMLString )
/*N*/ {
/*N*/     static const sal_Unicode aSpace( ' ' );
/*N*/     static const sal_Unicode aQuote( '\'' );
/*N*/     static const sal_Unicode aDoubleQuote( '\"' );
/*N*/     static const sal_Unicode aDollar( '$' );
/*N*/     static const sal_Unicode aBackslash( '\\' );
/*N*/
/*N*/     sal_Int32 nStartPos = 0;
/*N*/     sal_Int32 nEndPos = nStartPos;
/*N*/     const sal_Int32 nLength = rXMLString.getLength();
/*N*/
/*N*/     // reset
/*N*/     maChartRange.maRanges.clear();
/*N*/
/*N*/     // iterate over different ranges
/*N*/     for( sal_Int32 i = 0;
/*N*/          nEndPos < nLength;
/*N*/          nStartPos = ++nEndPos, i++ )
/*N*/     {
/*N*/         // find start point of next range
/*N*/
/*N*/         // ignore leading '$'
/*N*/         if( rXMLString[ nEndPos ] == aDollar)
/*N*/             nEndPos++;
/*N*/
/*N*/         bool bInQuotation = false;
/*N*/         // parse range
/*N*/         while( nEndPos < nLength &&
/*N*/                ( bInQuotation || rXMLString[ nEndPos ] != aSpace ))
/*N*/         {
/*N*/             // skip escaped characters (with backslash)
/*N*/             if( rXMLString[ nEndPos ] == aBackslash )
/*N*/                 ++nEndPos;
/*N*/             // toggle quotation mode when finding single quotes
/*N*/             else if( rXMLString[ nEndPos ] == aQuote )
/*N*/                 bInQuotation = ! bInQuotation;
/*N*/
/*N*/             ++nEndPos;
/*N*/         }
/*N*/
/*N*/         maChartRange.maRanges.resize( i + 1 );
/*N*/         if( ! getCellRangeAddressFromXMLString(
/*N*/                 rXMLString,
/*N*/                 nStartPos, nEndPos - 1,
/*N*/                 maChartRange.maRanges[ i ] ))
/*N*/         {
/*N*/             // if an error occured, bail out
/*N*/             maChartRange.maRanges.clear();
/*N*/             break;
/*N*/         }
/*N*/     }
/*N*/
/*N*/ #if OSL_DEBUG_LEVEL > 0
/*N*/     // output result
/*N*/     OSL_TRACE(
/*N*/         ::rtl::OUStringToOString(
/*N*/             ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Ranges retrieved from XML-String: \"" )) +
/*N*/             rXMLString +
/*N*/             ::rtl::OUString( sal_Unicode( '\"' )),
/*N*/             RTL_TEXTENCODING_ASCII_US ).getStr() );
/*N*/     OSL_TRACE( "Size: %d", maChartRange.maRanges.size() );
/*N*/     for( ::std::vector< SchCellRangeAddress >::const_iterator aIter = maChartRange.maRanges.begin();
/*N*/          aIter != maChartRange.maRanges.end();
/*N*/          ++aIter )
/*N*/     {
/*N*/         OSL_TRACE( " Cell Address found:" );
/*N*/         OSL_TRACE( "  Upper-Left: " );
/*N*/         for( ::std::vector< SchSingleCell >::const_iterator aIter2 = (*aIter).maUpperLeft.maCells.begin();
/*N*/              aIter2 != (*aIter).maUpperLeft.maCells.end();
/*N*/              ++aIter2 )
/*N*/         {
/*N*/             OSL_TRACE( "  Column: %d, Row: %d,  Rel-Col: %s, Rel-Row: %s",
/*N*/                        (*aIter2).mnColumn, (*aIter2).mnRow,
/*N*/                        (*aIter2).mbRelativeColumn ? "true" : "false",
/*N*/                        (*aIter2).mbRelativeRow ? "true" : "false" );
/*N*/         }
/*N*/         OSL_TRACE( "  Lower-Right: " );
/*N*/         for( ::std::vector< SchSingleCell >::const_iterator aIter3 = (*aIter).maLowerRight.maCells.begin();
/*N*/              aIter3 != (*aIter).maLowerRight.maCells.end();
/*N*/              ++aIter3 )
/*N*/         {
/*N*/             OSL_TRACE( "  Column: %d, Row: %d,  Rel-Col: %s, Rel-Row: %s",
/*N*/                        (*aIter3).mnColumn, (*aIter3).mnRow,
/*N*/                        (*aIter3).mbRelativeColumn ? "true" : "false",
/*N*/                        (*aIter3).mbRelativeRow ? "true" : "false" );
/*N*/         }
/*N*/         OSL_TRACE(
/*N*/             ::rtl::OUStringToOString(
/*N*/                 ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "  Table-Name: \"" )) +
/*N*/                 (*aIter).msTableName +
/*N*/                 ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "\", Number: " )) +
/*N*/                 ::rtl::OUString::valueOf( (*aIter).mnTableNumber ),
/*N*/                 RTL_TEXTENCODING_ASCII_US ).getStr() );
/*N*/     }
/*N*/ #endif
/*N*/ }

/** this is needed for export of charts embedded in calc
    for saving an XML document in old binary format
*/
/*N*/ ::rtl::OUString SchMemChart::createTableNumberList()
/*N*/ {
/*N*/     ::rtl::OUStringBuffer aBuffer;
/*N*/     ::std::vector< SchCellRangeAddress >::iterator aIter;
/*N*/     const ::std::vector< SchCellRangeAddress >::iterator aEndIter = maChartRange.maRanges.end();
/*N*/     sal_Bool bStarted = sal_False;
/*N*/
/*N*/     for( aIter = maChartRange.maRanges.begin(); aIter != aEndIter; aIter++ )
/*N*/     {
/*N*/         if( aIter->mnTableNumber != -1 )
/*N*/         {
/*N*/             if( bStarted )
/*?*/                 aBuffer.append( (sal_Unicode)' ' );
/*N*/             else
/*N*/                 bStarted = sal_True;
/*N*/
/*N*/             aBuffer.append( aIter->mnTableNumber );
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return aBuffer.makeStringAndClear();
/*N*/ }

// prerequisite: maChartRange must be set and have the correct dimension
// for all table numbers to fit in
/*N*/ void SchMemChart::parseTableNumberList( const ::rtl::OUString& aList )
/*N*/ {
/*N*/     static const sal_Unicode aSpace( ' ' );
/*N*/     sal_Int32 nChartRangeSize = maChartRange.maRanges.size();
/*N*/     sal_Int32 nStartPos = 0, nEndPos;
/*N*/     sal_Int32 nLength = aList.getLength();
/*N*/     sal_Int32 nRangeNumber = 0;
/*N*/
/*N*/     while( nStartPos < nLength )
/*N*/     {
/*N*/         nEndPos = aList.indexOf( aSpace, nStartPos );
/*N*/         if( nEndPos == -1 )
/*N*/             nEndPos = nLength;
/*N*/
/*N*/         if( nStartPos != nEndPos ) // there were more than one space
/*N*/         {
/*N*/             if( nRangeNumber < nChartRangeSize )
/*N*/             {
/*N*/                 maChartRange.maRanges[ nRangeNumber++ ].mnTableNumber =
/*N*/                     aList.copy( nStartPos, (nEndPos - nStartPos)).toInt32();
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 DBG_ERROR( "SchMemChart::parseTableNumberList: Too many table numbers for chart range" );
/*N*/             }
/*N*/         }
/*N*/
/*N*/         nStartPos = nEndPos + 1;
/*N*/     }
/*N*/ }


// methods to modify SchChartRange
// -------------------------------

/*N*/ static sal_Int32 lcl_GetWriterBoxNum( String& rStr, BOOL bFirst )
/*N*/ {
/*N*/   sal_Int32 nRet = 0;
/*N*/   xub_StrLen nPos = 0;
/*N*/   if( bFirst )
/*N*/   {
/*N*/       // the first box starts with a letter
/*N*/       sal_Unicode cChar;
/*N*/       BOOL bFirst = TRUE;
/*N*/       while( 0 != ( cChar = rStr.GetChar( nPos )) &&
/*N*/              ( (cChar >= 'A' && cChar <= 'Z') ||
/*N*/                (cChar >= 'a' && cChar <= 'z') ) )
/*N*/       {
/*N*/           if( (cChar -= 'A') >= 26 )
/*N*/               cChar -= 'a' - '[';
/*N*/           if( bFirst )
/*N*/               bFirst = FALSE;
/*N*/           else
/*N*/               ++nRet;
/*N*/           nRet = nRet * 52 + cChar;
/*N*/           ++nPos;
/*N*/       }
/*N*/       rStr.Erase( 0, nPos );      // remove the read characters
/*N*/   }
/*N*/   else if( STRING_NOTFOUND == ( nPos = rStr.Search( ':' ) ))
/*N*/   {
/*N*/       nRet = rStr.ToInt32();
/*N*/       rStr.Erase();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nRet = rStr.Copy( 0, nPos ).ToInt32();
/*N*/       rStr.Erase( 0, nPos+1 );
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*N*/ static void lcl_GetWriterTblBox( const String& rStr,
/*N*/                               SchCellAddress& rToFill )
/*N*/ {
/*N*/   BOOL bFirst = TRUE;
/*N*/   String sNm( rStr );
/*N*/   while( sNm.Len() )
/*N*/   {
/*N*/       SchSingleCell aCell;
/*N*/       aCell.mnColumn = ::lcl_GetWriterBoxNum( sNm, bFirst );
/*N*/       bFirst = FALSE;
/*N*/       aCell.mnRow = ::lcl_GetWriterBoxNum( sNm, bFirst );
/*N*/       rToFill.maCells.push_back( aCell );
/*N*/   }
/*N*/ }

/*N*/ String lcl_GetWriterBoxName( const SchCellAddress& rCell )
/*N*/ {
/*N*/   String sNm;
/*N*/
/*N*/     ::std::vector< SchSingleCell >::const_iterator aIter = rCell.maCells.begin();
/*N*/     const ::std::vector< SchSingleCell >::const_iterator aEnd = rCell.maCells.end();
/*N*/   BOOL bFirst = TRUE;
/*N*/   for( ; aIter != aEnd; aIter++ )
/*N*/   {
/*N*/       String sTmp( String::CreateFromInt32( aIter->mnRow ));
/*N*/       if( sNm.Len() )
/*N*/           sNm.Insert( '.', 0 ).Insert( sTmp, 0 );
/*N*/       else
/*N*/           sNm = sTmp;
/*N*/
/*N*/       if( bFirst )
/*N*/       {
/*N*/           const sal_Int32 coDiff = 52;    // 'A'-'Z' 'a' - 'z'
/*N*/           register sal_Int32 nCalc, nCol = aIter->mnColumn;
/*N*/
/*N*/           do {
/*N*/               nCalc = nCol % coDiff;
/*N*/               if( nCalc >= 26 )
/*N*/                   sNm.Insert( sal_Unicode('a' - 26 + nCalc ), 0 );
/*N*/               else
/*N*/                   sNm.Insert( sal_Unicode('A' + nCalc ), 0 );
/*N*/
/*N*/               if( !(nCol -= nCalc) )
/*N*/                   break;
/*N*/               nCol /= coDiff;
/*N*/               --nCol;
/*N*/           } while( 1 );
/*N*/           bFirst = FALSE;
/*N*/       }
/*N*/       else
/*N*/           sNm.Insert( '.', 0 ).Insert(
/*N*/                       String::CreateFromInt32( aIter->mnColumn ), 0 );
/*N*/   }
/*N*/   return sNm;
/*N*/ }


/// convert SomeData string(s) to SchChartRange and vice versa for Writer
/*N*/ void SchMemChart::ConvertChartRangeForWriter( BOOL bOldToNew )
/*N*/ {
/*N*/     if( bOldToNew )     // convert SomeData1 to SchChartRange
/*N*/     {
/*N*/       SchChartRange aRange;
/*N*/       if( 2 < aSomeData1.Len() )
/*N*/       {
/*N*/           // spitze Klammern am Anfang & Ende enfernen
/*N*/           String sBox( aSomeData1 );
/*N*/           if( '<' == sBox.GetChar( 0  ) ) sBox.Erase( 0, 1 );
/*N*/           if( '>' == sBox.GetChar( sBox.Len()-1  ) ) sBox.Erase( sBox.Len()-1 );
/*N*/
/*N*/           xub_StrLen nTrenner = sBox.Search( ':' );
/*N*/           DBG_ASSERT( STRING_NOTFOUND != nTrenner, "no valid selection" );
/*N*/
/*N*/           SchCellRangeAddress aCRA;
/*N*/           ::lcl_GetWriterTblBox( sBox.Copy( 0, nTrenner ), aCRA.maUpperLeft );
/*N*/           ::lcl_GetWriterTblBox( sBox.Copy( nTrenner+1 ), aCRA.maLowerRight );
/*N*/           aRange.maRanges.push_back( aCRA );
/*N*/       }
/*N*/       if( aSomeData2.Len() )
/*N*/       {
/*N*/           aRange.mbFirstRowContainsLabels = '1' == aSomeData2.GetChar(0);
/*N*/           aRange.mbFirstColumnContainsLabels = '1' == aSomeData2.GetChar(1);
/*N*/       }
/*N*/       SetChartRange( aRange );
/*N*/     }
/*N*/     else                // convert SchChartRange to SomeData1
/*N*/     {
/*N*/       String sData1, sData2;
/*N*/       const SchChartRange& rRg = GetChartRange();
/*N*/       if( rRg.maRanges.size() )
/*N*/       {
/*N*/           ::std::vector< SchCellRangeAddress >::const_iterator
/*N*/                                               aIter = rRg.maRanges.begin();
/*N*/           sData1.Assign( '<' )
/*N*/                 .Append( ::lcl_GetWriterBoxName( aIter->maUpperLeft ))
/*N*/                 .Append( ':' )
/*N*/                 .Append( ::lcl_GetWriterBoxName( aIter->maLowerRight ))
/*N*/                 .Append( '>' );
/*N*/
/*N*/           sData2.Assign( rRg.mbFirstRowContainsLabels ? '1' : '0' )
/*N*/                 .Append( rRg.mbFirstColumnContainsLabels ? '1' : '0' );
/*N*/       }
/*N*/       aSomeData1 = sData1;
/*N*/       aSomeData2 = sData2;
/*N*/     }
/*N*/ }

/// convert SomeData string(s) to SchChartRange and vice versa for Calc
//STRIP001 void SchMemChart::ConvertChartRangeForCalc( BOOL bOldToNew )
//STRIP001 {
//STRIP001     if( bOldToNew )
//STRIP001     {   // convert SomeData1/2/3 to SchChartRange
//STRIP001         DBG_ASSERT( SomeData1().Len() && SomeData2().Len() && SomeData3().Len(),
//STRIP001             "ConvertChartRangeForCalc: can't convert old to new" );
//STRIP001         SchChartRange aChartRange;
//STRIP001      const sal_Unicode cTok = ';';
//STRIP001      xub_StrLen nToken;
//STRIP001         String aPos = SomeData1();
//STRIP001      if ( (nToken = aPos.GetTokenCount( cTok )) >= 5)
//STRIP001      {
//STRIP001             aChartRange.mbKeepCopyOfData = sal_False;
//STRIP001             String aOpt = SomeData2();
//STRIP001          xub_StrLen nOptToken = aOpt.GetTokenCount( cTok );
//STRIP001             BOOL bNewChart = (nOptToken >= 4);      // as of 341/342
//STRIP001             DBG_ASSERT( SomeData3().Len(), "ConvertChartRangeForCalc: no sheet names" );
//STRIP001             String aSheetNames = SomeData3();       // as of 638m
//STRIP001          USHORT nCol1, nRow1, nTab1, nCol2, nRow2, nTab2;
//STRIP001          xub_StrLen nInd = 0;
//STRIP001             xub_StrLen nSheetInd = 0;
//STRIP001          for ( xub_StrLen j=0; j < nToken; j+=5 )
//STRIP001          {
//STRIP001              xub_StrLen nInd2 = nInd;
//STRIP001              nTab1 = (USHORT) aPos.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001                 // To make old versions (<341/342) skip it, the token separator
//STRIP001                 // is a ','
//STRIP001              if ( bNewChart )
//STRIP001                  nTab2 = (USHORT) aPos.GetToken( 1, ',', nInd2 ).ToInt32();
//STRIP001              else
//STRIP001                  nTab2 = nTab1;
//STRIP001              nCol1 = (USHORT) aPos.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001              nRow1 = (USHORT) aPos.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001              nCol2 = (USHORT) aPos.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001              nRow2 = (USHORT) aPos.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001                 for ( USHORT nTab = nTab1; nTab <= nTab2; ++nTab )
//STRIP001                 {
//STRIP001                     SchCellRangeAddress aCellRangeAddress;
//STRIP001                     SchSingleCell aCell;
//STRIP001                     aCell.mnColumn = nCol1;
//STRIP001                     aCell.mnRow = nRow1;
//STRIP001                     aCellRangeAddress.maUpperLeft.maCells.push_back( aCell );
//STRIP001                     aCell.mnColumn = nCol2;
//STRIP001                     aCell.mnRow = nRow2;
//STRIP001                     aCellRangeAddress.maLowerRight.maCells.push_back( aCell );
//STRIP001                     aCellRangeAddress.mnTableNumber = nTab;
//STRIP001                     String aName( aSheetNames.GetToken( 0, cTok, nSheetInd ) );
//STRIP001                     aCellRangeAddress.msTableName = aName;
//STRIP001                     aChartRange.maRanges.push_back( aCellRangeAddress );
//STRIP001                 }
//STRIP001          }
//STRIP001
//STRIP001             if ( aOpt.Len() >= 2 )
//STRIP001          {
//STRIP001                 aChartRange.mbFirstColumnContainsLabels = ( aOpt.GetChar(0) != '0' );
//STRIP001                 aChartRange.mbFirstColumnContainsLabels = ( aOpt.GetChar(1) != '0' );
//STRIP001 #if 0
//STRIP001 /*  Calc internal data
//STRIP001              if ( aOpt.Len() >= 3 )
//STRIP001              {
//STRIP001                  if ( bNewChart )
//STRIP001                  {
//STRIP001                      bDummyUpperLeft = ( aOpt.GetChar(2) != '0' );
//STRIP001                      xub_StrLen nInd = 4;    // 111;
//STRIP001                      eGlue = (ScChartGlue) aOpt.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001                      nStartCol = (USHORT) aOpt.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001                      nStartRow = (USHORT) aOpt.GetToken( 0, cTok, nInd ).ToInt32();
//STRIP001                      bInitOk = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001  */
//STRIP001 #endif
//STRIP001          }
//STRIP001          else
//STRIP001             {
//STRIP001                 aChartRange.mbFirstColumnContainsLabels = sal_False;
//STRIP001                 aChartRange.mbFirstRowContainsLabels = sal_False;
//STRIP001             }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001             aChartRange.mbFirstColumnContainsLabels = sal_False;
//STRIP001             aChartRange.mbFirstRowContainsLabels = sal_False;
//STRIP001             aChartRange.mbKeepCopyOfData = sal_True;
//STRIP001      }
//STRIP001         SetChartRange( aChartRange );
//STRIP001     }
//STRIP001     else
//STRIP001     {   // convert SchChartRange to SomeData1/2/3
//STRIP001         const sal_Unicode cTok = ';';
//STRIP001         String aRef, aSheetNames;
//STRIP001         const SchChartRange& rChartRange = GetChartRange();
//STRIP001         ::std::vector< SchCellRangeAddress >::const_iterator iRange =
//STRIP001             rChartRange.maRanges.begin();
//STRIP001         DBG_ASSERT( iRange != rChartRange.maRanges.end(),
//STRIP001             "ConvertChartRangeForCalc: no SchCellRangeAddress vector" );
//STRIP001         for ( ; iRange != rChartRange.maRanges.end(); ++iRange )
//STRIP001         {
//STRIP001             const SchSingleCell& rAddr1 = iRange->maUpperLeft.maCells[0];
//STRIP001             const SchSingleCell& rAddr2 = iRange->maLowerRight.maCells[0];
//STRIP001             sal_Int32 nTab = iRange->mnTableNumber;
//STRIP001             if ( aRef.Len() )
//STRIP001                 aRef += cTok;
//STRIP001             aRef += String::CreateFromInt32( nTab );
//STRIP001             // here ',' as TokenSep so old versions (<341/342) will ignore it
//STRIP001             aRef += ',';  aRef += String::CreateFromInt32( nTab );
//STRIP001             aRef += cTok; aRef += String::CreateFromInt32( rAddr1.mnColumn );
//STRIP001             aRef += cTok; aRef += String::CreateFromInt32( rAddr1.mnRow );
//STRIP001             aRef += cTok; aRef += String::CreateFromInt32( rAddr2.mnColumn );
//STRIP001             aRef += cTok; aRef += String::CreateFromInt32( rAddr2.mnRow );
//STRIP001             if ( aSheetNames.Len() )
//STRIP001                 aSheetNames += cTok;
//STRIP001             aSheetNames += String( iRange->msTableName );
//STRIP001         }
//STRIP001
//STRIP001         String aFlags = rChartRange.mbFirstRowContainsLabels ? '1' : '0';
//STRIP001         aFlags += rChartRange.mbFirstColumnContainsLabels ? '1' : '0';
//STRIP001 #if 0
//STRIP001 /* these can't be stored, automatically recalculated after load by old versions
//STRIP001         aFlags += bDummyUpperLeft ? '1' : '0';
//STRIP001         aFlags += cTok;
//STRIP001         aFlags += String::CreateFromInt32( eGlue );
//STRIP001         aFlags += cTok;
//STRIP001         aFlags += String::CreateFromInt32( nStartCol );
//STRIP001         aFlags += cTok;
//STRIP001         aFlags += String::CreateFromInt32( nStartRow );
//STRIP001 */
//STRIP001 #endif
//STRIP001
//STRIP001         SomeData1() = aRef;
//STRIP001         SomeData2() = aFlags;
//STRIP001         SomeData3() = aSheetNames;
//STRIP001     }
//STRIP001 }
