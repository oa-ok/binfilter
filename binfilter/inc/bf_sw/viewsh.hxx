/*************************************************************************
 *
 *  $RCSfile: viewsh.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:30:03 $
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
#ifndef _VIEWSH_HXX
#define _VIEWSH_HXX

#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _RING_HXX
#include <ring.hxx>
#endif
#ifndef _SWRECT_HXX
#include <swrect.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
/*N*/ #include <tools/debug.hxx> //for stripping
#ifdef ACCESSIBLE_LAYOUT
namespace com { namespace sun { namespace star { namespace accessibility {
           class XAccessible; } } } }
#endif
class VirtualDevice;
class SfxItemPool;
class Window;
class OutputDevice;
class SvtAccessibilityOptions;
class Fraction;
class SvEmbeddedObjectRef;

namespace binfilter {

class SwDoc;
class SfxPrinter;

class SfxProgress;
class SwRootFrm;
class SwNodes;
class SdrView;

class SfxViewShell;
class SwViewOption;
class SwViewImp;
class SwPrtOptions;
class SwPagePreViewPrtData;
class SwLayIdle;
struct ShellResource;
class SwRegionRects;
class SwFrm;
struct SwPrintData;
// OD 12.12.2002 #103492#
class SwPagePreviewLayout;

struct SwAccessibilityOptions;


//JP 19.07.98: - Bug 52312
// define fuer Flags, die im CTOR oder den darunter liegenden Schichten
// benoetigt werden.
// Zur Zeit wird fuer die DrawPage das PreView Flag benoetigt
#define VSHELLFLAG_ISPREVIEW            ((long)0x1)

class ViewShell : public Ring
{
    friend void SetOutDev( ViewShell *pSh, OutputDevice *pOut );
    friend void SetOutDevAndWin( ViewShell *pSh, OutputDevice *pOut,
                                 Window *pWin, sal_uInt16 nZoom );

    friend class SwViewImp;
    friend class SwLayIdle;

    // OD 12.12.2002 #103492# - for setting visible area for page preview paint
    friend class SwPagePreviewLayout;

    //Umsetzen der SwVisArea, damit vor dem Drucken sauber formatiert
    //werden kann.
    friend void SetSwVisArea( ViewShell *pSh, const SwRect &, BOOL bPDFExport = FALSE );

    static sal_Bool bLstAct;            // sal_True wenn Das EndAction der letzten Shell
                                    // laeuft; also die EndActions der
                                    // anderen Shells auf das Dokument
                                    // abgearbeitet sind.

    Point         aPrtOffst;         //Ofst fuer den Printer,
                                     //nicht bedruckbarer Rand.
     Size         aBrowseBorder;    //Rand fuer Framedokumente
    SwRect        aInvalidRect;

    SfxViewShell *pSfxViewShell;
    SwViewImp    *pImp;             //Core-Interna der ViewShell.
                                    //Der Pointer ist niemals 0.

    Window       *pWin;              // = 0 during printing or pdf export
    OutputDevice *pOut;              // Window, Printer, VirtDev, ...
    OutputDevice* mpTmpRef;           // Temporariy reference device. Is used
                                     // during (printer depending) prospect
                                     // and page preview printing
                                     // (because a scaling has to be set at
                                     // the original printer)

    SwViewOption *pOpt;
    SwAccessibilityOptions* pAccOptions;


    sal_Bool  bDocSizeChgd     :1;  //Fuer DocChgNotify(): Neue DocGroesse bei
                                //EndAction an das DocMDI melden.
    sal_Bool  bPaintWorks      :1;  //Normal Painten wenn sal_True,
                                //Paint merken wenn sal_False
    sal_Bool  bPaintInProgress :1;  //Kein zweifaches Paint durchlassen.
    sal_Bool  bViewLocked      :1;  //Lockt den sichtbaren Bereich,
                                //MakeVisible laeuft dann in's leere.
    sal_Bool  bInEndAction     :1;  //Fiese unstaende vermeiden, siehe viewsh.cxx
    sal_Bool  bPreView         :1;  //Ist sal_True wenns eine PreView-ViewShell ist.
    sal_Bool  bFrameView       :1;  //sal_True wenn es ein (HTML-)Frame ist.
    sal_Bool  bEnableSmooth    :1;  //Disable des SmoothScroll z.B. fuer
                                //Drag der Scrollbars.
    sal_Bool  bEndActionByVirDev:1; //Paints aus der EndAction immer ueber virtuelles

