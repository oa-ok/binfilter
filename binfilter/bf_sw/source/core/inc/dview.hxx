/*************************************************************************
 *
 *  $RCSfile: dview.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:23:25 $
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
#ifndef _DVIEW_HXX
#define _DVIEW_HXX


#ifndef _SVX_FMVIEW_HXX //autogen
#include <bf_svx/fmview.hxx>
#endif

class OutputDevice;
class SwViewImp;

class SwDrawView : public FmFormView
{
    //Fuer den Anker
    Point           aAnchorPoint;       //Ankerposition
    SwViewImp      &rImp;               //Die View gehoert immer zu einer Shell

//STRIP001  const SwFrm *CalcAnchor();

protected:
    // add custom handles (used by other apps, e.g. AnchorPos)
    virtual void AddCustomHdl();

public:
    SwDrawView( SwViewImp &rI, SdrModel *pMd, OutputDevice* pOutDev=NULL );

    //aus der Basisklasse
//STRIP001     virtual SdrObject*   GetMaxToTopObj(SdrObject* pObj) const;
//STRIP001     virtual SdrObject*   GetMaxToBtmObj(SdrObject* pObj) const;
    virtual void         MarkListHasChanged();

    // #i7672#
    // Overload to resue edit background color in active text edit view (OutlinerView)
    virtual void ModelHasChanged();

//STRIP001  virtual void         ObjOrderChanged( SdrObject* pObj, ULONG nOldPos,
//STRIP001                                          ULONG nNewPos );
//STRIP001     virtual BOOL TakeDragLimit(SdrDragMode eMode, Rectangle& rRect) const;
//STRIP001  virtual void MakeVisible( const Rectangle&, Window &rWin );
//STRIP001  virtual void CheckPossibilities();

    const SwViewImp &Imp() const { return rImp; }
          SwViewImp &Imp()       { return rImp; }

    // Innerhalb eines des sichtbaren Ankers?
//STRIP001  Rectangle *IsAnchorAtPos( const Point &rPt ) const;

    //Anker und Xor fuer das Draggen.
//STRIP001  void ShowDragAnchor();

//STRIP001  virtual void DeleteMarked();

    // temp. Fix fuer Bug 57153 - nach Undo kann in der MarkListe nicht
    //  immer ein Writer-Draw-Object stehen ( SdrObject ohne User-Call)
    // Dann muss die Markliste aktualisiert werden.
    // JP 02.10.98: hat aber Nebenwirkungen,wie Bug 57475
    //const SdrMarkList& GetMarkList() const;
    //JP 06.10.98: 2. Versuch
    inline void ValidateMarkList() { FlushComeBackTimer(); }

    // OD 18.06.2003 #108784# - method to replace marked/selected <SwDrawVirtObj>
    // by its reference object for delete of selection and group selection
//STRIP001     static void ReplaceMarkedDrawVirtObjs( SdrMarkView& _rMarkView );

};


#endif

