ifndef _RPC500_
include rpc500.inc
endif
ifndef __dimm_h__
define __dimm_h__
ifndef __unknwn_h__
include unknwn.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __ActiveIMM_LIBRARY_DEFINED__
define __ActiveIMM_LIBRARY_DEFINED__

ifndef _IMM_
include imm.inc
endif

if (WINVER lt 0x040A)
IMEMENUITEMINFOA	struct
cbSize			UINT ?
fType			UINT ?
fState			UINT ?
wID			UINT ?
hbmpChecked		HBITMAP ?
hbmpUnchecked		HBITMAP ?
dwItemData		DWORD ?
szString		CHAR 80 dup(?)
hbmpItem		HBITMAP ?
IMEMENUITEMINFOA	ends
IMEMENUITEMINFOW	struct
cbSize			UINT ?
fType			UINT ?
fState			UINT ?
wID			UINT ?
hbmpChecked		HBITMAP ?
hbmpUnchecked		HBITMAP ?
dwItemData		DWORD ?
szString		WCHAR 80 dup(?)
hbmpItem		HBITMAP ?
IMEMENUITEMINFOW	ends
endif

ifndef _DDKIMM_H_
INPUTCONTEXT		struct
hWnd			HWND ?
fOpen			BOOL ?
ptStatusWndPos		POINT <>
ptSoftKbdPos		POINT <>
fdwConversion		DWORD ?
fdwSentence		DWORD ?
union lfFont
 A			LOGFONTA <>
 W			LOGFONTW <>
ends
cfCompForm		COMPOSITIONFORM <>
cfCandForm		CANDIDATEFORM 4 dup(<>)
hCompStr		HIMCC ?
hCandInfo		HIMCC ?
hGuideLine		HIMCC ?
hPrivate		HIMCC ?
dwNumMsgBuf		DWORD ?
hMsgBuf			HIMCC ?
fdwInit			DWORD ?
dwReserve		DWORD 3 dup(?)
INPUTCONTEXT		ends

IMEINFO			struct
dwPrivateDataSize	DWORD ?
fdwProperty		DWORD ?
fdwConversionCaps	DWORD ?
fdwSentenceCaps		DWORD ?
fdwUICaps		DWORD ?
fdwSCSCaps		DWORD ?
fdwSelectCaps		DWORD ?
IMEINFO			ends
endif

externdef LIBID_ActiveIMM:IID

ifndef __IEnumRegisterWordA_INTERFACE_DEFINED__
define __IEnumRegisterWordA_INTERFACE_DEFINED__
DEFINE_IIDX(IEnumRegisterWordA, "08C03412-F96B-11d0-A475-00AA006BCC59")

.comdef IEnumRegisterWordA : public IUnknown
    Clone		proc :ptr ptr
    Next		proc :ULONG, :ptr, :ptr
    Reset		proc
    Skip		proc :ULONG
   .ends

endif

ifndef __IEnumRegisterWordW_INTERFACE_DEFINED__
define __IEnumRegisterWordW_INTERFACE_DEFINED__
DEFINE_IIDX(IEnumRegisterWordW, "4955DD31-B159-11d0-8FCF-00AA006BCC59")

.comdef IEnumRegisterWordW : public IUnknown
    Clone		proc :ptr ptr
    Next		proc :ULONG, :ptr, :ptr
    Reset		proc
    Skip		proc :ULONG
   .ends

endif

ifndef __IEnumInputContext_INTERFACE_DEFINED__
define __IEnumInputContext_INTERFACE_DEFINED__
DEFINE_IIDX(IEnumInputContext, "09b5eab0-f997-11d1-93d4-0060b067b86e")

.comdef IEnumInputContext : public IUnknown
    Clone		proc :ptr ptr
    Next		proc :ULONG, :ptr, :ptr
    Reset		proc
    Skip		proc :ULONG
   .ends

endif

ifndef __IActiveIMMRegistrar_INTERFACE_DEFINED__
define __IActiveIMMRegistrar_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIMMRegistrar, "b3458082-bd00-11d1-939b-0060b067b86e")

.comdef IActiveIMMRegistrar : public IUnknown
    RegisterIME		proc :REFCLSID, :LANGID, :LPCWSTR, :LPCWSTR
    UnregisterIME	proc :REFCLSID
   .ends

endif

ifndef __IActiveIMMMessagePumpOwner_INTERFACE_DEFINED__
define __IActiveIMMMessagePumpOwner_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIMMMessagePumpOwner, "b5cf2cfa-8aeb-11d1-9364-0060b067b86e")