                                //Device (etwa beim Browsen)

    //Initialisierung, wird von den verschiedenen Konstruktoren gerufen.
    void Init( const SwViewOption *pNewOpt );

    inline void ResetInvalidRect();

//STRIP001  void SetSubsLines();

    void Reformat();            //Invalidert das ges. Layout (ApplyViewOption)

//STRIP001  void PaintDesktop( const SwRect & );        // sammeln der Werte fuers
                                                // Malen der Wiese und rufen
    // PaintDesktop gesplittet, dieser Teil wird auch von PreViewPage benutzt
//STRIP001  void _PaintDesktop( const SwRegionRects &rRegion );

    sal_Bool CheckInvalidForPaint( const SwRect & );//Direkt Paint oder lieber
                                                //eine Aktion ausloesen.

    void Scroll();  //Scrollen wenn sich aus der LayAction Scrollmoeglichkeiten
                    //ergaben.

//STRIP001     void PrepareForPrint( const SwPrtOptions &rOptions );

//STRIP001  void ImplApplyViewOptions( const SwViewOption &rOpt );

protected:
    static ShellResource*   pShellRes;      // Resourcen fuer die Shell
    static Window*          pCareWindow;    // diesem Fenster ausweichen

    SwRect                  aVisArea;       //Die moderne Ausfuerung der VisArea
    SwDoc                   *pDoc;          //Das Dokument, niemals 0

    sal_uInt16 nStartAction; //ist != 0 wenn mindestens eine ::com::sun::star::chaos::Action laeuft
    sal_uInt16 nLockPaint;   //ist != 0 wenn das Paint gelocked ist.

public:
    TYPEINFO();

          SwViewImp *Imp() { return pImp; }
    const SwViewImp *Imp() const { return pImp; }

    const SwNodes& GetNodes() const;

    //Nach Druckerwechsel, vom Doc
    //pPDFOut != NULL is used for PDF export.
    void            InitPrt( SfxPrinter * , OutputDevice *pPDFOut = NULL );

    SwPrintData*    GetPrintData() const;
    void            SetPrintData(SwPrintData& rPrtData);

    //Klammerung von zusammengehoerenden Aktionen.
    inline void StartAction();
           void ImplStartAction();
    inline void EndAction( const sal_Bool bIdleEnd = sal_False );
           void ImplEndAction( const sal_Bool bIdleEnd = sal_False );
    sal_uInt16 ActionCount() const { return nStartAction; }
    sal_Bool ActionPend() const { return nStartAction != 0; }
    sal_Bool IsInEndAction() const { return bInEndAction; }

    void SetEndActionByVirDev( sal_Bool b ) { bEndActionByVirDev = b; }
    sal_Bool IsEndActionByVirDev()          { return bEndActionByVirDev; }

    //  Per UNO wird am RootFrame fuer alle shells der ActionCount kurzfristig
    //  auf Null gesetzt und wieder restauriert
//STRIP001  void    SetRestoreActions(sal_uInt16 nSet);
//STRIP001  sal_uInt16  GetRestoreActions() const;

    inline sal_Bool HasInvalidRect() const { return aInvalidRect.HasArea(); }
    void ChgHyphenation() { Reformat(); }
    void ChgNumberDigits() { Reformat(); }

    //Methoden fuer Paint- und Scrollrects, die auf allen Shells im
    //Ring arbeiten.
    sal_Bool AddPaintRect( const SwRect &rRect );
    void AddScrollRect( const SwFrm *pFrm, const SwRect &rRect, long nOffs );
    void SetNoNextScroll();

    void InvalidateWindows( const SwRect &rRect );
//STRIP001  virtual void Paint(const Rectangle &rRect);
    sal_Bool IsPaintInProgress() const { return bPaintInProgress; }

