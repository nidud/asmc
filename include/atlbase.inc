ifndef __ATLBASE_H__
__ATLBASE_H__ equ <>
.pragma list(push, 0)

ifdef _UNICODE
ifndef UNICODE
UNICODE equ 1
endif
endif

ifdef UNICODE
ifndef _UNICODE
_UNICODE equ 1
endif
endif

ifdef _DEBUG
ifndef DEBUG
DEBUG equ 1
endif
endif

ifdef _ATL_DISABLE_NO_VTABLE
ATL_NO_VTABLE equ <>
else
ATL_NO_VTABLE equ <__declspec(novtable)>
endif

ifndef _ATL_NO_PRAGMA_WARNINGS
.pragma warning(disable: 6004)
.pragma warning(disable: 7007)
endif

include windows.inc
include winnls.inc
include ole2.inc

include stddef.inc
include tchar.inc
include malloc.inc
ifndef _ATL_NO_DEBUG_CRT
include crtdbg.inc
endif

ifndef ATLASSERT
ATLASSERT equ <.ASSERT>
endif

include olectl.inc
include winreg.inc
include atliface.inc

ifndef _ATL_PACKING
_ATL_PACKING equ 8
endif
.pragma pack(push, _ATL_PACKING)

include atlconv.inc

ifdef _ATL_DLL
ATLAPI equ <__declspec(dllimport) WINAPI>
ATLAPI_ macro x
    exitm<x __declspec(dllimport) WINAPI>
    endm
ATLINLINE equ <>
elseifdef _ATL_DLL_IMPL
ATLAPI equ <__declspec(dllexport) WINAPI>
ATLAPI_ macro x
    exitm<x __declspec(dllexport) WINAPI>
    endm
ATLINLINE equ <>
else
ATLAPI equ <WINAPI>
ATLAPI_ macro x
    exitm<x WINAPI>
    endm
ATLINLINE equ <>
endif

CALLBACK(_ATL_CREATORFUNC, :ptr, :REFIID, :ptr LPVOID)
CALLBACK(_ATL_CREATORARGFUNC, :ptr, :REFIID, :ptr LPVOID, :ULONG_PTR)
CALLBACK(_ATL_MODULEFUNC, :ULONG_PTR)
CALLBACK(_ATL_DESCRIPTIONFUNC)

.template _ATL_OBJMAP_ENTRY

    pclsid LPCLSID ?
    pfnUpdateRegistry proc local WINAPI :BOOL
    pfnGetClassObject _ATL_CREATORFUNC ?
    pfnCreateInstance _ATL_CREATORFUNC ?
    pCF LPUNKNOWN ?
    dwRegister DWORD ?
    pfnGetObjectDescription _ATL_DESCRIPTIONFUNC ?

    .inline RevokeClassObject {

	CoRevokeClassObject([this]._ATL_OBJMAP_ENTRY.dwRegister)
	}
    .inline RegisterClassObject :DWORD, :DWORD {

       .new p:ptr IUnknown
	mov p,NULL
	.if ([this]._ATL_OBJMAP_ENTRY.pfnGetClassObject == NULL)
	    mov eax,S_OK
	.else

	   .new t:ptr _ATL_OBJMAP_ENTRY
	   .new hRes:HRESULT
	    mov t,this
	    mov hRes,[this]._ATL_OBJMAP_ENTRY.pfnGetClassObject(
			[this]._ATL_OBJMAP_ENTRY.pfnCreateInstance,
			&IID_IUnknown,
			&p)

	    .if (SUCCEEDED(hRes))

		mov this,t
		mov hRes,CoRegisterClassObject(
				[this]._ATL_OBJMAP_ENTRY.pclsid,
				p,
				[this]._ATL_OBJMAP_ENTRY.dwClsContext,
				[this]._ATL_OBJMAP_ENTRY.dwFlags,
				&[this]._ATL_OBJMAP_ENTRY.dwRegister)
		.if p != NULL
		    p.Release()
		.endif
	    .endif
	    mov eax,hRes
	}
    .ENDS

_ATL_REGMAP_ENTRY	STRUC
szKey			LPCOLESTR ?
szData			LPCOLESTR ?
_ATL_REGMAP_ENTRY	ENDS

_ATL_MODULE		STRUC
cbSize			UINT ?
m_hInst			HINSTANCE ?
m_hInstResource		HINSTANCE ?
m_hInstTypeLib		HINSTANCE ?
m_pObjMap		_ATL_OBJMAP_ENTRY <>
m_nLockCnt		LONG ?
m_hHeap			HANDLE ?
m_csTypeInfoHolder	CRITICAL_SECTION <>
m_csWindowCreate	CRITICAL_SECTION <>
m_csObjMap		CRITICAL_SECTION <>
_ATL_MODULE		ENDS

_ATL_SIMPLEMAPENTRY	equ (1)

_ATL_INTMAP_ENTRY	STRUC
piid			LPIID ?
d			ULONG_PTR ?
pFunc			_ATL_CREATORARGFUNC ?
_ATL_INTMAP_ENTRY	ENDS


