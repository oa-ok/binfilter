/*************************************************************************
 *
 *  $RCSfile: sch_chtmode8.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:55:58 $
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

#include "chtmodel.hxx"

/*
  ------------------------------------------------------------
  Some Information about chart types. This may be used as a
  basis for creating some chart classes (!)  with
  corresponding members.
  ------------------------------------------------------------

        Styles                     Basic:        Perc  Stack  Bar  3D   Symbols Net Axis sign neg. spline  XY Stat.

CHSTYLE_2D_LINE,                   Line           -      -     -     -      -     -    -   x    x    -       -   x
CHSTYLE_2D_STACKEDLINE,            Line           -      x     -     -      -     -    -   x    x    -       -   -
CHSTYLE_2D_PERCENTLINE,            Line           x      x     -     -      -     -    -   -    x    -       -   -
CHSTYLE_2D_COLUMN,                 Column         -      -     -     -      -     -    -   x    x    -       -   x
CHSTYLE_2D_STACKEDCOLUMN,          Column         -      x     -     -      -     -    -   x    x    -       -   -
CHSTYLE_2D_PERCENTCOLUMN,          Column         x      x     -     -      -     -    -   -    x    -       -   -
CHSTYLE_2D_BAR,                    *Column        -      -     x     -      -     -    -   x    x    -       -   x
CHSTYLE_2D_STACKEDBAR,             *Column        -      x     x     -      -     -    -   x    x    -       -   -
CHSTYLE_2D_PERCENTBAR,             *Column        x      x     x     -      -     -    -   -    x    -       -   -
CHSTYLE_2D_AREA,                   Area           -      -     -     -      -     -    -   x    x    -       -   -
CHSTYLE_2D_STACKEDAREA,            Area           -      x     -     -      -     -    -   x    x    -       -   -
CHSTYLE_2D_PERCENTAREA,            Area           x      x     -     -      -     -    x   -    x    -       -   -
CHSTYLE_2D_PIE,                    Pie            x      x     -     -      -     -    -   -    x    -       -   -
CHSTYLE_3D_STRIPE,                 Stripe?        -      -     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_COLUMN,                 Column         -      -     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_FLATCOLUMN,             Column?        -      -     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_STACKEDFLATCOLUMN       Column         -      x     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_PERCENTFLATCOLUMN       Column         x      x     -     x      -     -    -   -    x    -       -   -
CHSTYLE_3D_AREA,                   Area           -      -     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_STACKEDAREA,            Area           -      x     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_PERCENTAREA,            Area           x      x     -     x      -     -    -   -    -    -       -   -
CHSTYLE_3D_SURFACE,                Surface        -      -     -     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_PIE,                    Pie            x      x     ?     x      -     -    x   -    x    -       -   -
CHSTYLE_2D_XY,                     XYZ            -      -     -     -      -     -    -   x    x    -       x   x
CHSTYLE_3D_XYZ,                    XYZ            -      -     -     x      -     -    -   x    x    -       x   -
CHSTYLE_2D_LINESYMBOLS,            Line           -      -     -     -      x     -    -   x    x    -       -   x
CHSTYLE_2D_STACKEDLINESYM,         Line           -      x     -     -      x     -    -   x    x    -       -   -
CHSTYLE_2D_PERCENTLINESYM,         Line           x      x     -     -      x     -    -   -    x    -       -   -
CHSTYLE_2D_XYSYMBOLS,              XYZ            -      -     -     -      x     -    -   x    x    -       x   x
CHSTYLE_3D_XYZSYMBOLS,             XYZ            -      -     -     x      x     -    -   x    x    -       x   -
CHSTYLE_2D_DONUT1,                 *PIE           ?      ?     ?     -      -     -    x   -    x    -       -   -
CHSTYLE_2D_DONUT2,                 *PIE           ?      ?     ?     -      -     -    x   -    x    -       -   -
CHSTYLE_3D_BAR,                    *Column        -      -     x     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_FLATBAR,                *Column        -      -     x     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_STACKEDFLATBAR,         *Column        -      x     x     x      -     -    -   x    x    -       -   -
CHSTYLE_3D_PERCENTFLATBAR,         *Column        x      x     x     x      -     -    -   -    x    -       -   -
CHSTYLE_2D_PIE_SEGOF1,             PIE            x      x     ?     -      -     -    x   -    x    -       -   -
CHSTYLE_2D_PIE_SEGOFALL,           PIE            x      x     ?     -      -     -    x   -    x    -       -   -
CHSTYLE_2D_NET,                    Net            -      -     -     -      -     x    -   x    x    -       -   -
CHSTYLE_2D_NET_SYMBOLS,            Net            -      -     -     -      x     x    -   x    x    -       -   -
CHSTYLE_2D_NET_STACK,              Net            -      x     -     -      -     x    -   x    x    -       -   -
CHSTYLE_2D_NET_SYMBOLS_STACK,      Net            -      x     -     -      x     x    -   x    x    -       -   -
CHSTYLE_2D_NET_PERCENT,            Net            x      x     -     -      -     x    -   -    x    -       -   -
CHSTYLE_2D_NET_SYMBOLS_PERCENT,    Net            x      x     -     -      x     x    -   -    x    -       -   -
CHSTYLE_2D_CUBIC_SPLINE,           SplineC        -      -     -     -      -     -    -   x    x    C       -   x
CHSTYLE_2D_CUBIC_SPLINE_SYMBOL,    SplineC        -      -     -     -      x     -    -   x    x    C       -   x
CHSTYLE_2D_B_SPLINE,               SplineB        -      -     -     -      -     -    -   x    x    B       -   x
CHSTYLE_2D_B_SPLINE_SYMBOL,        SplineB        -      -     -     -      x     -    -   x    x    B       -   x
CHSTYLE_2D_CUBIC_SPLINE_XY,        SplineC        -      -     -     -      -     -    -   x    x    C       x   x
CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY, SplineC        -      -     -     -      x     -    -   x    x    C       x   x
CHSTYLE_2D_B_SPLINE_XY,            SplineB        -      -     -     -      -     -    -   x    x    B       x   x
CHSTYLE_2D_B_SPLINE_SYMBOL_XY,     SplineB        -      -     -     -      x     -    -   x    x    B       x   x
CHSTYLE_2D_XY_LINE,                Line_&_XYZ     -      -     -     -      -     -    -   x    x    -       x   -
CHSTYLE_2D_LINE_COLUMN,            Column+1_Line  -      -     -     -      -     -    -   x    x    -       -   -
CHSTYLE_2D_LINE_STACKEDCOLUMN Column+1_Line - x - - - - - x x - - - */