    //Benachrichtung, dass sich der sichtbare Bereich geaendert hat.
    //VisArea wird neu gesetzt, anschliessend wird gescrollt.
    //Das uebergebene Rect liegt auf Pixelgrenzen,
    //um Pixelfehler beim Scrollen zu vermeiden.
//STRIP001  virtual void VisPortChgd( const SwRect & );
//STRIP001  sal_Bool SmoothScroll( long lXDiff, long lYDiff, const Rectangle* );//Browser
    void EnableSmooth( sal_Bool b ) { bEnableSmooth = b; }

    const SwRect &VisArea() const { return aVisArea; }
        //Es wird, wenn notwendig, soweit gescrollt, dass das
        //uebergebene Rect im sichtbaren Ausschnitt liegt.
    void MakeVisible( const SwRect & );

    //Bei naechster Gelegenheit die neue Dokuemntgroesse an das UI weiterreichen.
    void SizeChgNotify(const Size &);
    void UISizeNotify();            //Das weiterreichen der aktuellen groesse.

//STRIP001  Point GetPagePos( sal_uInt16 nPageNum ) const;

//STRIP001  sal_uInt16 GetNumPages();   //Anzahl der aktuellen Seiten Layout erfragen.
//STRIP001     sal_Bool   IsDummyPage( USHORT nPageNum ) const;  // An empty page?

    //Invalidierung der ersten Sichtbaren Seite fuer alle Shells im Ring.
    void SetFirstVisPageInvalid();

    SwRootFrm   *GetLayout() const;
//STRIP001  sal_Bool         IsNewLayout() const; //Wurde das Layout geladen oder neu
                                      //erzeugt?

     Size GetDocSize() const;// erfrage die Groesse des Dokuments

    void CalcLayout();  //Durchformatierung des Layouts erzwingen.

    inline SwDoc *GetDoc()  const { return pDoc; }  //niemals 0.

    // 1. GetPrt:      The printer at the document
    // 3. GetRefDev:   Either the printer or the virtual device from the doc
    // 2. GetWin:      Available if we not printing
    // 4. GetOut:      Printer, Window or Virtual device
    SfxPrinter* GetPrt( sal_Bool bCreate = sal_False ) const;
    VirtualDevice* GetVirDev( sal_Bool bCreate = sal_False ) const;
    OutputDevice& GetRefDev() const;
    inline Window* GetWin()    const { return pWin; }
    inline OutputDevice* GetOut()     const { return pOut; }

    static inline sal_Bool IsLstEndAction() { return ViewShell::bLstAct; }

    // Setzt Drucker fuer ALLE Sichten im Ring; einschl. Invalidierungen
//STRIP001     void SetPrt( SfxPrinter* );
    void SetVirDev( VirtualDevice* );

    //Andern alle PageDescriptoren
//STRIP001  void   ChgAllPageOrientation( sal_uInt16 eOri );
//STRIP001  void   ChgAllPageSize( Size &rSz );

    //Druckauftrag abwickeln.
    // pPDFOut != Null is: do PDF Export (no printing!)
    sal_Bool Prt( SwPrtOptions& rOptions, SfxProgress& rProgress,
                  OutputDevice *pPDFOut = NULL );
    //"Drucken" fuer OLE 2.0
//STRIP001     static void PrtOle2( SwDoc *pDoc, const SwViewOption *pOpt, SwPrtOptions& rOptions,
//STRIP001                       OutputDevice* pOleOut, const Rectangle& rRect );

    // creates temporary doc with selected text for PDF export
    SwDoc * CreatePrtDoc( SfxPrinter* pPrt, SvEmbeddedObjectRef &rDocShellRef );
    SwDoc * FillPrtDoc( SwDoc* pPrtDoc, const SfxPrinter* pPrt );

    //Wird intern fuer die Shell gerufen die Druckt. Formatiert die Seiten.
//STRIP001  void CalcPagesForPrint( sal_uInt16 nMax, SfxProgress* pProgress = 0,
//STRIP001      const String* pStr = NULL, sal_uInt32 nMergeAct = 0, sal_uInt32 nMergeCnt = 0 );

