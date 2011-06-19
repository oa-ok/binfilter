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

#include "svdundo.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "scene3d.hxx"


namespace binfilter {

/*N*/ SdrUndoGroup::SdrUndoGroup(SdrModel& rNewMod)
/*N*/ : SdrUndoAction(rNewMod),
/*N*/   aBuf(1024,32,32),
/*N*/   eFunction(SDRREPFUNC_OBJ_NONE)      /*#72642#*/
/*N*/ {}

/*N*/ SdrUndoGroup::~SdrUndoGroup()
/*N*/ {
/*N*/   Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::Clear()
/*N*/ {
/*N*/   for (ULONG nu=0; nu<GetActionCount(); nu++) {
/*N*/       SdrUndoAction* pAct=GetAction(nu);
/*N*/       delete pAct;
/*N*/   }
/*N*/   aBuf.Clear();
/*N*/ }

/*N*/ void SdrUndoGroup::AddAction(SdrUndoAction* pAct)
/*N*/ {
/*N*/   aBuf.Insert(pAct,CONTAINER_APPEND);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// OBJECTS
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoObj::SdrUndoObj(SdrObject& rNewObj):
/*N*/   SdrUndoAction(*rNewObj.GetModel()),
/*N*/   pObj(&rNewObj)
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoGeoObj::SdrUndoGeoObj(SdrObject& rNewObj):
/*N*/   SdrUndoObj(rNewObj),
/*N*/   pUndoGeo(NULL),
/*N*/   pRedoGeo(NULL),
/*N*/   pUndoGroup(NULL)
/*N*/ {
/*N*/   SdrObjList* pOL=rNewObj.GetSubList();
/*N*/   if (pOL!=NULL && pOL->GetObjCount() && !rNewObj.ISA(E3dScene))
/*N*/   {
/*?*/       // Aha, Gruppenobjekt
/*?*/       // AW: Aber keine 3D-Szene, dann nur fuer die Szene selbst den Undo anlegen
/*?*/       pUndoGroup=new SdrUndoGroup(*pObj->GetModel());
/*?*/       ULONG nObjAnz=pOL->GetObjCount();
/*?*/       for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
/*?*/           pUndoGroup->AddAction(new SdrUndoGeoObj(*pOL->GetObj(nObjNum)));
/*?*/       }
/*N*/   } else {
/*N*/       pUndoGeo=pObj->GetGeoData();
/*N*/   }
/*N*/ }

/*N*/ SdrUndoGeoObj::~SdrUndoGeoObj()
/*N*/ {
/*N*/   if (pUndoGeo!=NULL) delete pUndoGeo;
/*N*/   if (pRedoGeo!=NULL) delete pRedoGeo;
/*N*/   if (pUndoGroup!=NULL) delete pUndoGroup;
/*N*/ }

/*N*/ SdrUndoObjList::SdrUndoObjList(SdrObject& rNewObj, bool bOrdNumDirect):
/*N*/   SdrUndoObj(rNewObj),
/*N*/   bOwner(FALSE),
/*N*/   pView(NULL),
/*N*/   pPageView(NULL)
/*N*/ {
/*N*/   pObjList=pObj->GetObjList();
/*N*/   if (bOrdNumDirect) {
/*?*/       nOrdNum=pObj->GetOrdNumDirect();
/*N*/   } else {
/*N*/       nOrdNum=pObj->GetOrdNum();
/*N*/   }
/*N*/ }
/*N*/
/*N*/ SdrUndoObjList::~SdrUndoObjList()
/*N*/ {
/*N*/   if (pObj!=NULL && IsOwner())
/*N*/   {
/*N*/       // Attribute muessen wieder in den regulaeren Pool
/*?*/       DBG_BF_ASSERT(0, "STRIP");
/*?*/
/*?*/       // nun loeschen
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PAGES
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrUndoPage::SdrUndoPage(SdrPage& rNewPg):
/*N*/   SdrUndoAction(*rNewPg.GetModel()), pPage(&rNewPg)
/*N*/ { }

/*N*/ SdrUndoPageList::SdrUndoPageList(SdrPage& rNewPg):
/*N*/   SdrUndoPage(rNewPg),
/*N*/   bItsMine(FALSE)
/*N*/ {
/*N*/   nPageNum=rNewPg.GetPageNum();
/*N*/ }

/*N*/ SdrUndoPageList::~SdrUndoPageList()
/*N*/ {
/*N*/   if(bItsMine && pPage)
/*N*/   {
/*?*/       delete pPage;
/*?*/       pPage = 0L;
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