// meaning supports symbols
/*N*/ BOOL ChartModel::HasSymbols(const long nRow) const
/*N*/ {
/*N*/
/*N*/   switch(eChartStyle)
/*N*/   {
/*N*/       case CHSTYLE_2D_STOCK_1:
/*N*/       case CHSTYLE_2D_STOCK_2:
/*N*/
/*N*/
/*N*/
/*N*/       case CHSTYLE_2D_XY :
/*N*/           DBG_TRACE("ChartModel::HasSymbols:Achtung, neuer Typ, ungetestet");
/*N*/
/*N*/       case CHSTYLE_2D_LINESYMBOLS:
/*N*/       case CHSTYLE_2D_STACKEDLINESYM:
/*N*/       case CHSTYLE_2D_PERCENTLINESYM:
/*N*/       case CHSTYLE_2D_XYSYMBOLS:
/*N*/       case CHSTYLE_3D_XYZSYMBOLS:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_STACK:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_PERCENT:
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL:
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL:
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY:
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL_XY:
/*N*/           return TRUE;
/*N*/           break;
/*N*/
/*N*/       case CHSTYLE_2D_STOCK_3:
/*N*/       case CHSTYLE_2D_STOCK_4:
/*?*/           return (nRow!=0);
/*N*/
/*N*/       case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_LINE_COLUMN:
/*N*/           if(nRow >= (GetRowCount() - nNumLinesInColChart))
/*N*/               return TRUE;
/*N*/           return FALSE;
/*N*/           break;
/*N*/
/*N*/       default:
/*N*/           break;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ChartModel::IsLine(const long nRow) const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_STOCK_3:
/*N*/       case CHSTYLE_2D_STOCK_4:
/*?*/           return nRow ? TRUE : FALSE;
/*N*/
/*N*/       case CHSTYLE_2D_STOCK_1:
/*N*/       case CHSTYLE_2D_STOCK_2:
/*N*/
/*N*/       // lines and symbol types
/*N*/       case CHSTYLE_2D_XY :
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_STACK :
/*N*/       case CHSTYLE_2D_NET_SYMBOLS :
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_PERCENT :
/*N*/       case CHSTYLE_2D_LINESYMBOLS:
/*N*/       case CHSTYLE_2D_STACKEDLINESYM:
/*N*/       case CHSTYLE_2D_PERCENTLINESYM:
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL:
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL:
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY:
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL_XY:
/*N*/
/*N*/       // lines only
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_XY :
/*N*/       case CHSTYLE_2D_B_SPLINE_XY :
/*N*/       case CHSTYLE_2D_LINE :
/*N*/       case CHSTYLE_2D_STACKEDLINE :
/*N*/       case CHSTYLE_2D_PERCENTLINE :
/*N*/       case CHSTYLE_2D_NET :
/*N*/       case CHSTYLE_2D_NET_STACK :
/*N*/       case CHSTYLE_2D_NET_PERCENT :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE :
/*N*/       case CHSTYLE_2D_B_SPLINE :
/*N*/       case CHSTYLE_2D_XY_LINE :
/*N*/           return TRUE;
/*N*/
/*N*/       case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_LINE_COLUMN:
/*N*/           if( nRow >= (GetRowCount() - nNumLinesInColChart))
/*N*/               return ( GetRowCount() > 1 ); // only one series => must be a bar
/*N*/           return FALSE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

// for all types which return TRUE here it is assumed
// that toggling bSwitchColRow is allowed
/*N*/ BOOL ChartModel::IsBar() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_BAR:
/*N*/       case CHSTYLE_2D_STACKEDBAR:
/*N*/       case CHSTYLE_2D_PERCENTBAR:
/*N*/       case CHSTYLE_3D_BAR:
/*N*/       case CHSTYLE_3D_FLATBAR:
/*N*/       case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/       case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }
/*N*/ BOOL ChartModel::IsCol(long nRow) const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_COLUMN:
/*N*/       case CHSTYLE_2D_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/       case CHSTYLE_3D_COLUMN:
/*N*/       case CHSTYLE_3D_FLATCOLUMN:
/*N*/       case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/           return TRUE;
/*N*/
/*N*/       case CHSTYLE_2D_STOCK_3:
/*N*/       case CHSTYLE_2D_STOCK_4:
/*?*/           return nRow ? FALSE : TRUE ;
/*N*/
/*N*/       case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_LINE_COLUMN:
/*N*/           return ! (nRow >= (GetRowCount() - nNumLinesInColChart));
/*N*/
/*N*/       default:
/*?*/           return FALSE;
/*N*/   }
/*N*/ }