.comdef IActiveIMMMessagePumpOwner : public IUnknown
    Start		proc
    _End		proc
    OnTranslateMessage	proc :ptr
    _Pause		proc :ptr
    Resume		proc :DWORD
   .ends

endif

ifndef __IActiveIMMApp_INTERFACE_DEFINED__
define __IActiveIMMApp_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIMMApp, "08c0e040-62d1-11d1-9326-0060b067b86e")

.comdef IActiveIMMApp : public IUnknown
    AssociateContext	proc :HWND, :HIMC, :ptr
    ConfigureIMEA	proc :HKL, :HWND, :DWORD, :ptr
    ConfigureIMEW	proc :HKL, :HWND, :DWORD, :ptr
    CreateContext	proc :ptr
    DestroyContext	proc :HIMC
    EnumRegisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR, :LPVOID, :ptr ptr
    EnumRegisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR, :LPVOID, :ptr ptr
    EscapeA		proc :HKL, :HIMC, :UINT, :LPVOID, :ptr
    EscapeW		proc :HKL, :HIMC, :UINT, :LPVOID, :ptr
    GetCandidateListA	proc :HIMC, :DWORD, :UINT, :ptr, :ptr
    GetCandidateListW	proc :HIMC, :DWORD, :UINT, :ptr, :ptr
    GetCandidateListCountA proc :HIMC, :ptr, :ptr
    GetCandidateListCountW proc :HIMC, :ptr, :ptr
    GetCandidateWindow	proc :HIMC, :DWORD, :ptr
    GetCompositionFontA proc :HIMC, :ptr
    GetCompositionFontW proc :HIMC, :ptr
    GetCompositionStringA proc :HIMC, :DWORD, :DWORD, :ptr, :LPVOID
    GetCompositionStringW proc :HIMC, :DWORD, :DWORD, :ptr, :LPVOID
    GetCompositionWindow proc :HIMC, :ptr
    GetContext		proc :HWND, :ptr
    GetConversionListA	proc :HKL, :HIMC, :LPSTR, :UINT, :UINT, :ptr, :ptr
    GetConversionListW	proc :HKL, :HIMC, :LPWSTR, :UINT, :UINT, :ptr, :ptr
    GetConversionStatus proc :HIMC, :ptr, :ptr
    GetDefaultIMEWnd	proc :HWND, :ptr
    GetDescriptionA	proc :HKL, :UINT, :LPSTR, :ptr
    GetDescriptionW	proc :HKL, :UINT, :LPWSTR, :ptr
    GetGuideLineA	proc :HIMC, :DWORD, :DWORD, :LPSTR, :ptr
    GetGuideLineW	proc :HIMC, :DWORD, :DWORD, :LPWSTR, :ptr
    GetIMEFileNameA	proc :HKL, :UINT, :LPSTR, :ptr
    GetIMEFileNameW	proc :HKL, :UINT, :LPWSTR, :ptr
    GetOpenStatus	proc :HIMC
    GetProperty		proc :HKL, :DWORD, :ptr
    GetRegisterWordStyleA proc :HKL, :UINT, :ptr, :ptr
    GetRegisterWordStyleW proc :HKL, :UINT, :ptr, :ptr
    GetStatusWindowPos	proc :HIMC, :ptr
    GetVirtualKey	proc :HWND, :ptr
    InstallIMEA		proc :LPSTR, :LPSTR, :ptr
    InstallIMEW		proc :LPWSTR, :LPWSTR, :ptr
    IsIME		proc :HKL
    IsUIMessageA	proc :HWND, :UINT, :WPARAM, :LPARAM
    IsUIMessageW	proc :HWND, :UINT, :WPARAM, :LPARAM
    NotifyIME		proc :HIMC, :DWORD, :DWORD, :DWORD
    RegisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR
    RegisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR
    ReleaseContext	proc :HWND, :HIMC
    SetCandidateWindow	proc :HIMC, :ptr
    SetCompositionFontA proc :HIMC, :ptr
    SetCompositionFontW proc :HIMC, :ptr
    SetCompositionStringA proc :HIMC, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD
    SetCompositionStringW proc :HIMC, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD
    SetCompositionWindow proc :HIMC, :ptr
    SetConversionStatus proc :HIMC, :DWORD, :DWORD
    SetOpenStatus	proc :HIMC, :BOOL
    SetStatusWindowPos	proc :HIMC, :ptr
    SimulateHotKey	proc :HWND, :DWORD
    UnregisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR
    UnregisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR
    Activate		proc :BOOL
    Deactivate		proc
    OnDefWindowProc	proc :HWND, :UINT, :WPARAM, :LPARAM, :ptr
    FilterClientWindows proc :ptr, :UINT
    GetCodePageA	proc :HKL, :ptr
    GetLangId		proc :HKL, :ptr
    AssociateContextEx	proc :HWND, :HIMC, :DWORD
    DisableIME		proc :DWORD
    GetImeMenuItemsA	proc :HIMC, :DWORD, :DWORD, :ptr, :ptr, :DWORD, :ptr
    GetImeMenuItemsW	proc :HIMC, :DWORD, :DWORD, :ptr, :ptr, :DWORD, :ptr
    EnumInputContext	proc :DWORD, :ptr ptr
   .ends

