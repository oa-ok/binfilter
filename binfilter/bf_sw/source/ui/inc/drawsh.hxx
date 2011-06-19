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

#ifndef _SWDRAWSH_HXX
#define _SWDRAWSH_HXX

#include "drwbassh.hxx"
namespace binfilter {

class SdrObject;
class SwDrawBaseShell;

class SwDrawShell: public SwDrawBaseShell
{
public:
    SFX_DECL_INTERFACE(SW_DRAWSHELL);

    SwDrawShell(SwView &rView):SwDrawBaseShell(rView){DBG_BF_ASSERT(0, "STRIP");} ;

    void        Execute(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");};
    void        ExecDrawDlg(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");};
    void        ExecDrawAttrArgs(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");};
    void        GetDrawAttrState(SfxItemSet &rSet){DBG_BF_ASSERT(0, "STRIP");};

    void        ExecFormText(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");};
    void        GetFormTextState(SfxItemSet& rSet){DBG_BF_ASSERT(0, "STRIP");};
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