//STRIP001 bool ChartModel::IsFlat3DChart() const
//STRIP001 {
//STRIP001     switch( eChartStyle )
//STRIP001     {
//STRIP001      case CHSTYLE_3D_FLATCOLUMN:
//STRIP001      case CHSTYLE_3D_FLATBAR:
//STRIP001      case CHSTYLE_3D_STACKEDFLATCOLUMN:
//STRIP001      case CHSTYLE_3D_STACKEDFLATBAR:
//STRIP001      case CHSTYLE_3D_PERCENTFLATCOLUMN:
//STRIP001      case CHSTYLE_3D_PERCENTFLATBAR:
//STRIP001             return true;
//STRIP001
//STRIP001         default:
//STRIP001             return false;
//STRIP001     }
//STRIP001 }

/*N*/ BOOL ChartModel::Is3DChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_3D_STRIPE:
/*N*/       case CHSTYLE_3D_COLUMN:
/*N*/       case CHSTYLE_3D_BAR:
/*N*/       case CHSTYLE_3D_FLATCOLUMN:
/*N*/       case CHSTYLE_3D_FLATBAR:
/*N*/       case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/       case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/       case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/       case CHSTYLE_3D_AREA:
/*N*/       case CHSTYLE_3D_STACKEDAREA:
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/       case CHSTYLE_3D_SURFACE:
/*N*/       case CHSTYLE_3D_PIE:
/*N*/       // new since 380 Build 1502, but still not supported
/*N*/       case CHSTYLE_3D_XYZ:
/*N*/       case CHSTYLE_3D_XYZSYMBOLS:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsStackedChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_STACKEDLINE:
/*N*/       case CHSTYLE_2D_PERCENTLINE:
/*N*/       case CHSTYLE_2D_STACKEDAREA:
/*N*/       case CHSTYLE_2D_PERCENTAREA:
/*N*/       case CHSTYLE_2D_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/       case CHSTYLE_2D_STACKEDBAR:
/*N*/       case CHSTYLE_2D_PERCENTBAR:
/*N*/       case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/       case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/       case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/       case CHSTYLE_3D_STACKEDAREA:
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/       case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsStacked() const
/*N*/ {
/*N*/   if( IsPercent() )              // percent => stacked
/*N*/       return TRUE;
/*N*/
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_STACKEDBAR:
/*N*/       case CHSTYLE_2D_STACKEDLINE:
/*N*/       case CHSTYLE_2D_STACKEDAREA:
/*N*/       case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/       case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/       case CHSTYLE_3D_STACKEDAREA:
/*N*/       case CHSTYLE_2D_STACKEDLINESYM:
/*N*/       case CHSTYLE_2D_NET_STACK:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_STACK:
/*N*/       case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsPercentChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_PERCENTLINE:
/*N*/       case CHSTYLE_2D_PERCENTAREA:
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/       case CHSTYLE_2D_PERCENTBAR:
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsPercent() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/       case CHSTYLE_2D_PERCENTBAR:
/*N*/       case CHSTYLE_2D_PERCENTLINE:
/*N*/       case CHSTYLE_2D_PERCENTAREA:
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/       case CHSTYLE_2D_NET_PERCENT:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_PERCENT:
/*N*/       case CHSTYLE_2D_PERCENTLINESYM:
/*N*/       case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsArea(long nRow)
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_AREA:
/*N*/       case CHSTYLE_2D_STACKEDAREA:
/*N*/       case CHSTYLE_2D_PERCENTAREA:
/*N*/       case CHSTYLE_3D_AREA:
/*N*/       case CHSTYLE_3D_STACKEDAREA:
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsAxisChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_DONUT1:
/*N*/       case CHSTYLE_2D_DONUT2:
/*N*/       case CHSTYLE_2D_PIE:
/*N*/       case CHSTYLE_2D_PIE_SEGOF1:
/*N*/       case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/       case CHSTYLE_3D_PIE:
/*N*/           return FALSE;
/*N*/
/*N*/       default:
/*N*/           return TRUE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsNegativeChart( SvxChartStyle* pStyle ) const
/*N*/ {
/*N*/   switch( pStyle? *pStyle: eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/           return FALSE;
/*N*/
/*N*/       default:
/*N*/           return TRUE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsSignedChart( SvxChartStyle* pStyle ) const
/*N*/ {
/*N*/   switch( pStyle? *pStyle: eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_3D_PIE :
/*N*/       case CHSTYLE_2D_PIE :
/*N*/       case CHSTYLE_2D_PIE_SEGOF1:
/*N*/       case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/       case CHSTYLE_2D_DONUT1:
/*N*/       case CHSTYLE_2D_DONUT2:
/*N*/       case CHSTYLE_2D_PERCENTLINE :
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN :
/*N*/       case CHSTYLE_2D_PERCENTAREA :
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN :
/*N*/       case CHSTYLE_3D_PERCENTAREA :
/*N*/       case CHSTYLE_2D_PERCENTBAR :
/*N*/           return FALSE;
/*N*/
/*N*/       default :
/*N*/           return TRUE;
/*N*/   }
/*N*/ }

//STRIP001 BOOL ChartModel::IsPieOrDonutChart() const
//STRIP001 {
//STRIP001  switch( eChartStyle )
//STRIP001  {
//STRIP001      case CHSTYLE_3D_PIE :
//STRIP001      case CHSTYLE_2D_PIE :
//STRIP001      case CHSTYLE_2D_PIE_SEGOF1:
//STRIP001      case CHSTYLE_2D_PIE_SEGOFALL:
//STRIP001      case CHSTYLE_2D_DONUT1:
//STRIP001      case CHSTYLE_2D_DONUT2:
//STRIP001          return TRUE;
//STRIP001
//STRIP001      default:
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001 }

/*N*/ BOOL ChartModel::IsPieChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_3D_PIE :
/*N*/       case CHSTYLE_2D_PIE :
/*N*/       case CHSTYLE_2D_PIE_SEGOF1:
/*N*/       case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/           return TRUE;
/*N*/
/*N*/       default:
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsXYChart( SvxChartStyle* pStyle ) const
/*N*/ {
/*N*/   // if pStyle == NULL (default) the current style of 'this' is used
/*N*/
/*N*/   switch( pStyle? *pStyle: eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_XY :
/*N*/       case CHSTYLE_3D_XYZ :
/*N*/       case CHSTYLE_2D_XYSYMBOLS :
/*N*/       case CHSTYLE_3D_XYZSYMBOLS :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_XY :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
/*N*/       case CHSTYLE_2D_B_SPLINE_XY :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :
/*N*/       case CHSTYLE_2D_XY_LINE :
/*N*/           return TRUE;
/*N*/
/*N*/       case CHSTYLE_ADDIN:
/*N*/           return TRUE;
/*N*/
/*N*/       default :
/*N*/           return FALSE;
/*N*/   }
/*N*/ }


/*N*/ BOOL ChartModel::IsSplineChart () const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL :
/*N*/       case CHSTYLE_2D_B_SPLINE :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_XY :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
/*N*/       case CHSTYLE_2D_B_SPLINE_XY :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :
/*N*/           return TRUE;
/*N*/
/*N*/       default :
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsStatisticChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_BAR :
/*N*/       case CHSTYLE_2D_B_SPLINE :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :
/*N*/       case CHSTYLE_2D_B_SPLINE_XY :
/*N*/       case CHSTYLE_2D_COLUMN :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_XY :
/*N*/       case CHSTYLE_2D_LINE :
/*N*/       case CHSTYLE_2D_LINESYMBOLS :
/*N*/       case CHSTYLE_2D_STOCK_1:
/*N*/       case CHSTYLE_2D_STOCK_2:
/*N*/       case CHSTYLE_2D_STOCK_3:
/*N*/       case CHSTYLE_2D_STOCK_4:
/*N*/       case CHSTYLE_2D_XY :
/*N*/       case CHSTYLE_2D_XYSYMBOLS :
/*N*/       case CHSTYLE_2D_XY_LINE :
/*N*/           return TRUE;
/*N*/
/*N*/       default :
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::IsNetChart() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_NET :
/*N*/       case CHSTYLE_2D_NET_SYMBOLS :
/*N*/       case CHSTYLE_2D_NET_STACK :
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_STACK :
/*N*/       case CHSTYLE_2D_NET_PERCENT :
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_PERCENT :
/*N*/           return TRUE;
/*N*/
/*N*/       default :
/*N*/           return FALSE;
/*N*/   }
/*N*/ }

