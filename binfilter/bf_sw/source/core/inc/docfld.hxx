/*************************************************************************
 *
 *  $RCSfile: docfld.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: pjunck $ $Date: 2004-10-27 13:35:42 $
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

#ifndef _DOCFLD_HXX
#define _DOCFLD_HXX

#ifndef _CALC_HXX
#include <calc.hxx>         // fuer SwHash
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
namespace binfilter {

class SwTxtFld;
class SwIndex;
class SwNodeIndex;
class SwCntntNode;
class SwCntntFrm;
class SwSectionNode;
class SwSection;
class SwTxtTOXMark;
class SwTableBox;
class SwTxtINetFmt;
class SwFlyFrmFmt;

// Update an den Expression Feldern
class _SetGetExpFld
{
    ULONG nNode;
    xub_StrLen nCntnt;
    union {
        const SwTxtFld* pTxtFld;
        const SwSection* pSection;
        const SwPosition* pPos;
        const SwTxtTOXMark* pTxtTOX;
        const SwTableBox* pTBox;
        const SwTxtINetFmt* pTxtINet;
        const SwFlyFrmFmt* pFlyFmt;
    } CNTNT;
    enum _SetGetExpFldType
        {
            TEXTFIELD, TEXTTOXMARK, SECTIONNODE, CRSRPOS, TABLEBOX,
            TEXTINET, FLYFRAME
        } eSetGetExpFldType;

public:
    _SetGetExpFld( const SwNodeIndex& rNdIdx, const SwTxtFld* pFld = 0,
                    const SwIndex* pIdx = 0 );

    _SetGetExpFld( const SwNodeIndex& rNdIdx, const SwTxtINetFmt& rINet,
                    const SwIndex* pIdx = 0 );

    _SetGetExpFld( const SwSectionNode& rSectNode,
                    const SwPosition* pPos = 0  );

    _SetGetExpFld( const SwTableBox& rTableBox,
                    const SwPosition* pPos = 0  );

    _SetGetExpFld( const SwNodeIndex& rNdIdx, const SwTxtTOXMark& rTOX,
                    const SwIndex* pIdx );

    _SetGetExpFld( const SwPosition& rPos );

    _SetGetExpFld( const SwFlyFrmFmt& rFlyFmt, const SwPosition* pPos = 0 );

    BOOL operator==( const _SetGetExpFld& rFld ) const
    {   return nNode == rFld.nNode && nCntnt == rFld.nCntnt &&
                ( !CNTNT.pTxtFld || !rFld.CNTNT.pTxtFld ||
                    CNTNT.pTxtFld == rFld.CNTNT.pTxtFld ); }
    BOOL operator<( const _SetGetExpFld& rFld ) const;

     const SwTxtFld* GetFld() const
        { return TEXTFIELD == eSetGetExpFldType ? CNTNT.pTxtFld : 0; }
//STRIP001  const SwTxtTOXMark* GetTOX() const
//STRIP001      { return TEXTTOXMARK == eSetGetExpFldType ? CNTNT.pTxtTOX : 0; }
     const SwSection* GetSection() const
         { return SECTIONNODE == eSetGetExpFldType ? CNTNT.pSection : 0; }
//STRIP001  const SwTableBox* GetTableBox() const
//STRIP001      { return TABLEBOX == eSetGetExpFldType ? CNTNT.pTBox : 0; }
//STRIP001  const SwTxtINetFmt* GetINetFmt() const
//STRIP001      { return TEXTINET == eSetGetExpFldType ? CNTNT.pTxtINet : 0; }
//STRIP001  const SwFlyFrmFmt* GetFlyFmt() const
//STRIP001      { return FLYFRAME == eSetGetExpFldType ? CNTNT.pFlyFmt : 0; }
//STRIP001
     ULONG GetNode() const { return nNode; }
//STRIP001  xub_StrLen GetCntnt() const { return nCntnt; }
    const void* GetPointer() const { return CNTNT.pTxtFld; }
//STRIP001
//STRIP001  void GetPos( SwPosition& rPos ) const;
//STRIP001  void GetPosOfContent( SwPosition& rPos ) const;
//STRIP001
    const SwNode* GetNodeFromCntnt() const;
    xub_StrLen GetCntPosFromCntnt() const;
//STRIP001
//STRIP001  void SetBodyPos( const SwCntntFrm& rFrm );
};

typedef _SetGetExpFld* _SetGetExpFldPtr;
SV_DECL_PTRARR_SORT_DEL( _SetGetExpFlds, _SetGetExpFldPtr, 0, 10 )


// Struktur zum Speichern der Strings aus SetExp-String-Feldern
struct _HashStr : public SwHash
{
    String aSetStr;
    _HashStr( const String& rName, const String& rText, _HashStr* = 0 );
};

struct SwCalcFldType : public SwHash
{
    const SwFieldType* pFldType;

    SwCalcFldType( const String& rStr, const SwFieldType* pFldTyp )
        : SwHash( rStr ), pFldType( pFldTyp )
    {}
};

// Suche nach dem String, der unter dem Namen in der HashTabelle abgelegt
// wurde
void LookString( SwHash** ppTbl, USHORT nSize, const String& rName,
                    String& rRet, USHORT* pPos = 0 );


// --------

const int GETFLD_ALL        = 3;        // veroderte Flags !!
const int GETFLD_CALC       = 1;
const int GETFLD_EXPAND     = 2;

class SwDocUpdtFld
{
    _SetGetExpFlds* pFldSortLst;    // akt. Field-Liste zum Calculieren
    SwCalcFldType*  aFldTypeTable[ TBLSZ ];

// noch eine weitere Optimierung - wird z.Z. nicht angesprochen!
    long nFldUpdtPos;               // ab dieser Position mit Update starten
    SwCntntNode* pCNode;            // der TxtNode zur UpdatePos.

    ULONG nNodes;                   // sollte die NodesAnzahl unterschiedlich sein
    BYTE nFldLstGetMode;

    BOOL bInUpdateFlds : 1;         // zur Zeit laeuft ein UpdateFlds,
    BOOL bFldsDirty : 1;            // irgendwelche Felder sind ungueltig

    void _MakeFldList( SwDoc& pDoc, int eGetMode );
    void GetBodyNode( const SwTxtFld& , USHORT nFldWhich );
    void GetBodyNode( const SwSectionNode&);
public:
    SwDocUpdtFld();
    ~SwDocUpdtFld();

    const _SetGetExpFlds* GetSortLst() const { return pFldSortLst; }

    void MakeFldList( SwDoc& rDoc, int bAll, int eGetMode )
    {
        if( !pFldSortLst || bAll || !( eGetMode & nFldLstGetMode ) ||
            rDoc.GetNodes().Count() != nNodes )
            _MakeFldList( rDoc, eGetMode );
    }

    void InsDelFldInFldLst( BOOL bIns, const SwTxtFld& rFld );

    void InsertFldType( const SwFieldType& rType );
//STRIP001  void RemoveFldType( const SwFieldType& rType );

    BOOL IsInUpdateFlds() const         { return bInUpdateFlds; }
    void SetInUpdateFlds( BOOL b )      { bInUpdateFlds = b; }

    BOOL IsFieldsDirty() const          { return bFldsDirty; }
    void SetFieldsDirty( BOOL b )       { bFldsDirty = b; }

    SwHash**    GetFldTypeTable() const { return (SwHash**)aFldTypeTable; }
};


} //namespace binfilter
#endif  // _DOCFLD_HXX

