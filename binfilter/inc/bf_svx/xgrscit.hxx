/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xgrscit.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:33:47 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _SVX_XGRSCIT_HXX
#define _SVX_XGRSCIT_HXX

#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* GradientenSchritte-Item fuer Gradienten-Fuellungen
|*
\************************************************************************/

class XGradientStepCountItem: public SfxUInt16Item
{
public:
                            TYPEINFO();
                            XGradientStepCountItem( USHORT nStepCount = 0 );
                            XGradientStepCountItem( SvStream& rIn );
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = NULL ) const;
    virtual SfxPoolItem*    Create( SvStream& rIn, USHORT nVer ) const;
//STRIP001  virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
//STRIP001                                  SfxMapUnit eCoreMetric,
//STRIP001                                  SfxMapUnit ePresMetric,
//STRIP001                                     String &rText, const IntlWrapper * = 0 ) const;
};

}//end of namespace binfilter
#endif