// ========================================
// return base type
// ========================================

/*N*/ long ChartModel::GetBaseType() const
/*N*/ {
/*N*/   switch( eChartStyle )
/*N*/   {
/*N*/       case CHSTYLE_2D_B_SPLINE :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL :
/*N*/       case CHSTYLE_2D_LINE:
/*N*/       case CHSTYLE_2D_STACKEDLINE:
/*N*/       case CHSTYLE_2D_PERCENTLINE:
/*N*/       case CHSTYLE_2D_LINESYMBOLS:
/*N*/       case CHSTYLE_2D_STACKEDLINESYM:
/*N*/       case CHSTYLE_2D_PERCENTLINESYM:
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL :
/*N*/       case CHSTYLE_3D_STRIPE:
/*N*/           return CHTYPE_LINE;
/*N*/
/*N*/       case CHSTYLE_2D_AREA:
/*N*/       case CHSTYLE_2D_STACKEDAREA:
/*N*/       case CHSTYLE_2D_PERCENTAREA:
/*N*/       case CHSTYLE_3D_AREA:
/*N*/       case CHSTYLE_3D_STACKEDAREA:
/*N*/       case CHSTYLE_3D_PERCENTAREA:
/*N*/           return CHTYPE_AREA;
/*N*/
/*N*/       case CHSTYLE_2D_PIE:
/*N*/       case CHSTYLE_2D_PIE_SEGOF1:
/*N*/       case CHSTYLE_2D_PIE_SEGOFALL:
/*N*/       case CHSTYLE_3D_PIE:
/*N*/           return CHTYPE_CIRCLE;
/*N*/
/*N*/       case CHSTYLE_2D_DONUT1:
/*N*/       case CHSTYLE_2D_DONUT2:
/*?*/           return CHTYPE_DONUT;
/*N*/
/*N*/       case CHSTYLE_2D_B_SPLINE_XY :
/*N*/       case CHSTYLE_2D_XY_LINE :
/*N*/       case CHSTYLE_2D_B_SPLINE_SYMBOL_XY :
/*N*/       case CHSTYLE_2D_XYSYMBOLS:
/*N*/       case CHSTYLE_2D_XY:
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_XY :
/*N*/       case CHSTYLE_2D_CUBIC_SPLINE_SYMBOL_XY :
/*N*/           return CHTYPE_XY;
/*N*/
/*N*/       case CHSTYLE_2D_NET:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS:
/*N*/       case CHSTYLE_2D_NET_STACK:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_STACK:
/*N*/       case CHSTYLE_2D_NET_PERCENT:
/*N*/       case CHSTYLE_2D_NET_SYMBOLS_PERCENT:
/*N*/           return CHTYPE_NET;
/*N*/
/*N*/       case CHSTYLE_2D_COLUMN:
/*N*/       case CHSTYLE_2D_STACKEDCOLUMN:
/*N*/       case CHSTYLE_2D_PERCENTCOLUMN:
/*N*/       case CHSTYLE_2D_LINE_COLUMN:
/*N*/       case CHSTYLE_2D_LINE_STACKEDCOLUMN:
/*N*/       case CHSTYLE_3D_COLUMN:
/*N*/       case CHSTYLE_3D_FLATCOLUMN:
/*N*/       case CHSTYLE_3D_STACKEDFLATCOLUMN:
/*N*/       case CHSTYLE_3D_PERCENTFLATCOLUMN:
/*N*/           return CHTYPE_COLUMN;
/*N*/
/*N*/       case CHSTYLE_2D_STOCK_1:
/*N*/       case CHSTYLE_2D_STOCK_2:
/*N*/       case CHSTYLE_2D_STOCK_3:
/*N*/       case CHSTYLE_2D_STOCK_4:
/*N*/           return CHTYPE_STOCK;
/*N*/
/*N*/       case CHSTYLE_2D_BAR:
/*N*/       case CHSTYLE_2D_STACKEDBAR:
/*N*/       case CHSTYLE_2D_PERCENTBAR:
/*N*/       case CHSTYLE_3D_BAR:
/*N*/       case CHSTYLE_3D_FLATBAR:
/*N*/       case CHSTYLE_3D_STACKEDFLATBAR:
/*N*/       case CHSTYLE_3D_PERCENTFLATBAR:
/*N*/           return CHTYPE_BAR;
/*N*/
/*N*/       case CHSTYLE_ADDIN:
/*?*/           return CHTYPE_ADDIN;
/*N*/
/*N*/       default:
/*?*/           DBG_ERROR( "Invalid Chart style given!" );
/*?*/           return CHTYPE_INVALID;
/*N*/   }
/*N*/ }

