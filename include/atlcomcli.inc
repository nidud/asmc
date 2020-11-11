ifndef __ATLCOMCLI_H__
__ATLCOMCLI_H__ equ <>

include atlcore.inc
include ole2.inc
ifndef _ATL_USE_WINAPI_FAMILY_PHONE_APP
include olectl.inc
endif

.pragma pack(push,_ATL_PACKING)
if 0
AtlHresultFromLastError proto {
    GetLastError()
    HRESULT_FROM_WIN32(eax)
}
endif
AtlHresultFromWin32 proto :DWORD {
    HRESULT_FROM_WIN32( ecx )
}


AtlComPtrAssign proto :ptr ptr IUnknown, :ptr IUnknown
AtlComQIPtrAssign proto :ptr ptr IUnknown, :ptr IUnknown, :REFIID


ClassesAllowedInStream	union
rgclsidAllowed		LPCLSID ?
pfnClsidAllowed		proc :ptr CLSID, :REFIID, :ptr ptr
ClassesAllowedInStream	ends

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

AtlInternalOleLoadFromStream proto :ptr IStream, :REFIID, :ptr ptr, :ClassesAllowedInStream, :DWORD

endif

AtlComPtrAssign proto :ptr ptr IUnknown, :ptr IUnknown {
	int 3
}

AtlComQIPtrAssign proto :ptr ptr IUnknown, :ptr IUnknown, :REFIID {
	int 3
}

.class _NoAddRefReleaseOnCComPtr ;: public T
	AddRef		proc
	Release		proc
	.ENDS

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

AtlSetChildSite proto :ptr IUnknown, :ptr IUnknown {
	int 3
}

endif

.class CComPtrBase

	.ENDS

.class CComPtr : public CComPtrBase

	.ENDS

.class CComPtr : public CComPtrBase

	.ENDS

.class CComQIPtr : public CComPtr

	.ENDS

.class CComQIPtr :  public CComPtr

	.ENDS

CComDispatchDriver typedef CComQIPtr

ifndef _ATL_STREAM_MAX_SIZE
_ATL_STREAM_MAX_SIZE  equ 0x100000
endif

.class CComBSTR

	.ENDS


.class CAdapt

	.ENDS


ATL_VARIANT_TRUE  equ ( -1 )
ATL_VARIANT_FALSE equ ( 0 )

.class CVarTypeInfo

	.ENDS


ifdef _ATL_NO_VARIANT_THROW
ATLVARIANT_THROW equ <throw>
else
ATLVARIANT_THROW equ <>
endif

.class CComVariant : public VARIANT

	.ENDS


ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP


endif


.pragma pack(pop)

endif