endif

ifndef __IActiveIMMIME_INTERFACE_DEFINED__
define __IActiveIMMIME_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIMMIME, "08C03411-F96B-11d0-A475-00AA006BCC59")

.comdef IActiveIMMIME : public IUnknown
    AssociateContext	proc :HWND, :HIMC, :ptr
    ConfigureIMEA	proc :HKL, :HWND, :DWORD, :ptr
    ConfigureIMEW	proc :HKL, :HWND, :DWORD, :ptr
    CreateContext	proc :ptr
    DestroyContext	proc :HIMC
    EnumRegisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR, :LPVOID, :ptr ptr
    EnumRegisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR, :LPVOID, :ptr ptr
    EscapeA		proc :HKL, :HIMC, :UINT, :LPVOID, :ptr
    EscapeW		proc :HKL, :HIMC, :UINT, :LPVOID, :ptr
    GetCandidateListA	proc :HIMC, :DWORD, :UINT, :ptr, :ptr
    GetCandidateListW	proc :HIMC, :DWORD, :UINT, :ptr, :ptr
    GetCandidateListCountA proc :HIMC, :ptr, :ptr
    GetCandidateListCountW proc :HIMC, :ptr, :ptr
    GetCandidateWindow	proc :HIMC, :DWORD, :ptr
    GetCompositionFontA proc :HIMC, :ptr
    GetCompositionFontW proc :HIMC, :ptr
    GetCompositionStringA proc :HIMC, :DWORD, :DWORD, :ptr, :LPVOID
    GetCompositionStringW proc :HIMC, :DWORD, :DWORD, :ptr, :LPVOID
    GetCompositionWindow proc :HIMC, :ptr
    GetContext		proc :HWND, :ptr
    GetConversionListA	proc :HKL, :HIMC, :LPSTR, :UINT, :UINT, :ptr, :ptr
    GetConversionListW	proc :HKL, :HIMC, :LPWSTR, :UINT, :UINT, :ptr, :ptr
    GetConversionStatus proc :HIMC, :ptr, :ptr
    GetDefaultIMEWnd	proc :HWND, :ptr
    GetDescriptionA	proc :HKL, :UINT, :LPSTR, :ptr
    GetDescriptionW	proc :HKL, :UINT, :LPWSTR, :ptr
    GetGuideLineA	proc :HIMC, :DWORD, :DWORD, :LPSTR, :ptr
    GetGuideLineW	proc :HIMC, :DWORD, :DWORD, :LPWSTR, :ptr
    GetIMEFileNameA	proc :HKL, :UINT, :LPSTR, :ptr
    GetIMEFileNameW	proc :HKL, :UINT, :LPWSTR, :ptr
    GetOpenStatus	proc :HIMC
    GetProperty		proc :HKL, :DWORD, :ptr
    GetRegisterWordStyleA proc :HKL, :UINT, :ptr, :ptr
    GetRegisterWordStyleW proc :HKL, :UINT, :ptr, :ptr
    GetStatusWindowPos	proc :HIMC, :ptr
    GetVirtualKey	proc :HWND, :ptr
    InstallIMEA		proc :LPSTR, :LPSTR, :ptr
    InstallIMEW		proc :LPWSTR, :LPWSTR, :ptr
    IsIME		proc :HKL
    IsUIMessageA	proc :HWND, :UINT, :WPARAM, :LPARAM
    IsUIMessageW	proc :HWND, :UINT, :WPARAM, :LPARAM
    NotifyIME		proc :HIMC, :DWORD, :DWORD, :DWORD
    RegisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR
    RegisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR
    ReleaseContext	proc :HWND, :HIMC
    SetCandidateWindow	proc :HIMC, :ptr
    SetCompositionFontA proc :HIMC, :ptr
    SetCompositionFontW proc :HIMC, :ptr
    SetCompositionStringA proc :HIMC, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD
    SetCompositionStringW proc :HIMC, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD
    SetCompositionWindow proc :HIMC, :ptr
    SetConversionStatus proc :HIMC, :DWORD, :DWORD
    SetOpenStatus	proc :HIMC, :BOOL
    SetStatusWindowPos	proc :HIMC, :ptr
    SimulateHotKey	proc :HWND, :DWORD
    UnregisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR
    UnregisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR
    GenerateMessage	proc :HIMC
    LockIMC		proc :HIMC, :ptr ptr
    UnlockIMC		proc :HIMC
    GetIMCLockCount	proc :HIMC, :ptr
    CreateIMCC		proc :DWORD, :ptr
    DestroyIMCC		proc :HIMCC
    LockIMCC		proc :HIMCC, :ptr ptr
    UnlockIMCC		proc :HIMCC
    ReSizeIMCC		proc :HIMCC, :DWORD, :ptr
    GetIMCCSize		proc :HIMCC, :ptr
    GetIMCCLockCount	proc :HIMCC, :ptr
    GetHotKey		proc :DWORD, :ptr, :ptr, :ptr
    SetHotKey		proc :DWORD, :UINT, :UINT, :HKL
    CreateSoftKeyboard	proc :UINT, :HWND, :int_t, :int_t, :ptr
    DestroySoftKeyboard proc :HWND
    ShowSoftKeyboard	proc :HWND, :int_t
    GetCodePageA	proc :HKL, :ptr
    GetLangId		proc :HKL, :ptr
    KeybdEvent		proc :LANGID, :BYTE, :BYTE, :DWORD, :DWORD
    LockModal		proc
    UnlockModal		proc
    AssociateContextEx	proc :HWND, :HIMC, :DWORD
    DisableIME		proc :DWORD
    GetImeMenuItemsA	proc :HIMC, :DWORD, :DWORD, :ptr, :ptr, :DWORD, :ptr
    GetImeMenuItemsW	proc :HIMC, :DWORD, :DWORD, :ptr, :ptr, :DWORD, :ptr
    EnumInputContext	proc :DWORD, :ptr ptr
    RequestMessageA	proc :HIMC, :WPARAM, :LPARAM, :ptr
    RequestMessageW	proc :HIMC, :WPARAM, :LPARAM, :ptr
    SendIMCA		proc :HWND, :UINT, :WPARAM, :LPARAM, :ptr
    SendIMCW		proc :HWND, :UINT, :WPARAM, :LPARAM, :ptr
    IsSleeping		proc
   .ends

