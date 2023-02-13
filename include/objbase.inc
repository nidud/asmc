ifndef __OBJBASE_INC
define __OBJBASE_INC

include winapifamily.inc

include rpc.inc
include rpcndr.inc

ifndef _OBJBASE_H_
define _OBJBASE_H_

.pragma pack(push, size_t)

include combaseapi.inc
include coml2api.inc

.enum COINIT {
  COINIT_APARTMENTTHREADED  = 0x2,
if  (_WIN32_WINNT ge 0x0400 ) or defined(_WIN32_DCOM)
  COINIT_MULTITHREADED      = COINITBASE_MULTITHREADED,
  COINIT_DISABLE_OLE1DDE    = 0x4,
  COINIT_SPEED_OVER_MEMORY  = 0x8,
endif
}

define MARSHALINTERFACE_MIN 500

define ASYNC_MODE_COMPATIBILITY    0x00000001
define ASYNC_MODE_DEFAULT          0x00000000

define STGTY_REPEAT                0x00000100
define STG_TOEND                   0xFFFFFFFF

define STG_LAYOUT_SEQUENTIAL       0x00000000
define STG_LAYOUT_INTERLEAVED      0x00000001

;include wtypes.inc
include objidl.inc

ifdef _OLE32_
ifdef _OLE32PRIV_
wIsEqualGUID proto WINAPI :REFGUID, :REFGUID
IsEqualGUID macro rguid1, rguid2
  exitm<wIsEqualGUID(rguid1, rguid2)>
  endm
else
define __INLINE_ISEQUAL_GUID
endif
endif

.pragma comment(lib, ole32)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CoBuildVersion proto WINAPI
CoInitialize proto WINAPI :LPVOID

define COM_SUPPORT_MALLOC_SPIES
CoRegisterMallocSpy proto WINAPI :LPMALLOCSPY
CoRevokeMallocSpy proto WINAPI
CoCreateStandardMalloc proto WINAPI :DWORD, :ptr

if (_WIN32_WINNT ge 0x0501)

CoRegisterInitializeSpy proto WINAPI :ptr, :ptr
CoRevokeInitializeSpy proto WINAPI :ULARGE_INTEGER

.enum COMSD {
    SD_LAUNCHPERMISSIONS = 0,
    SD_ACCESSPERMISSIONS = 1,
    SD_LAUNCHRESTRICTIONS = 2,
    SD_ACCESSRESTRICTIONS = 3
    }
CoGetSystemSecurityPermissions proto WINAPI :COMSD, :ptr

endif

CoLoadLibrary proto WINAPI :LPOLESTR, :BOOL
CoFreeLibrary proto WINAPI :HINSTANCE
CoFreeAllLibraries proto WINAPI

if (_WIN32_WINNT ge 0x0400 ) or defined(_WIN32_DCOM)

CoGetInstanceFromFile proto WINAPI :ptr, :ptr, :ptr, :DWORD, :DWORD, :ptr, :DWORD, :ptr
CoGetInstanceFromIStorage proto WINAPI :ptr, :ptr, :ptr, :DWORD, :ptr, :DWORD, :ptr

endif

if (_WIN32_WINNT ge 0x0500 ) or defined(_WIN32_DCOM)

CoAllowSetForegroundWindow proto WINAPI :ptr, :LPVOID
DcomChannelSetHResult proto WINAPI :LPVOID, :ptr, :HRESULT

endif

CoIsOle1Class proto WINAPI :REFCLSID
CLSIDFromProgIDEx proto WINAPI :LPCOLESTR, :LPCLSID

CoFileTimeToDosDateTime proto WINAPI :ptr, :LPWORD, :LPWORD
CoDosDateTimeToFileTime proto WINAPI :WORD, :WORD, :ptr
CoFileTimeNow proto WINAPI :ptr

CoRegisterMessageFilter proto WINAPI :LPMESSAGEFILTER, :ptr

if (_WIN32_WINNT ge 0x0400 ) or defined(_WIN32_DCOM)
CoRegisterChannelHook proto WINAPI :REFGUID, :ptr
endif

CoTreatAsClass proto WINAPI :REFCLSID, :REFCLSID
CreateDataAdviseHolder proto WINAPI :ptr
CreateDataCache proto WINAPI :LPUNKNOWN, :REFCLSID, :REFIID, :ptr
StgOpenAsyncDocfileOnIFillLockBytes proto WINAPI :ptr, :DWORD, :DWORD, :ptr ptr
StgGetIFillLockBytesOnILockBytes proto WINAPI :ptr, :ptr ptr
StgGetIFillLockBytesOnFile proto WINAPI :ptr, :ptr ptr
StgOpenLayoutDocfile proto WINAPI :ptr, :DWORD, :DWORD, :ptr ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
CoInstall proto WINAPI :ptr, :DWORD, :ptr, :ptr, :LPWSTR
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PC_APP)

BindMoniker proto WINAPI :LPMONIKER, :DWORD, :REFIID, :ptr

CoGetObject proto WINAPI :LPCWSTR, :ptr, :REFIID, :ptr ptr
MkParseDisplayName proto WINAPI :LPBC, :LPCOLESTR, :ptr, :ptr
MonikerRelativePathTo proto WINAPI :LPMONIKER, :LPMONIKER, :ptr, :BOOL
MonikerCommonPrefixWith proto WINAPI :LPMONIKER, :LPMONIKER, :ptr
CreateBindCtx proto WINAPI :DWORD, :ptr
CreateGenericComposite proto WINAPI :LPMONIKER, :LPMONIKER, :ptr
GetClassFile proto WINAPI :LPCOLESTR, :ptr
CreateClassMoniker proto WINAPI :REFCLSID, :ptr
CreateFileMoniker proto WINAPI :LPCOLESTR, :ptr
CreateItemMoniker proto WINAPI :LPCOLESTR, :LPCOLESTR, :ptr
CreateAntiMoniker proto WINAPI :ptr
CreatePointerMoniker proto WINAPI :LPUNKNOWN, :ptr
CreateObjrefMoniker proto WINAPI :LPUNKNOWN, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
GetRunningObjectTable proto WINAPI :DWORD, :ptr
endif

include urlmon.inc
include propidl.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
CreateStdProgressIndicator proto WINAPI :HWND, :LPCOLESTR, :ptr, :ptr ptr
endif

.pragma pack(pop)

endif
endif
