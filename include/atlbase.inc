ifndef __ATLBASE_H__
define __ATLBASE_H__

ifdef _UNICODE
ifndef UNICODE
define UNICODE
endif
endif

ifdef UNICODE
ifndef _UNICODE
define _UNICODE
endif
endif

ifdef _DEBUG
ifndef DEBUG
define DEBUG
endif
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
define _ATL_PACKING 8
endif

.pragma pack(push, _ATL_PACKING)

include atlconv.inc

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

_ATL_SIMPLEMAPENTRY	equ 1

_ATL_INTMAP_ENTRY	STRUC
piid			LPIID ?
d			ULONG_PTR ?
pFunc			_ATL_CREATORARGFUNC ?
_ATL_INTMAP_ENTRY	ENDS


AtlInternalQueryInterface proto WINAPI :ptr, :_ATL_INTMAP_ENTRY, :REFIID, :ptr ptr
AtlComPtrAssign proto WINAPI :ptr ptr IUnknown, :ptr IUnknown
AtlComQIPtrAssign proto WINAPI :ptr ptr IUnknown, :ptr IUnknown, :REFIID
AtlFreeMarshalStream proto WINAPI :ptr IStream
AtlMarshalPtrInProc proto WINAPI :ptr IUnknown, :ptr IID, :ptr ptr IStream
AtlUnmarshalPtr proto WINAPI :ptr IStream, :ptr IID, :ptr ptr IUnknown
AtlWaitWithMessageLoop proto WINAPI :HANDLE
AtlAdvise proto WINAPI :ptr IUnknown, :ptr IUnknown, :ptr IID, :LPDWORD
AtlUnadvise proto WINAPI :ptr IUnknown, :ptr IID, :DWORD
AtlSetErrorInfo proto WINAPI :ptr CLSID, :LPCOLESTR, :DWORD, :LPCOLESTR, :ptr IID, :HRESULT, :HINSTANCE
AtlModuleInit proto WINAPI :_ATL_MODULE, :_ATL_OBJMAP_ENTRY, :HINSTANCE
AtlModuleRegisterClassObjects proto WINAPI :_ATL_MODULE, :DWORD, :DWORD
AtlModuleRevokeClassObjects proto WINAPI :_ATL_MODULE
AtlModuleGetClassObject proto WINAPI :_ATL_MODULE, :REFCLSID, :REFIID, :ptr LPVOID
AtlModuleTerm proto WINAPI :_ATL_MODULE
AtlModuleRegisterServer proto WINAPI :_ATL_MODULE, :BOOL, :ptr CLSID
AtlModuleUnregisterServer proto WINAPI :_ATL_MODULE, :ptr CLSID
AtlModuleUpdateRegistryFromResourceD proto WINAPI :_ATL_MODULE, :LPCOLESTR, :BOOL, :ptr _ATL_REGMAP_ENTRY, :ptr IRegistrar
AtlModuleRegisterTypeLib proto WINAPI :_ATL_MODULE, :LPCOLESTR

ifdef _DEBUG
AtlTrace proto _Cdecl :LPCTSTR, :vararg
ifndef ATLTRACE
ATLTRACE equ <AtlTrace>
endif
else
ATLTRACENOTIMPL macro funcname
exitm<E_NOTIMPL>
endm
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
define _ATL_FREE_THREADED 1
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
endif