/*N*/ BOOL ChartModel::SetBaseType(long nBaseType)
/*N*/ {
/*N*/   // setting the basetype currently sets the default type in the base category
/*N*/   // returns TRUE, iff chart type has been changed
/*N*/
/*N*/   SvxChartStyle eNewStyle = eChartStyle;
/*N*/
/*N*/   switch( nBaseType )
/*N*/   {
/*N*/       case CHTYPE_LINE:
/*N*/           eNewStyle = CHSTYLE_2D_LINE;
/*N*/           break;
/*N*/       case CHTYPE_AREA:
/*N*/           eNewStyle = CHSTYLE_2D_AREA;
/*N*/           break;
/*N*/       case CHTYPE_DONUT:
/*?*/           eNewStyle = CHSTYLE_2D_DONUT1;
/*?*/           break;
/*N*/       case CHTYPE_CIRCLE:
/*N*/           eNewStyle = CHSTYLE_2D_PIE;
/*N*/           break;
/*N*/       case CHTYPE_XY:
/*N*/           eNewStyle = CHSTYLE_2D_XY;
/*N*/           break;
/*N*/       case CHTYPE_NET:
/*N*/           eNewStyle = CHSTYLE_2D_NET;
/*N*/           break;
/*N*/       case CHTYPE_COLUMN: // == BAR
/*N*/       case CHTYPE_BAR:
/*N*/           eNewStyle = CHSTYLE_2D_COLUMN;
/*N*/           break;
/*N*/       case CHTYPE_STOCK:
/*N*/           eNewStyle = CHSTYLE_2D_STOCK_1;
/*N*/           break;
/*N*/       case CHTYPE_ADDIN:
/*?*/           eNewStyle = CHSTYLE_ADDIN;
/*?*/           break;
/*?*/       default:
/*?*/           DBG_ERROR( "ChartModel::SetBaseType: Invalid Type!" );
/*?*/           break;
/*N*/   }
/*N*/
/*N*/   if( eChartStyle != eNewStyle )
/*N*/   {
/*N*/       ChangeChart( eNewStyle );
/*N*/       BuildChart( FALSE );
/*N*/       return TRUE;
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

