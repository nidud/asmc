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
__comcat_h__ equ <>
include unknwn.inc
.xlist
ifdef __PE__
option	dllimport:<uuid.lib>
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

;;  Interface Definitions
ifndef _LPENUMGUID_DEFINED
_LPENUMGUID_DEFINED equ <>

externdef __MIDL_itf_comcat_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_comcat_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumGUID_INTERFACE_DEFINED__
__IEnumGUID_INTERFACE_DEFINED__ equ <>

LPENUMGUID typedef ptr IEnumGUID

externdef IID_IEnumGUID:IID

IEnumGUIDVtbl	STRUC
QueryInterface	PVOID ?
AddRef		PVOID ?
Release		PVOID ?
Next		PVOID ?
Skip		PVOID ?
Reset		PVOID ?
Clone		PVOID ?
IEnumGUIDVtbl	ENDS

LPIEnumGUIDVtbl typedef ptr IEnumGUIDVtbl
IEnumGUID	STRUC
lpVtbl		LPIEnumGUIDVtbl ?
IEnumGUID	ENDS


;HRESULT STDMETHODCALLTYPE
IEnumGUID_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumGUID,
		  celt: ULONG,
		 rgelt: ptr GUID,
	  pceltFetched: ptr ULONG

;void __RPC_STUB
IEnumGUID_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif ;; __IEnumGUID_INTERFACE_DEFINED__
endif ;; _LPENUMGUID_DEFINED

ifndef _LPENUMCATEGORYINFO_DEFINED
_LPENUMCATEGORYINFO_DEFINED equ <>


externdef __MIDL_itf_comcat_0000_0001_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_comcat_0000_0001_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumCATEGORYINFO_INTERFACE_DEFINED__
__IEnumCATEGORYINFO_INTERFACE_DEFINED__ equ <>

LPENUMCATEGORYINFO typedef ptr IEnumCATEGORYINFO

CATEGORYINFO	STRUC
catid		CATID <>
lcid		LCID ?
szDescription	OLECHAR 128 dup(?)
CATEGORYINFO	ENDS
LPCATEGORYINFO	typedef ptr CATEGORYINFO


externdef IID_IEnumCATEGORYINFO:IID

IEnumCATEGORYINFOVtbl	STRUC
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
Next			PVOID ?
Skip			PVOID ?
Reset			PVOID ?
Clone			PVOID ?
IEnumCATEGORYINFOVtbl	ENDS
LPIEnumCATEGORYINFOVtbl typedef ptr IEnumCATEGORYINFOVtbl

IEnumCATEGORYINFO	STRUC
lpVtbl			LPIEnumCATEGORYINFOVtbl ?
IEnumCATEGORYINFO	ENDS

endif ;; __IEnumCATEGORYINFO_INTERFACE_DEFINED__
endif

ifndef _LPCATREGISTER_DEFINED
_LPCATREGISTER_DEFINED equ <>

externdef __MIDL_itf_comcat_0000_0002_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_comcat_0000_0002_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICatRegister_INTERFACE_DEFINED__
__ICatRegister_INTERFACE_DEFINED__ equ <>

LPCATREGISTER typedef ptr ICatRegister

externdef IID_ICatRegister:IID

ICatRegisterVtbl		STRUC
QueryInterface			PVOID ?
AddRef				PVOID ?
Release				PVOID ?
RegisterCategories		PVOID ?
UnRegisterCategories		PVOID ?
RegisterClassImplCategories	PVOID ?
UnRegisterClassImplCategories	PVOID ?
RegisterClassReqCategories	PVOID ?
UnRegisterClassReqCategories	PVOID ?
ICatRegisterVtbl		ENDS
LPICatRegisterVtbl		typedef ptr ICatRegisterVtbl

ICatRegister	STRUC
lpVtbl		LPICatRegisterVtbl ?
ICatRegister	ENDS


endif ;; __ICatRegister_INTERFACE_DEFINED__
endif

ifndef _LPCATINFORMATION_DEFINED
_LPCATINFORMATION_DEFINED equ <>

externdef __MIDL_itf_comcat_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_comcat_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICatInformation_INTERFACE_DEFINED__
__ICatInformation_INTERFACE_DEFINED__ equ <>

LPCATINFORMATION typedef ptr ICatInformation

externdef IID_ICatInformation:IID

ICatInformationVtbl		STRUC
QueryInterface			PVOID ?
AddRef				PVOID ?
Release				PVOID ?
EnumCategories			PVOID ?
GetCategoryDesc			PVOID ?
EnumClassesOfCategories		PVOID ?
IsClassOfCategories		PVOID ?
EnumImplCategoriesOfClass	PVOID ?
EnumReqCategoriesOfClass	PVOID ?
ICatInformationVtbl		ENDS
LPICatInformationVtbl		typedef ptr ICatInformationVtbl

ICatInformation STRUC
lpVtbl		LPICatInformationVtbl ?
ICatInformation ENDS


;HRESULT STDMETHODCALLTYPE
ICatInformation_RemoteEnumClassesOfCategories_Proxy proto WINAPI \
		 _This: ptr ICatInformation,
	  cImplemented: ULONG,
	   rgcatidImpl: ptr CATID,
	     cRequired: ULONG,
	    rgcatidReq: ptr CATID,
	   ppenumClsid: ptr IEnumGUID

ICatInformation_RemoteEnumClassesOfCategories_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

ICatInformation_RemoteIsClassOfCategories_Proxy proto WINAPI \
		 _This: ptr ICatInformation,
		rclsid: REFCLSID,
	  cImplemented: ULONG,
	   rgcatidImpl: ptr CATID,
	     cRequired: ULONG,
	    rgcatidReq: ptr CATID

ICatInformation_RemoteIsClassOfCategories_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif ;; __ICatInformation_INTERFACE_DEFINED__
endif


externdef __MIDL_itf_comcat_0000_0004_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_comcat_0000_0004_v0_0_s_ifspec:RPC_IF_HANDLE

IEnumGUID_Next_Proxy proto WINAPI \
		 _This: ptr IEnumGUID,
		  celt: ULONG,
		 rgelt: ptr GUID,
	  pceltFetched: ptr ULONG

IEnumGUID_Next_Stub proto WINAPI \
		 _This: ptr IEnumGUID,
		  celt: ULONG,
		 rgelt: ptr GUID,
	  pceltFetched: ptr ULONG

ICatInformation_EnumClassesOfCategories_Proxy proto WINAPI \
		 _This: ptr ICatInformation,
	  cImplemented: ULONG,
	   rgcatidImpl: ptr CATID,
	     cRequired: ULONG,
	    rgcatidReq: ptr CATID,
	   ppenumClsid: ptr IEnumGUID

ICatInformation_EnumClassesOfCategories_Stub proto WINAPI \
		 _This: ptr ICatInformation,
	  cImplemented: ULONG,
	   rgcatidImpl: ptr CATID,
	     cRequired: ULONG,
	    rgcatidReq: ptr CATID,
	   ppenumClsid: ptr IEnumGUID

ICatInformation_IsClassOfCategories_Proxy proto WINAPI \
		 _This: ptr ICatInformation,
		rclsid: REFCLSID,
	  cImplemented: ULONG,
	   rgcatidImpl: ptr CATID,
	     cRequired: ULONG,
	    rgcatidReq: ptr CATID

ICatInformation_IsClassOfCategories_Stub proto WINAPI \
		 _This: ptr ICatInformation,
		rclsid: REFCLSID,
	  cImplemented: ULONG,
	   rgcatidImpl: ptr CATID,
	     cRequired: ULONG,
	    rgcatidReq: ptr CATID

.list
endif
