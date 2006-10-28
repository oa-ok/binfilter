/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLFootnoteBodyImportContext.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:10:35 $
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

#ifndef _XMLOFF_XMLFOOTNOTEBODYIMPORTCONTEXT_HXX_
#include "XMLFootnoteBodyImportContext.hxx"
#endif

#include "rtl/ustring.hxx"


#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif




namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::xml::sax::XAttributeList;


TYPEINIT1( XMLFootnoteBodyImportContext, SvXMLImportContext );

XMLFootnoteBodyImportContext::XMLFootnoteBodyImportContext(
    SvXMLImport& rImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName ) :
        SvXMLImportContext(rImport, nPrfx, rLocalName)
{
}

SvXMLImportContext* XMLFootnoteBodyImportContext::CreateChildContext(
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    // return text context
    SvXMLImportContext *pContext =
        GetImport().GetTextImport()->CreateTextChildContext(GetImport(),
                                                       nPrefix,
                                                       rLocalName,
                                                       xAttrList,
                                                       XML_TEXT_TYPE_FOOTNOTE);
    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );

    return pContext;
}
}//end of namespace binfilter
