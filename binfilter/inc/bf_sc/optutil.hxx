/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: optutil.hxx,v $
 * $Revision: 1.5 $
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

#ifndef SC_OPTUTIL_HXX
#define SC_OPTUTIL_HXX

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
namespace binfilter {


class ScOptionsUtil
{
public:
    static BOOL     IsMetricSystem();
};


//  ConfigItem for classes that use items from several sub trees

class ScLinkConfigItem : public ::utl::ConfigItem
{
    Link    aCommitLink;

public:
            ScLinkConfigItem( const ::rtl::OUString rSubTree );
    void    SetCommitLink( const Link& rLink );


    void    SetModified()   { ConfigItem::SetModified(); }
    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>
            GetProperties(const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames)
                            { return ConfigItem::GetProperties( rNames ); }
    sal_Bool PutProperties( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames,
                            const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>& rValues)
                            { return ConfigItem::PutProperties( rNames, rValues ); }
    sal_Bool EnableNotification(::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames)
                            { return ConfigItem::EnableNotification( rNames ); }

    ::com::sun::star::uno::Sequence< ::rtl::OUString > GetNodeNames(::rtl::OUString& rNode)
                            { return ConfigItem::GetNodeNames( rNode ); }
    virtual void                Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
    virtual void                Commit();
};

} //namespace binfilter
#endif