AtlInternalQueryInterface proto ATLAPI \
		 pThis: ptr,
	      pEntries: _ATL_INTMAP_ENTRY,
		   iid: REFIID,
	     ppvObject: ptr ptr


AtlComPtrAssign proto ATLAPI \
		    pp: ptr ptr IUnknown,
		    lp: ptr IUnknown

AtlComQIPtrAssign proto ATLAPI \
		    pp: ptr ptr IUnknown,
		    lp: ptr IUnknown,
		  riid: REFIID

AtlFreeMarshalStream proto ATLAPI \
	       pStream: ptr IStream

AtlMarshalPtrInProc proto ATLAPI \
		  pUnk: ptr IUnknown,
		   iid: ptr IID,
	      ppStream: ptr ptr IStream

AtlUnmarshalPtr proto ATLAPI \
	      pStream: ptr IStream,
		  iid: ptr IID,
		ppUnk: ptr ptr IUnknown

AtlWaitWithMessageLoop proto ATLAPI \
	       hEvent: HANDLE

AtlAdvise proto ATLAPI \
	       pUnkCP: ptr IUnknown,
		 pUnk: ptr IUnknown,
		  iid: ptr IID,
		  pdw: LPDWORD

AtlUnadvise proto ATLAPI \
	       pUnkCP: ptr IUnknown,
		  iid: ptr IID,
		    d: DWORD

AtlSetErrorInfo proto ATLAPI \
		clsid: ptr CLSID,
	     lpszDesc: LPCOLESTR,
	     dwHelpID: DWORD,
	 lpszHelpFile: LPCOLESTR,
		  iid: ptr IID,
		 hRes: HRESULT,
		hInst: HINSTANCE

AtlModuleInit proto ATLAPI \
		   pM: _ATL_MODULE,
		    p: _ATL_OBJMAP_ENTRY,
		    h: HINSTANCE

AtlModuleRegisterClassObjects proto ATLAPI \
		   pM: _ATL_MODULE,
	 dwClsContext: DWORD,
	      dwFlags: DWORD

AtlModuleRevokeClassObjects proto ATLAPI \
		   pM: _ATL_MODULE

AtlModuleGetClassObject proto ATLAPI \
		   pM: _ATL_MODULE,
	       rclsid: REFCLSID,
		 riid: REFIID,
		  ppv: ptr LPVOID

AtlModuleTerm proto ATLAPI \
		   pM: _ATL_MODULE

AtlModuleRegisterServer proto ATLAPI \
		   pM: _ATL_MODULE,
	  bRegTypeLib: BOOL,
	       pCLSID: ptr CLSID

AtlModuleUnregisterServer proto ATLAPI \
		   pM: _ATL_MODULE,
	       pCLSID: ptr CLSID

AtlModuleUpdateRegistryFromResourceD proto ATLAPI \
		   pM: _ATL_MODULE,
	      lpszRes: LPCOLESTR,
	    bRegister: BOOL,
	  pMapEntries: ptr _ATL_REGMAP_ENTRY,
		 pReg: ptr IRegistrar

AtlModuleRegisterTypeLib proto ATLAPI \
		   pM: _ATL_MODULE,
	    lpszIndex: LPCOLESTR


ifdef _DEBUG
AtlTrace proto _Cdecl :LPCTSTR, :vararg
ifndef ATLTRACE
ATLTRACE equ <AtlTrace>
endif
else
ifndef ATLTRACE
endif
ATLTRACENOTIMPL macro funcname
exitm<E_NOTIMPL>
endm
endif

ifndef offsetofclass
endif

_ATL	 equ 1
undef _ATL_VER
_ATL_VER equ 0x0203

ifndef _ATL_NO_FORCE_LIBS
	.pragma comment(lib, kernel32)
	.pragma comment(lib, user32)
	.pragma comment(lib, ole32)
	.pragma comment(lib, oleaut32)
	;.pragma comment(lib, olepro32)
	.pragma comment(lib, uuid)
	.pragma comment(lib, advapi32)
endif


ATL_VARIANT_TRUE  equ ( -1 )
ATL_VARIANT_FALSE equ ( 0 )

ifndef _ATL_SINGLE_THREADED
ifndef _ATL_APARTMENT_THREADED
ifndef _ATL_FREE_THREADED
_ATL_FREE_THREADED equ 1
endif
endif
endif

THREADFLAGS_APARTMENT equ 0x1
THREADFLAGS_BOTH equ 0x2
AUTPRXFLAG equ 0x4

_AtlCreateWndData	STRUC
m_pThis			PVOID ?
m_dwThreadID		DWORD ?
m_pNext			PVOID ?
_AtlCreateWndData	ENDS


ifdef _ATL_STATIC_REGISTRY
UpdateRegistryFromResource equ <UpdateRegistryFromResourceS>
else
UpdateRegistryFromResource equ <UpdateRegistryFromResourceD>
endif

.pragma pack(pop)
.pragma list(pop)
endif