endif

ifndef __IActiveIME_INTERFACE_DEFINED__
define __IActiveIME_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIME, "6FE20962-D077-11d0-8FE7-00AA006BCC59")

.comdef IActiveIME : public IUnknown
    Inquire		proc :DWORD, :ptr, :LPWSTR, :ptr
    ConversionList	proc :HIMC, :LPWSTR, :UINT, :UINT, :ptr, :ptr
    Configure		proc :HKL, :HWND, :DWORD, :ptr
    Destroy		proc :UINT
    Escape		proc :HIMC, :UINT, :ptr, :ptr
    SetActiveContext	proc :HIMC, :BOOL
    ProcessKey		proc :HIMC, :UINT, :DWORD, :ptr
    Notify		proc :HIMC, :DWORD, :DWORD, :DWORD
    Select		proc :HIMC, :BOOL
    SetCompositionString proc :HIMC, :DWORD, :ptr, :DWORD, :ptr, :DWORD
    ToAsciiEx		proc :UINT, :UINT, :ptr, :UINT, :HIMC, :ptr, :ptr
    RegisterWord	proc :LPWSTR, :DWORD, :LPWSTR
    UnregisterWord	proc :LPWSTR, :DWORD, :LPWSTR
    GetRegisterWordStyle proc :UINT, :ptr, :ptr
    EnumRegisterWord	proc :LPWSTR, :DWORD, :LPWSTR, :LPVOID, :ptr ptr
    GetCodePageA	proc :ptr
    GetLangId		proc :ptr
   .ends

endif

ifndef __IActiveIME2_INTERFACE_DEFINED__
define __IActiveIME2_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIME2, "e1c4bf0e-2d53-11d2-93e1-0060b067b86e")

.comdef IActiveIME2 : public IActiveIME
    Sleep		proc
    Unsleep		proc :BOOL
   .ends

endif

DEFINE_GUIDS(CLSID_CActiveIMM, "4955DD33-B159-11d0-8FCF-00AA006BCC59")

endif

endif

endif
