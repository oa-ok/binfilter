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

// INCLUDE ---------------------------------------------------------------

#include <bf_sfx2/app.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>


#include "dbdocfun.hxx"
#include "bf_sc.hrc"
#include "dbcolect.hxx"
#include "undodat.hxx"
#include "docsh.hxx"
#include "docfunc.hxx"
#include "globstr.hrc"
#include "patattr.hxx"
#include "rangenam.hxx"
#include "dpobject.hxx"
#include "editable.hxx"
namespace binfilter {


/*N*/ BOOL ScDBDocFunc::AddDBRange( const String& rName, const ScRange& rRange, BOOL /*bApi*/ )
/*N*/ {
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/
/*N*/   ScDBData* pNew = new ScDBData( rName, rRange.aStart.Tab(),
/*N*/                                   rRange.aStart.Col(), rRange.aStart.Row(),
/*N*/                                   rRange.aEnd.Col(), rRange.aEnd.Row() );
/*N*/
/*N*/   pDoc->CompileDBFormula( TRUE );     // CreateFormulaString
/*N*/   BOOL bOk = pDocColl->Insert( pNew );
/*N*/   pDoc->CompileDBFormula( FALSE );    // CompileFormulaString
/*N*/   if (!bOk)
/*N*/   {
/*N*/       delete pNew;
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/   SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/   return TRUE;
/*N*/ }
/*N*/
/*N*/ BOOL ScDBDocFunc::DeleteDBRange( const String& rName, BOOL /*bApi*/ )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/
/*N*/   USHORT nPos = 0;
/*N*/   if (pDocColl->SearchName( rName, nPos ))
/*N*/   {
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       pDoc->CompileDBFormula( TRUE );     // CreateFormulaString
/*N*/       pDocColl->AtFree( nPos );
/*N*/       pDoc->CompileDBFormula( FALSE );    // CompileFormulaString
/*N*/
/*N*/       aModificator.SetDocumentModified();
/*N*/       SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/       bDone = TRUE;
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDBDocFunc::RenameDBRange( const String& rOld, const String& rNew, BOOL /*bApi*/ )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/
/*N*/   USHORT nPos = 0;
/*N*/   USHORT nDummy = 0;
/*N*/   if ( pDocColl->SearchName( rOld, nPos ) &&
/*N*/        !pDocColl->SearchName( rNew, nDummy ) )
/*N*/   {
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScDBData* pData = (*pDocColl)[nPos];
/*N*/       ScDBData* pNewData = new ScDBData(*pData);
/*N*/       pNewData->SetName(rNew);
/*N*/
/*N*/       ScDBCollection* pUndoColl = new ScDBCollection( *pDocColl );
/*N*/
/*N*/       pDoc->CompileDBFormula( TRUE );             // CreateFormulaString
/*N*/       pDocColl->AtFree( nPos );
/*N*/       BOOL bInserted = pDocColl->Insert( pNewData );
/*N*/       pDoc->CompileDBFormula( FALSE );            // CompileFormulaString
/*N*/
/*N*/       if (bInserted)                              // Einfuegen hat geklappt
/*N*/       {
/*N*/               delete pUndoColl;
/*N*/
/*N*/           aModificator.SetDocumentModified();
/*N*/           SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDBDocFunc::ModifyDBData( const ScDBData& rNewData, BOOL /*bApi*/)
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/
/*N*/   USHORT nPos = 0;
/*N*/   if (pDocColl->SearchName( rNewData.GetName(), nPos ))
/*N*/   {
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScDBData* pData = (*pDocColl)[nPos];
/*N*/
/*N*/       ScRange aOldRange, aNewRange;
/*N*/       pData->GetArea(aOldRange);
/*N*/       rNewData.GetArea(aNewRange);
/*N*/
/*N*/       *pData = rNewData;
/*N*/
/*N*/       aModificator.SetDocumentModified();
/*N*/       bDone = TRUE;
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }


/*N*/ BOOL ScDBDocFunc::RepeatDB( const String& rDBName, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   //! auch fuer ScDBFunc::RepeatDB benutzen!
/*N*/
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScDBCollection* pColl = pDoc->GetDBCollection();
/*N*/   USHORT nIndex;
/*N*/   if ( pColl && pColl->SearchName( rDBName, nIndex ) )
/*N*/   {
/*N*/       ScDBData* pDBData = (*pColl)[nIndex];
/*N*/
/*N*/       ScQueryParam aQueryParam;
/*N*/       pDBData->GetQueryParam( aQueryParam );
/*N*/       BOOL bQuery = aQueryParam.GetEntry(0).bDoQuery;
/*N*/
/*N*/       ScSortParam aSortParam;
/*N*/       pDBData->GetSortParam( aSortParam );
/*N*/       BOOL bSort = aSortParam.bDoSort[0];
/*N*/
/*N*/       ScSubTotalParam aSubTotalParam;
/*N*/       pDBData->GetSubTotalParam( aSubTotalParam );
/*N*/       BOOL bSubTotal = aSubTotalParam.bGroupActive[0] && !aSubTotalParam.bRemoveOnly;
/*N*/
/*N*/       if ( bQuery || bSort || bSubTotal )
/*N*/       {
/*N*/           ScRange aOldQuery;
/*N*/           ScRange aNewQuery;
/*N*/           if (bQuery && !aQueryParam.bInplace)
/*N*/           {
/*N*/               ScDBData* pDest = pDoc->GetDBAtCursor( aQueryParam.nDestCol, aQueryParam.nDestRow,
/*N*/                                                       aQueryParam.nDestTab, TRUE );
/*N*/               if (pDest && pDest->IsDoSize())
/*N*/                   pDest->GetArea( aOldQuery );
/*N*/           }
/*N*/
/*N*/           USHORT nTab;
/*N*/           USHORT nStartCol;
/*N*/           USHORT nStartRow;
/*N*/           USHORT nEndCol;
/*N*/           USHORT nEndRow;
/*N*/           pDBData->GetArea( nTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/
/*N*/           ScDocument* pUndoDoc = NULL;
/*N*/
/*N*/           if (bRecord)
/*N*/           {
/*N*/               USHORT nTabCount = pDoc->GetTableCount();
/*N*/               pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/               ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
/*N*/               if (!pTable)
/*N*/                   pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
/*N*/
/*N*/               //  Datenbereich sichern - incl. Filter-Ergebnis
/*N*/               pDoc->CopyToDocument( 0,nStartRow,nTab, MAXCOL,nEndRow,nTab, IDF_ALL, FALSE, pUndoDoc );
/*N*/
/*N*/               //  alle Formeln wegen Referenzen
/*N*/               pDoc->CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTabCount-1, IDF_FORMULA, FALSE, pUndoDoc );
/*N*/           }
/*N*/
/*N*/           if (bSort && bSubTotal)
/*N*/           {
/*N*/               //  Sortieren ohne SubTotals
/*N*/
/*N*/               aSubTotalParam.bRemoveOnly = TRUE;      // wird unten wieder zurueckgesetzt
/*N*/               DoSubTotals( nTab, aSubTotalParam, NULL, FALSE, bApi );
/*N*/           }
/*N*/
/*N*/           if (bSort)
/*N*/           {
/*N*/               pDBData->GetSortParam( aSortParam );            // Bereich kann sich geaendert haben
/*N*/               Sort( nTab, aSortParam, FALSE, FALSE, bApi );
/*N*/           }
/*N*/           if (bQuery)
/*N*/           {
/*N*/               pDBData->GetQueryParam( aQueryParam );          // Bereich kann sich geaendert haben
/*N*/               ScRange aAdvSource;
/*N*/               if (pDBData->GetAdvancedQuerySource(aAdvSource))
/*N*/                   Query( nTab, aQueryParam, &aAdvSource, FALSE, bApi );
/*N*/               else
/*N*/                   Query( nTab, aQueryParam, NULL, FALSE, bApi );
/*N*/
/*N*/               //  bei nicht-inplace kann die Tabelle umgestellt worden sein
/*N*/ //                if ( !aQueryParam.bInplace && aQueryParam.nDestTab != nTab )
/*N*/ //                    SetTabNo( nTab );
/*N*/           }
/*N*/           if (bSubTotal)
/*N*/           {
/*N*/               pDBData->GetSubTotalParam( aSubTotalParam );    // Bereich kann sich geaendert haben
/*N*/               aSubTotalParam.bRemoveOnly = FALSE;
/*N*/               DoSubTotals( nTab, aSubTotalParam, NULL, FALSE, bApi );
/*N*/           }
/*N*/
/*N*/           rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab,
/*N*/                                   PAINT_GRID | PAINT_LEFT | PAINT_TOP | PAINT_SIZE );
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/       else if (!bApi)     // "Keine Operationen auszufuehren"
/*N*/           rDocShell.ErrorMessage(STR_MSSG_REPEATDB_0);
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }


/*N*/ BOOL ScDBDocFunc::Sort( USHORT nTab, const ScSortParam& rSortParam,
/*N*/                           BOOL bRecord, BOOL bPaint, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/
/*N*/   ScDBData* pDBData = pDoc->GetDBAtArea( nTab, rSortParam.nCol1, rSortParam.nRow1,
/*N*/                                                   rSortParam.nCol2, rSortParam.nRow2 );
/*N*/   if (!pDBData)
/*N*/   {
/*N*/       OSL_FAIL( "Sort: keine DBData" );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScDBData* pDestData = NULL;
/*N*/   ScRange aOldDest;
/*N*/   BOOL bCopy = !rSortParam.bInplace;
/*N*/   if ( bCopy && rSortParam.nDestCol == rSortParam.nCol1 &&
/*N*/                 rSortParam.nDestRow == rSortParam.nRow1 && rSortParam.nDestTab == nTab )
/*N*/       bCopy = FALSE;
/*N*/   ScSortParam aLocalParam( rSortParam );
/*N*/
/*N*/   ScEditableTester aTester( pDoc, nTab, aLocalParam.nCol1,aLocalParam.nRow1,
/*N*/                                       aLocalParam.nCol2,aLocalParam.nRow2 );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   if ( aLocalParam.bIncludePattern && pDoc->HasAttrib(
/*N*/                                       aLocalParam.nCol1, aLocalParam.nRow1, nTab,
/*N*/                                       aLocalParam.nCol2, aLocalParam.nRow2, nTab,
/*N*/                                       HASATTR_MERGED | HASATTR_OVERLAPPED ) )
/*N*/   {
/*N*/       //  Merge-Attribute wuerden beim Sortieren durcheinanderkommen
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(STR_SORT_ERR_MERGED);
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/
/*N*/   //      ausfuehren
/*N*/
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   BOOL bRepeatQuery = FALSE;                          // bestehenden Filter wiederholen?
/*N*/   ScQueryParam aQueryParam;
/*N*/   pDBData->GetQueryParam( aQueryParam );
/*N*/   if ( aQueryParam.GetEntry(0).bDoQuery )
/*N*/       bRepeatQuery = TRUE;
/*N*/
/*N*/   if (bRepeatQuery && bCopy)
/*N*/   {
/*N*/       if ( aQueryParam.bInplace ||
/*N*/               aQueryParam.nDestCol != rSortParam.nDestCol ||
/*N*/               aQueryParam.nDestRow != rSortParam.nDestRow ||
/*N*/               aQueryParam.nDestTab != rSortParam.nDestTab )       // Query auf selben Zielbereich?
/*N*/           bRepeatQuery = FALSE;
/*N*/   }
/*N*/
/*N*/   if ( bCopy )
/*N*/   {
/*N*/       if (pDestData)
/*N*/           pDoc->DeleteAreaTab(aOldDest, IDF_CONTENTS);            // Zielbereich vorher loeschen
/*N*/   }
/*N*/
/*N*/   BOOL bSave = TRUE;
/*N*/   if (bCopy)
/*N*/   {
/*N*/       ScSortParam aOldSortParam;
/*N*/       pDBData->GetSortParam( aOldSortParam );
/*N*/       if ( aOldSortParam.bDoSort[0] && aOldSortParam.bInplace )   // Inplace-Sortierung gemerkt?
/*N*/       {
/*N*/           bSave = FALSE;
/*N*/           aOldSortParam.nDestCol = rSortParam.nDestCol;
/*N*/           aOldSortParam.nDestRow = rSortParam.nDestRow;
/*N*/           aOldSortParam.nDestTab = rSortParam.nDestTab;
/*N*/           pDBData->SetSortParam( aOldSortParam );                 // dann nur DestPos merken
/*N*/       }
/*N*/   }
/*N*/   if (bSave)                                              // Parameter merken
/*N*/   {
/*N*/       pDBData->SetSortParam( rSortParam );
/*N*/       pDBData->SetHeader( rSortParam.bHasHeader );        //! ???
/*N*/       pDBData->SetByRow( rSortParam.bByRow );             //! ???
/*N*/   }
/*N*/
/*N*/   if (bCopy)                                          // neuen DB-Bereich merken
/*N*/   {
/*N*/       //  Tabelle umschalten von aussen (View)
/*N*/       //! SetCursor ??!?!
/*N*/
/*N*/       ScRange aDestPos( aLocalParam.nCol1, aLocalParam.nRow1, nTab,
/*N*/                           aLocalParam.nCol2, aLocalParam.nRow2, nTab );
/*N*/       ScDBData* pNewData;
/*N*/       if (pDestData)
/*N*/           pNewData = pDestData;               // Bereich vorhanden -> anpassen
/*N*/       else                                    // Bereich ab Cursor/Markierung wird angelegt
/*N*/           pNewData = rDocShell.GetDBData(aDestPos, SC_DB_MAKE, TRUE );
/*N*/       if (pNewData)
/*N*/       {
/*N*/           pNewData->SetArea( nTab,
/*N*/                               aLocalParam.nCol1,aLocalParam.nRow1,
/*N*/                               aLocalParam.nCol2,aLocalParam.nRow2 );
/*N*/           pNewData->SetSortParam( aLocalParam );
/*N*/           pNewData->SetHeader( aLocalParam.bHasHeader );      //! ???
/*N*/           pNewData->SetByRow( aLocalParam.bByRow );
/*N*/       }
/*N*/       else
/*N*/           OSL_FAIL("Zielbereich nicht da");
/*N*/   }
/*N*/
/*N*/   ScRange aDirtyRange( aLocalParam.nCol1, aLocalParam.nRow1, nTab,
/*N*/       aLocalParam.nCol2, aLocalParam.nRow2, nTab );
/*N*/   pDoc->SetDirty( aDirtyRange );
/*N*/
/*N*/   if (bPaint)
/*N*/   {
/*N*/       USHORT nPaint = PAINT_GRID;
/*N*/       USHORT nStartX = aLocalParam.nCol1;
/*N*/       USHORT nStartY = aLocalParam.nRow1;
/*N*/       USHORT nEndX = aLocalParam.nCol2;
/*N*/       USHORT nEndY = aLocalParam.nRow2;
/*N*/       if ( bRepeatQuery )
/*N*/       {
/*N*/           nPaint |= PAINT_LEFT;
/*N*/           nStartX = 0;
/*N*/           nEndX = MAXCOL;
/*N*/       }
/*N*/       if (pDestData)
/*N*/       {
/*N*/           if ( nEndX < aOldDest.aEnd.Col() )
/*N*/               nEndX = aOldDest.aEnd.Col();
/*N*/           if ( nEndY < aOldDest.aEnd.Row() )
/*N*/               nEndY = aOldDest.aEnd.Row();
/*N*/       }
/*N*/       rDocShell.PostPaint( nStartX, nStartY, nTab, nEndX, nEndY, nTab, nPaint );
/*N*/   }
/*N*/
/*N*/ //    AdjustRowHeight( aLocalParam.nRow1, aLocalParam.nRow2, bPaint );
/*N*/   rDocShell.AdjustRowHeight( aLocalParam.nRow1, aLocalParam.nRow2, nTab );
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }


/*N*/ BOOL ScDBDocFunc::Query( USHORT nTab, const ScQueryParam& rQueryParam,
/*N*/                       const ScRange* pAdvSource, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScDBData* pDBData = pDoc->GetDBAtArea( nTab, rQueryParam.nCol1, rQueryParam.nRow1,
/*N*/                                                   rQueryParam.nCol2, rQueryParam.nRow2 );
/*N*/   if (!pDBData)
/*N*/   {
/*N*/       OSL_FAIL( "Query: keine DBData" );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   //  Wechsel von Inplace auf nicht-Inplace, dann erst Inplace aufheben:
/*N*/   //  (nur, wenn im Dialog "Persistent" ausgewaehlt ist)
/*N*/
/*N*/   if ( !rQueryParam.bInplace && pDBData->HasQueryParam() && rQueryParam.bDestPers )
/*N*/   {
/*N*/       ScQueryParam aOldQuery;
/*N*/       pDBData->GetQueryParam(aOldQuery);
/*N*/       if (aOldQuery.bInplace)
/*N*/       {
/*N*/           //  alte Filterung aufheben
/*N*/
/*N*/           USHORT nEC = aOldQuery.GetEntryCount();
/*N*/           for (USHORT i=0; i<nEC; i++)
/*N*/               aOldQuery.GetEntry(i).bDoQuery = FALSE;
/*N*/           aOldQuery.bDuplicate = TRUE;
/*N*/           Query( nTab, aOldQuery, NULL, bRecord, bApi );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ScQueryParam aLocalParam( rQueryParam );        // fuer Paint / Zielbereich
/*N*/   BOOL bCopy = !rQueryParam.bInplace;             // kopiert wird in Table::Query
/*N*/   ScDBData* pDestData = NULL;                     // Bereich, in den kopiert wird
/*N*/   BOOL bDoSize = FALSE;                           // Zielgroesse anpassen (einf./loeschen)
/*N*/   USHORT nFormulaCols = 0;                        // nur bei bDoSize
/*N*/   BOOL bKeepFmt = FALSE;
/*N*/   ScRange aOldDest;
/*N*/   ScRange aDestTotal;
/*N*/   if ( bCopy && rQueryParam.nDestCol == rQueryParam.nCol1 &&
/*N*/                 rQueryParam.nDestRow == rQueryParam.nRow1 && rQueryParam.nDestTab == nTab )
/*N*/       bCopy = FALSE;
/*N*/   USHORT nDestTab = nTab;
/*N*/
/*N*/   //      ausfuehren
/*N*/
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   ScSubTotalParam aSubTotalParam;
/*N*/   if (rQueryParam.GetEntry(0).bDoQuery)           // nicht beim Aufheben
/*N*/       pDBData->GetSubTotalParam( aSubTotalParam );    // Teilergebnisse vorhanden?
/*N*/
/*N*/   ScDocument* pAttribDoc = NULL;
/*N*/   ScRange aAttribRange;
/*N*/   if (pDestData)                                      // Zielbereich loeschen
/*N*/   {
/*N*/       if ( bKeepFmt )
/*N*/       {
/*N*/           //  kleinere der End-Spalten, Header+1 Zeile
/*N*/           aAttribRange = aOldDest;
/*N*/           if ( aAttribRange.aEnd.Col() > aDestTotal.aEnd.Col() )
/*N*/               aAttribRange.aEnd.SetCol( aDestTotal.aEnd.Col() );
/*N*/           aAttribRange.aEnd.SetRow( aAttribRange.aStart.Row() +
/*N*/                                       ( aLocalParam.bHasHeader ? 1 : 0 ) );
/*N*/
/*N*/           //  auch fuer aufgefuellte Formeln
/*N*/           aAttribRange.aEnd.SetCol( aAttribRange.aEnd.Col() + nFormulaCols );
/*N*/
/*N*/           pAttribDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           pAttribDoc->InitUndo( pDoc, nDestTab, nDestTab, FALSE, TRUE );
/*N*/           pDoc->CopyToDocument( aAttribRange, IDF_ATTRIB, FALSE, pAttribDoc );
/*N*/       }
/*N*/
/*N*/       if ( bDoSize )
/*N*/           pDoc->FitBlock( aOldDest, aDestTotal );
/*N*/       else
/*N*/           pDoc->DeleteAreaTab(aOldDest, IDF_ALL);         // einfach loeschen
/*N*/   }
/*N*/
/*N*/   //  Filtern am Dokument ausfuehren
/*N*/   if (bCopy)
/*N*/   {
/*N*/       aLocalParam.nRow2 = aLocalParam.nRow1;
/*N*/
/*N*/       if ( bDoSize )
/*N*/       {
/*N*/           //  auf wirklichen Ergebnis-Bereich anpassen
/*N*/           //  (das hier ist immer eine Verkleinerung)
/*N*/
/*N*/           ScRange aNewDest( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/                               aLocalParam.nCol2, aLocalParam.nRow2, nDestTab );
/*N*/           pDoc->FitBlock( aDestTotal, aNewDest, FALSE );      // FALSE - nicht loeschen
/*N*/
/*N*/           if ( nFormulaCols )
/*N*/           {
/*N*/               //  Formeln ausfuellen
/*N*/               //! Undo (Query und Repeat) !!!
/*N*/
/*N*/               ScRange aNewForm( aLocalParam.nCol2+1, aLocalParam.nRow1, nDestTab,
/*N*/                                 aLocalParam.nCol2+nFormulaCols, aLocalParam.nRow2, nDestTab );
/*N*/               ScRange aOldForm = aNewForm;
/*N*/               aOldForm.aEnd.SetRow( aOldDest.aEnd.Row() );
/*N*/               pDoc->FitBlock( aOldForm, aNewForm, FALSE );
/*N*/
/*N*/               ScMarkData aMark;
/*N*/               aMark.SelectOneTable(nDestTab);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( pAttribDoc )       // gemerkte Attribute zurueckkopieren
/*N*/       {
/*N*/           //  Header
/*N*/           if (aLocalParam.bHasHeader)
/*N*/           {
/*N*/               ScRange aHdrRange = aAttribRange;
/*N*/               aHdrRange.aEnd.SetRow( aHdrRange.aStart.Row() );
/*N*/               pAttribDoc->CopyToDocument( aHdrRange, IDF_ATTRIB, FALSE, pDoc );
/*N*/           }
/*N*/
/*N*/           //  Daten
/*N*/           USHORT nAttrEndCol = aAttribRange.aEnd.Col();
/*N*/           USHORT nAttrRow = aAttribRange.aStart.Row() + ( aLocalParam.bHasHeader ? 1 : 0 );
/*N*/           for (USHORT nCol = aAttribRange.aStart.Col(); nCol<=nAttrEndCol; nCol++)
/*N*/           {
/*N*/               const ScPatternAttr* pSrcPattern = pAttribDoc->GetPattern(
/*N*/                                                   nCol, nAttrRow, nDestTab );
/*N*/               DBG_ASSERT(pSrcPattern,"Pattern ist 0");
/*N*/               if (pSrcPattern)
/*N*/                   pDoc->ApplyPatternAreaTab( nCol, nAttrRow, nCol, aLocalParam.nRow2,
/*N*/                                                   nDestTab, *pSrcPattern );
/*N*/               const ScStyleSheet* pStyle = pSrcPattern->GetStyleSheet();
/*N*/               if (pStyle)
/*N*/                   pDoc->ApplyStyleAreaTab( nCol, nAttrRow, nCol, aLocalParam.nRow2,
/*N*/                                                   nDestTab, *pStyle );
/*N*/           }
/*N*/
/*N*/           delete pAttribDoc;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //  speichern: Inplace immer, sonst je nach Einstellung
/*N*/   //             alter Inplace-Filter ist ggf. schon aufgehoben
/*N*/
/*N*/   BOOL bSave = rQueryParam.bInplace || rQueryParam.bDestPers;
/*N*/   if (bSave)                                                  // merken
/*N*/   {
/*N*/       pDBData->SetQueryParam( rQueryParam );
/*N*/       pDBData->SetHeader( rQueryParam.bHasHeader );       //! ???
/*N*/       pDBData->SetAdvancedQuerySource( pAdvSource );      // after SetQueryParam
/*N*/   }
/*N*/
/*N*/   if (bCopy)                                              // neuen DB-Bereich merken
/*N*/   {
/*N*/       //  selektieren wird hinterher von aussen (dbfunc)
/*N*/       //  momentan ueber DB-Bereich an der Zielposition, darum muss dort
/*N*/       //  auf jeden Fall ein Bereich angelegt werden.
/*N*/
/*N*/       ScDBData* pNewData;
/*N*/       if (pDestData)
/*N*/           pNewData = pDestData;               // Bereich vorhanden -> anpassen (immer!)
/*N*/       else                                    // Bereich anlegen
/*N*/           pNewData = rDocShell.GetDBData(
/*N*/                           ScRange( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/                                    aLocalParam.nCol2, aLocalParam.nRow2, nDestTab ),
/*N*/                           SC_DB_MAKE, TRUE );
/*N*/
/*N*/       if (pNewData)
/*N*/       {
/*N*/           pNewData->SetArea( nDestTab, aLocalParam.nCol1, aLocalParam.nRow1,
/*N*/                                           aLocalParam.nCol2, aLocalParam.nRow2 );
/*N*/
/*N*/           //  Query-Param wird am Ziel nicht mehr eingestellt, fuehrt nur zu Verwirrung
/*N*/           //  und Verwechslung mit dem Query-Param am Quellbereich (#37187#)
/*N*/       }
/*N*/       else
/*N*/           OSL_FAIL("Zielbereich nicht da");
/*N*/   }
/*N*/
/*N*/   if (!bCopy)
/*N*/       pDoc->UpdatePageBreaks( nTab );
/*N*/
/*N*/   ScRange aDirtyRange( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/       aLocalParam.nCol2, aLocalParam.nRow2, nDestTab );
/*N*/   pDoc->SetDirty( aDirtyRange );
/*N*/
/*N*/   if (bCopy)
/*N*/   {
/*N*/       USHORT nEndX = aLocalParam.nCol2;
/*N*/       USHORT nEndY = aLocalParam.nRow2;
/*N*/       if (pDestData)
/*N*/       {
/*N*/           if ( aOldDest.aEnd.Col() > nEndX )
/*N*/               nEndX = aOldDest.aEnd.Col();
/*N*/           if ( aOldDest.aEnd.Row() > nEndY )
/*N*/               nEndY = aOldDest.aEnd.Row();
/*N*/       }
/*N*/       if (bDoSize)
/*N*/           nEndY = MAXROW;
/*N*/       rDocShell.PostPaint( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/                                   nEndX, nEndY, nDestTab, PAINT_GRID );
/*N*/   }
/*N*/   else
/*N*/       rDocShell.PostPaint( 0, rQueryParam.nRow1, nTab, MAXCOL, MAXROW, nTab,
/*N*/                                               PAINT_GRID | PAINT_LEFT );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }


/*N*/ BOOL ScDBDocFunc::DoSubTotals( USHORT nTab, const ScSubTotalParam& rParam,
/*N*/                               const ScSortParam* /*pForceNewSort*/, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   //! auch fuer ScDBFunc::DoSubTotals benutzen!
/*N*/   //  dann bleibt aussen:
/*N*/   //  - neuen Bereich (aus DBData) markieren
/*N*/   //  - SelectionChanged (?)
/*N*/
/*N*/   BOOL bDo = !rParam.bRemoveOnly;                         // FALSE = nur loeschen
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScDBData* pDBData = pDoc->GetDBAtArea( nTab, rParam.nCol1, rParam.nRow1,
/*N*/                                               rParam.nCol2, rParam.nRow2 );
/*N*/   if (!pDBData)
/*N*/   {
/*N*/       OSL_FAIL( "SubTotals: keine DBData" );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScEditableTester aTester( pDoc, nTab, 0,rParam.nRow1+1, MAXCOL,MAXROW );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   if (pDoc->HasAttrib( rParam.nCol1, rParam.nRow1+1, nTab,
/*N*/                        rParam.nCol2, rParam.nRow2, nTab, HASATTR_MERGED | HASATTR_OVERLAPPED ))
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(STR_MSSG_INSERTCELLS_0); // nicht in zusammengefasste einfuegen
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   BOOL bOk = TRUE;
/*N*/
/*N*/   if (bOk)
/*N*/   {
/*N*/       WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScSubTotalParam aNewParam( rParam );        // Bereichsende wird veraendert
/*N*/       ScDocument*     pUndoDoc = NULL;
/*N*/       USHORT          nTabCount = 0;              // fuer Referenz-Undo
/*N*/
/*N*/       if (bRecord)                                        // alte Daten sichern
/*N*/       {
/*N*/           BOOL bOldFilter = bDo && rParam.bDoSort;
/*N*/
/*N*/           nTabCount = pDoc->GetTableCount();
/*N*/           pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
/*N*/           if (!pTable)
/*N*/               pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, bOldFilter );
/*N*/
/*N*/           //  Datenbereich sichern - incl. Filter-Ergebnis
/*N*/           pDoc->CopyToDocument( 0,rParam.nRow1+1,nTab, MAXCOL,rParam.nRow2,nTab,
/*N*/                                   IDF_ALL, FALSE, pUndoDoc );
/*N*/
/*N*/           //  alle Formeln wegen Referenzen
/*N*/           pDoc->CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTabCount-1,
/*N*/                                       IDF_FORMULA, FALSE, pUndoDoc );
/*N*/       }
/*N*/
/*N*/       /* ScOutlineTable* pOut = */ pDoc->GetOutlineTable( nTab );
/*N*/
/*N*/       BOOL bSuccess = TRUE;
/*N*/       ScRange aDirtyRange( aNewParam.nCol1, aNewParam.nRow1, nTab,
/*N*/           aNewParam.nCol2, aNewParam.nRow2, nTab );
/*N*/       pDoc->SetDirty( aDirtyRange );
/*N*/
/*N*/       if (!bSuccess)
/*N*/       {
/*N*/           // "Kann keine Zeilen einfuegen"
/*N*/           if (!bApi)
/*N*/               rDocShell.ErrorMessage(STR_MSSG_DOSUBTOTALS_2);
/*N*/       }
/*N*/
/*N*/                                                   // merken
/*N*/       pDBData->SetSubTotalParam( aNewParam );
/*N*/       pDBData->SetArea( nTab, aNewParam.nCol1,aNewParam.nRow1, aNewParam.nCol2,aNewParam.nRow2 );
/*N*/
/*N*/       rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab,
/*N*/                                               PAINT_GRID | PAINT_LEFT | PAINT_TOP | PAINT_SIZE );
/*N*/       aModificator.SetDocumentModified();
/*N*/
/*N*/       bRet = bSuccess;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ BOOL ScDBDocFunc::DataPilotUpdate( ScDPObject* pOldObj, const ScDPObject* pNewObj,
/*N*/                                       BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   BOOL bDone = FALSE;
/*N*/   USHORT nErrId = 0;
/*N*/
/*N*/   ScDocument* pOldUndoDoc = NULL;
/*N*/   ScDocument* pNewUndoDoc = NULL;
/*N*/   ScDPObject* pUndoDPObj = NULL;
/*N*/   if ( bRecord && pOldObj )
/*N*/       pUndoDPObj = new ScDPObject( *pOldObj );    // copy old settings for undo
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   if ( !rDocShell.IsEditable() || pDoc->GetChangeTrack() )
/*N*/   {
/*N*/       //  not recorded -> disallow
/*N*/       //! different error messages?
/*N*/
/*N*/       nErrId = STR_PROTECTIONERR;
/*N*/   }
/*N*/   if ( pOldObj && !nErrId )
/*N*/   {
/*N*/       ScRange aOldOut = pOldObj->GetOutRange();
/*N*/       ScEditableTester aTester( pDoc, aOldOut );
/*N*/       if ( !aTester.IsEditable() )
/*N*/           nErrId = aTester.GetMessageId();
/*N*/   }
/*N*/   if ( pNewObj && !nErrId )
/*N*/   {
/*N*/       //  at least one cell at the output position must be editable
/*N*/       //  -> check in advance
/*N*/       //  (start of output range in pNewObj is valid)
/*N*/
/*N*/       ScRange aNewStart( pNewObj->GetOutRange().aStart );
/*N*/       ScEditableTester aTester( pDoc, aNewStart );
/*N*/       if ( !aTester.IsEditable() )
/*N*/           nErrId = aTester.GetMessageId();
/*N*/   }
/*N*/
/*N*/   ScDPObject* pDestObj = NULL;
/*N*/   if ( !nErrId )
/*N*/   {
/*N*/       if ( pOldObj && !pNewObj )
/*N*/       {
/*N*/           //  delete table
/*N*/
/*N*/           ScRange aRange = pOldObj->GetOutRange();
/*N*/           USHORT nTab = aRange.aStart.Tab();
/*N*/
/*N*/           if ( bRecord )
/*N*/           {
/*N*/               pOldUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/               pOldUndoDoc->InitUndo( pDoc, nTab, nTab );
/*N*/               pDoc->CopyToDocument( aRange, IDF_ALL, FALSE, pOldUndoDoc );
/*N*/           }
/*N*/
/*N*/           pDoc->DeleteAreaTab( aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/                                aRange.aEnd.Col(),   aRange.aEnd.Row(),
/*N*/                                nTab, IDF_ALL );
/*N*/
/*N*/           pDoc->GetDPCollection()->Free( pOldObj );   // object is deleted here
/*N*/
/*N*/           rDocShell.PostPaintGridAll();   //! only necessary parts
/*N*/           rDocShell.PostPaint( aRange.aStart.Col(), aRange.aStart.Row(), nTab,
/*N*/                                aRange.aEnd.Col(),   aRange.aEnd.Row(),   nTab,
/*N*/                                PAINT_GRID );
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/       else if ( pNewObj )
/*N*/       {
/*N*/           if ( pOldObj )
/*N*/           {
/*N*/               if ( bRecord )
/*N*/               {
/*N*/                   ScRange aRange = pOldObj->GetOutRange();
/*N*/                   USHORT nTab = aRange.aStart.Tab();
/*N*/                   pOldUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/                   pOldUndoDoc->InitUndo( pDoc, nTab, nTab );
/*N*/                   pDoc->CopyToDocument( aRange, IDF_ALL, FALSE, pOldUndoDoc );
/*N*/               }
/*N*/
/*N*/               pDestObj = pOldObj;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               //  output range must be set at pNewObj
/*N*/
/*N*/               pDestObj = new ScDPObject( *pNewObj );
/*N*/               pDestObj->SetAlive(TRUE);
/*N*/               if ( !pDoc->GetDPCollection()->Insert(pDestObj) )
/*N*/               {
/*N*/                   OSL_FAIL("cannot insert DPObject");
/*N*/                   DELETEZ( pDestObj );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       // else nothing (no old, no new)
/*N*/   }
/*N*/
/*N*/   delete pOldUndoDoc;     // if not used for undo
/*N*/   delete pNewUndoDoc;
/*N*/   delete pUndoDPObj;
/*N*/
/*N*/   if (bDone)
/*N*/       aModificator.SetDocumentModified();
/*N*/
/*N*/   if ( nErrId && !bApi )
/*N*/       rDocShell.ErrorMessage( nErrId );
/*N*/
/*N*/   return bDone;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
