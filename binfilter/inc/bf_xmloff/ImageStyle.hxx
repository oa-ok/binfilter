/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ImageStyle.hxx,v $
 * $Revision: 1.4 $
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

#ifndef _XMLOFF_IMAGESTYLE_HXX
#define _XMLOFF_IMAGESTYLE_HXX

#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLAttributeList;
class SvXMLUnitConverter;
class SvXMLExport;
class SvXMLImport;

class XMLImageStyle
{
public:
    XMLImageStyle();
    ~XMLImageStyle();

    sal_Bool exportXML( const ::rtl::OUString& rStrName, const ::com::sun::star::uno::Any& rValue, SvXMLExport& rExport );
    sal_Bool importXML( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList, ::com::sun::star::uno::Any& rValue, ::rtl::OUString& rStrName, SvXMLImport& rImport );

private:

    sal_Bool ImpExportXML( const ::rtl::OUString& rStrName, const ::com::sun::star::uno::Any& rValue,
                           SvXMLExport& rExport );
    sal_Bool ImpImportXML( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                           ::com::sun::star::uno::Any& rValue, ::rtl::OUString& rStrName,
                           SvXMLImport& rImport );
};

}//end of namespace binfilter
#endif // _XMLOFF_IMAGESTYLE_HXX
