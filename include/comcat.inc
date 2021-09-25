.pragma list(push, 0)

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __comcat_h__
define __comcat_h__
include unknwn.inc
ifndef __PE__
.pragma comment(lib, uuid)
endif

externdef CLSID_StdComponentCategoriesMgr:CLSID

CATID		typedef GUID
REFCATID	typedef REFGUID

IID_IEnumCLSID	equ <IID_IEnumGUID>
IEnumCLSID	equ <IEnumGUID>
LPENUMCLSID	equ <LPENUMGUID>
CATID_NULL	equ <GUID_NULL>

IsEqualCATID macro rcatid1, rcatid2
      exitm<IsEqualGUID(rcatid1, rcatid2)>
      endm

IID_IEnumCATID	equ <IID_IEnumGUID>
IEnumCATID	equ <IEnumGUID>

;;  Category IDs (link to uuid3.lib)
externdef CATID_Insertable:CATID
externdef CATID_Control:CATID
externdef CATID_Programmable:CATID
externdef CATID_IsShortcut:CATID
externdef CATID_NeverShowExt:CATID
externdef CATID_DocObject:CATID
externdef CATID_Printable:CATID
externdef CATID_RequiresDataPathHost:CATID
externdef CATID_PersistsToMoniker:CATID
externdef CATID_PersistsToStorage:CATID
externdef CATID_PersistsToStreamInit:CATID
externdef CATID_PersistsToStream:CATID
externdef CATID_PersistsToMemory:CATID
externdef CATID_PersistsToFile:CATID
externdef CATID_PersistsToPropertyBag:CATID
externdef CATID_InternetAware:CATID
externdef CATID_DesignTimeUIActivatableControl:CATID

ifndef _LPENUMGUID_DEFINED
define _LPENUMGUID_DEFINED

ifndef __IEnumGUID_INTERFACE_DEFINED__
define __IEnumGUID_INTERFACE_DEFINED__

LPENUMGUID typedef ptr IEnumGUID

DEFINE_IIDX(IEnumGUID, "0002E000-0000-0000-C000-000000000046")

.comdef IEnumGUID : public IUnknown

    Next		proc
    Skip		proc
    Reset		proc
    Clone		proc

    .ends

endif
endif

ifndef _LPENUMCATEGORYINFO_DEFINED
define _LPENUMCATEGORYINFO_DEFINED

ifndef __IEnumCATEGORYINFO_INTERFACE_DEFINED__
define __IEnumCATEGORYINFO_INTERFACE_DEFINED__

LPENUMCATEGORYINFO typedef ptr IEnumCATEGORYINFO

CATEGORYINFO	STRUC
catid		CATID <>
lcid		LCID ?
szDescription	OLECHAR 128 dup(?)
CATEGORYINFO	ENDS
LPCATEGORYINFO	typedef ptr CATEGORYINFO

DEFINE_IIDX(IEnumCATEGORYINFO, "0002E011-0000-0000-C000-000000000046")

.comdef IEnumCATEGORYINFO : public IUnknown

    Next		proc
    Skip		proc
    Reset		proc
    Clone		proc

    .ends
endif
endif

ifndef _LPCATREGISTER_DEFINED
define _LPCATREGISTER_DEFINED

ifndef __ICatRegister_INTERFACE_DEFINED__
define __ICatRegister_INTERFACE_DEFINED__

DEFINE_IIDX(ICatRegister, "0002E012-0000-0000-C000-000000000046")

.comdef ICatRegister : public IUnknown

    RegisterCategories	proc
    UnRegisterCategories proc
    RegisterClassImplCategories proc
    UnRegisterClassImplCategories proc
    RegisterClassReqCategories proc
    UnRegisterClassReqCategories proc

    .ends

LPCATREGISTER typedef ptr ICatRegister

endif
endif

ifndef _LPCATINFORMATION_DEFINED
define _LPCATINFORMATION_DEFINED

ifndef __ICatInformation_INTERFACE_DEFINED__
define __ICatInformation_INTERFACE_DEFINED__

DEFINE_IIDX(ICatInformation, "0002E013-0000-0000-C000-000000000046")

.comdef ICatInformation : public IUnknown

    EnumCategories	proc
    GetCategoryDesc	proc
    EnumClassesOfCategories proc
    IsClassOfCategories proc
    EnumImplCategoriesOfClass proc
    EnumReqCategoriesOfClass proc

    .ends

LPCATINFORMATION typedef ptr ICatInformation

endif
endif

endif
.pragma list(pop)