    //All about fields.
//STRIP001  void UpdateFlds(sal_Bool bCloseDB = sal_False);
//STRIP001  sal_Bool IsAnyFieldInDoc() const;
    // update all charts, for that exists any table
//STRIP001  void UpdateAllCharts();
//STRIP001  sal_Bool HasCharts() const;

    // Sollen Absatzabstaende addiert oder maximiert werden?
//STRIP001  sal_Bool IsParaSpaceMax() const;
//STRIP001  sal_Bool IsParaSpaceMaxAtPages() const;
//STRIP001  void SetParaSpaceMax( sal_Bool bNew, sal_Bool bAtPages );

    // compatible behaviour of tabs
//STRIP001     sal_Bool IsTabCompat() const;
//STRIP001     void SetTabCompat( sal_Bool bNew );

    //formatting by virtual device or printer
    sal_Bool IsUseVirtualDevice()const;
    void SetUseVirtualDevice(sal_Bool bSet);

    //Ruft den Idle-Formatierer des Layouts
    void LayoutIdle();

    inline const SwViewOption *GetViewOptions() const { return pOpt; }
    void  ApplyViewOptions( const SwViewOption &rOpt ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001         void  ApplyViewOptions( const SwViewOption &rOpt );
           void  SetUIOptions( const SwViewOption &rOpt );
//STRIP001         void  SetReadonlyOption(sal_Bool bSet);   // Readonly-Bit d. ViewOptions setzen
//STRIP001         void  SetPrtFormatOption(sal_Bool bSet);  // PrtFormat-Bit d. ViewOptions setzen
           void  SetReadonlySelectionOption(sal_Bool bSet);//change the selection mode in readonly docs

    const SwAccessibilityOptions* GetAccessibilityOptions() const { return pAccOptions;}

    static void           SetShellRes( ShellResource* pRes ) { pShellRes = pRes; }
    static ShellResource* GetShellRes() { return pShellRes; }

    static void           SetCareWin( Window* pNew ) { pCareWindow = pNew; }
    static Window*        GetCareWin(ViewShell& rVSh)
                        { return pCareWindow ? pCareWindow : CareChildWin(rVSh); }
    static Window*        CareChildWin(ViewShell& rVSh){DBG_BF_ASSERT(0, "STRIP"); return NULL;} ;//STRIP001    static Window*        CareChildWin(ViewShell& rVSh);

    inline SfxViewShell   *GetSfxViewShell() { return pSfxViewShell; }
    inline void           SetSfxViewShell(SfxViewShell *pNew) { pSfxViewShell = pNew; }

    // Selektion der Draw ::com::sun::star::script::Engine geaendert
    virtual void DrawSelChanged(SdrView*);

    // OD 12.12.2002 #103492#
    SwPagePreviewLayout* PagePreviewLayout();

    /** adjust view options for page preview

        OD 09.01.2003 #i6467#
        Because page preview should show the document as it is printed -
        page preview is print preview -, the view options are adjusted to the
        same as for printing.

        @param _rPrintOptions
        input parameter - constant reference to print options, to which the
        view option will be adjusted.
    */
    void AdjustOptionsForPagePreview( const SwPrtOptions &_rPrintOptions );

    // print page/print preview
    void PrintPreViewPage( SwPrtOptions& rOptions, sal_uInt16 nRowCol,
                           SfxProgress& rProgress,
                           const SwPagePreViewPrtData* = 0 );

    // Prospekt-Format drucken
//STRIP001  void PrintProspect( SwPrtOptions&, SfxProgress& );

    sal_Bool IsViewLocked() const { return bViewLocked; }
    void LockView( sal_Bool b )   { bViewLocked = b;    }

//STRIP001  inline void LockPaint();
//STRIP001         void ImplLockPaint();
//STRIP001  inline void UnlockPaint( sal_Bool bVirDev = sal_False );
//STRIP001         void ImplUnlockPaint( sal_Bool bVirDev );
           sal_Bool IsPaintLocked() const { return nLockPaint != 0; }

    // Abfragen/Erzeugen DrawView + PageView
    const sal_Bool HasDrawView() const;
    void MakeDrawView();

    //DrawView darf u.U. am UI benutzt werden.
          SdrView *GetDrawView();
    const SdrView *GetDrawView() const { return ((ViewShell*)this)->GetDrawView(); }

    //sorge dafuer, das auf jedenfall die MarkListe aktuell ist (Bug 57153)
//STRIP001  SdrView *GetDrawViewWithValidMarkList();

    // erfrage den Attribut Pool
    inline const SfxItemPool& GetAttrPool() const;
                 SfxItemPool& GetAttrPool();

    sal_Bool IsPreView() const { return bPreView; }

    sal_Bool IsFrameView()  const { return bFrameView; }
    void SetFrameView( const Size& rBrowseBorder )
        { bFrameView = sal_True; aBrowseBorder = rBrowseBorder; }

    //Nimmt die notwendigen Invalidierungen vor,
    //wenn sich der BrowdseModus aendert, bBrowseChgd == sal_True
    //oder, im BrowseModus, wenn sich die Groessenverhaeltnisse
    //aendern (bBrowseChgd == sal_False)
     void CheckBrowseView( FASTBOOL bBrowseChgd );

    //Damit in der UI nicht ueberall das dochxx includet werden muss
    sal_Bool IsBrowseMode() const;

//STRIP001  sal_Bool IsHeadInBrowse() const;
//STRIP001  void SetHeadInBrowse( sal_Bool bOn = sal_True );
//STRIP001  sal_Bool IsFootInBrowse() const;
//STRIP001  void SetFootInBrowse( sal_Bool bOn = sal_True );

    const Size& GetBrowseBorder() const{ return aBrowseBorder; }
    void SetBrowseBorder( const Size& rNew );

//STRIP001     ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible > CreateAccessible();

    // OD 15.01.2003 #103492# - change method signature due to new page preview
    // functionality.
//STRIP001     ::com::sun::star::uno::Reference<
//STRIP001         ::com::sun::star::accessibility::XAccessible >
//STRIP001             CreateAccessiblePreview();

//STRIP001  void ShowPreViewSelection( sal_uInt16 nSelPage );
//STRIP001  void InvalidateAccessibleFocus();

    //apply Accessiblity options
    void ApplyAccessiblityOptions(SvtAccessibilityOptions& rAccessibilityOptions);

    ViewShell( ViewShell&, Window *pWin = 0, OutputDevice *pOut = 0,
                long nFlags = 0 );
    ViewShell( SwDoc& rDoc, Window *pWin,
               const SwViewOption *pOpt = 0, OutputDevice *pOut = 0,
               long nFlags = 0 );
    virtual ~ViewShell();

};

//---- class CurrShell verwaltet den globalen ShellPointer -------------------

class CurrShell
{
public:
    ViewShell *pPrev;
    SwRootFrm *pRoot;

    CurrShell( ViewShell *pNew );
    ~CurrShell();
};

inline void ViewShell::ResetInvalidRect()
{
    aInvalidRect.Clear();
}
inline void ViewShell::StartAction()
{
    if ( !nStartAction++ )
        ImplStartAction();
}
inline void ViewShell::EndAction( const sal_Bool bIdleEnd )
{
    if( 0 == (nStartAction - 1) )
        ImplEndAction( bIdleEnd );
    --nStartAction;
}

//STRIP001 inline void ViewShell::LockPaint()
//STRIP001 {
//STRIP001  if ( !nLockPaint++ )
//STRIP001      ImplLockPaint();
//STRIP001 }
//STRIP001 inline void ViewShell::UnlockPaint( sal_Bool bVirDev )
//STRIP001 {
//STRIP001  if ( 0 == --nLockPaint )
//STRIP001      ImplUnlockPaint( bVirDev );
//STRIP001 }
inline const SfxItemPool& ViewShell::GetAttrPool() const
{
    return ((ViewShell*)this)->GetAttrPool();
}



} //namespace binfilter
#endif //_VIEWSH_HXX
