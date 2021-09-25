.pragma list(push, 0)
ifndef _APISETLIBLOADER_
define _APISETLIBLOADER_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

;;??
ifndef _APISET_MINWIN_VERSION
_APISET_MINWIN_VERSION	equ 0x0100
endif

ifndef _APISET_LIBLOADER_VER
ifdef _APISET_MINWIN_VERSION
if _APISET_MINWIN_VERSION GE 0x0102
_APISET_LIBLOADER_VER	equ 0x0200
elseif _APISET_MINWIN_VERSION EQ 0x0101
_APISET_LIBLOADER_VER	equ 0x0101
elseif _APISET_MINWIN_VERSION LE 0x0100
_APISET_LIBLOADER_VER	equ 0x0100
endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

FIND_RESOURCE_DIRECTORY_TYPES equ (0x0100)
FIND_RESOURCE_DIRECTORY_NAMES equ (0x0200)
FIND_RESOURCE_DIRECTORY_LANGUAGES equ (0x0400)

RESOURCE_ENUM_LN	equ (0x0001)
RESOURCE_ENUM_MUI	equ (0x0002)
RESOURCE_ENUM_MUI_SYSTEM equ (0x0004)
RESOURCE_ENUM_VALIDATE	equ (0x0008)
RESOURCE_ENUM_MODULE_EXACT equ (0x0010)

SUPPORT_LANG_NUMBER	equ 32
LPLANGID		typedef ptr LANGID
ENUMUILANG		STRUC
NumOfEnumUILang		ULONG ? ;; Acutall number of enumerated languages
SizeOfEnumUIBuffer	ULONG ? ;; Buffer size of pMUIEnumUILanguages
pEnumUIBuffer		LPLANGID ?
ENUMUILANG		ENDS
PENUMUILANG		typedef ptr ENUMUILANG

ifdef STRICT

CALLBACK(ENUMRESLANGPROCA, :HMODULE, :LPCSTR, :LPCSTR, :WORD, :LONG_PTR)
CALLBACK(ENUMRESLANGPROCW, :HMODULE, :LPCWSTR, :LPCWSTR, :WORD, :LONG_PTR)
ifdef _UNICODE
ENUMRESLANGPROC		typedef ENUMRESLANGPROCW
else
ENUMRESLANGPROC		typedef ENUMRESLANGPROCA
endif

CALLBACK(ENUMRESNAMEPROCA, :HMODULE, :LPCSTR, :LPSTR, :LONG_PTR)
CALLBACK(ENUMRESNAMEPROCW, :HMODULE, :LPCWSTR, :LPWSTR, :LONG_PTR)
ifdef _UNICODE
ENUMRESNAMEPROC		typedef ENUMRESNAMEPROCW
else
ENUMRESNAMEPROC		typedef ENUMRESNAMEPROCA
endif

CALLBACK(ENUMRESTYPEPROCA, :HMODULE, :LPSTR, :LONG_PTR)
CALLBACK(ENUMRESTYPEPROCW, :HMODULE, :LPWSTR, :LONG_PTR)
ifdef _UNICODE
ENUMRESTYPEPROC		typedef ENUMRESTYPEPROCW
else
ENUMRESTYPEPROC		typedef ENUMRESTYPEPROCA
endif

else

ENUMRESTYPEPROCA	typedef FARPROC
ENUMRESTYPEPROCW	typedef FARPROC
ifdef _UNICODE
ENUMRESTYPEPROC		typedef ENUMRESTYPEPROCW
else
ENUMRESTYPEPROC		typedef ENUMRESTYPEPROCA
endif
ENUMRESNAMEPROCA	typedef FARPROC
ENUMRESNAMEPROCW	typedef FARPROC
ifdef _UNICODE
ENUMRESNAMEPROC		typedef ENUMRESNAMEPROCW
else
ENUMRESNAMEPROC		typedef ENUMRESNAMEPROCA
endif
ENUMRESLANGPROCA	typedef FARPROC
ENUMRESLANGPROCW	typedef FARPROC
ifdef _UNICODE
ENUMRESLANGPROC		typedef ENUMRESLANGPROCW
else
ENUMRESLANGPROC		typedef ENUMRESLANGPROCA
endif

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
DisableThreadLibraryCalls proto WINAPI \
	    hLibModule: HMODULE
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
FindResourceExW proto WINAPI \
	       hModule: HMODULE,
		lpType: LPCWSTR,
		lpName: LPCWSTR,
	     wLanguage: DWORD;WORD

ifdef _UNICODE
FindResourceEx equ <FindResourceExW>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (_WIN32_WINNT GE _WIN32_WINNT_WIN7)
FindStringOrdinal proto WINAPI \
dwFindStringOrdinalFlags: DWORD,
	lpStringSource: LPCWSTR,
	     cchSource: SINT,
	 lpStringValue: LPCWSTR,
	      cchValue: SINT,
	   bIgnoreCase: BOOL
endif
FreeLibrary proto WINAPI \
	    hLibModule: HMODULE
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

FreeLibraryAndExitThread proto WINAPI \
	    hLibModule: HMODULE,
	    dwExitCode: DWORD

FreeResource proto WINAPI \
	      hResData: HGLOBAL

GetModuleFileNameA proto WINAPI \
	       hModule: HMODULE,
	    lpFilename: LPSTR,
		 nSize: DWORD

GetModuleFileNameW proto WINAPI \
	       hModule: HMODULE,
	    lpFilename: LPWSTR,
		 nSize: DWORD

ifdef _UNICODE
GetModuleFileName equ <GetModuleFileNameW>
else
GetModuleFileName equ <GetModuleFileNameA>
endif

GetModuleHandleA proto WINAPI \
	  lpModuleName: LPCSTR

GetModuleHandleW proto WINAPI \
	  lpModuleName: LPCWSTR

ifdef _UNICODE
GetModuleHandle equ <GetModuleHandleW>
else
GetModuleHandle equ <GetModuleHandleA>
endif

ifndef RC_INVOKED

GET_MODULE_HANDLE_EX_FLAG_PIN equ (0x00000001)
GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT equ (0x00000002)
GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS equ (0x00000004)

CALLBACK(PGET_MODULE_HANDLE_EXA, :DWORD, :LPCSTR, :ptr HMODULE)
CALLBACK(PGET_MODULE_HANDLE_EXW, :DWORD, :LPCWSTR, :ptr HMODULE)
ifdef _UNICODE
PGET_MODULE_HANDLE_EX	equ <PGET_MODULE_HANDLE_EXW>
else
PGET_MODULE_HANDLE_EX	equ <PGET_MODULE_HANDLE_EXA>
endif

GetModuleHandleExA proto WINAPI \
	       dwFlags: DWORD,
	  lpModuleName: LPCSTR,
	      phModule: ptr HMODULE

GetModuleHandleExW proto WINAPI \
	       dwFlags: DWORD,
	  lpModuleName: LPCWSTR,
	      phModule: ptr HMODULE

ifdef _UNICODE
GetModuleHandleEx equ <GetModuleHandleExW>
else
GetModuleHandleEx equ <GetModuleHandleExA>
endif

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

GetProcAddress proto WINAPI \
	       hModule: HMODULE,
	    lpProcName: LPCSTR


endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

LoadLibraryExA proto WINAPI \
	 lpLibFileName: LPCSTR,
		 hFile: HANDLE,
	       dwFlags: DWORD

LoadLibraryExW proto WINAPI \
	 lpLibFileName: LPCWSTR,
		 hFile: HANDLE,
	       dwFlags: DWORD

ifdef _UNICODE
LoadLibraryEx equ <LoadLibraryExW>
else
LoadLibraryEx equ <LoadLibraryExA>
endif

DONT_RESOLVE_DLL_REFERENCES equ 0x00000001
LOAD_LIBRARY_AS_DATAFILE equ 0x00000002
;; reserved for internal LOAD_PACKAGED_LIBRARY: 0x00000004
LOAD_WITH_ALTERED_SEARCH_PATH equ 0x00000008
LOAD_IGNORE_CODE_AUTHZ_LEVEL equ 0x00000010
LOAD_LIBRARY_AS_IMAGE_RESOURCE equ 0x00000020
LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE equ 0x00000040
LOAD_LIBRARY_REQUIRE_SIGNED_TARGET equ 0x00000080
LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR equ 0x00000100
LOAD_LIBRARY_SEARCH_APPLICATION_DIR equ 0x00000200
LOAD_LIBRARY_SEARCH_USER_DIRS equ 0x00000400
LOAD_LIBRARY_SEARCH_SYSTEM32 equ 0x00000800
LOAD_LIBRARY_SEARCH_DEFAULT_DIRS equ 0x00001000

LoadResource proto WINAPI \
	       hModule: HMODULE,
	      hResInfo: HRSRC


endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

LoadStringA proto WINAPI \
	     hInstance: HINSTANCE,
		   uID: UINT,
	      lpBuffer: LPSTR,
	  cchBufferMax: SINT

LoadStringW proto WINAPI \
	     hInstance: HINSTANCE,
		   uID: UINT,
	      lpBuffer: LPWSTR,
	  cchBufferMax: SINT

ifdef _UNICODE
LoadString		equ <LoadStringW>
else
LoadString		equ <LoadStringA>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
LockResource proto WINAPI \
	      hResData: HGLOBAL

SizeofResource proto WINAPI \
	       hModule: HMODULE,
	      hResInfo: HRSRC
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

PDLL_DIRECTORY_COOKIE	typedef ptr DLL_DIRECTORY_COOKIE

AddDllDirectory proto WINAPI \
	  NewDirectory: PCWSTR


RemoveDllDirectory proto WINAPI \
		Cookie: DLL_DIRECTORY_COOKIE

SetDefaultDllDirectories proto WINAPI \
	DirectoryFlags: DWORD

endif

if (defined(_CONTRACT_GEN) eq 0) OR (_APISET_LIBLOADER_VER GE 0x0100)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


if (_WIN32_WINNT GE _WIN32_WINNT_VISTA)

EnumResourceLanguagesExA proto WINAPI \
	       hModule: HMODULE,
		lpType: LPCSTR,
		lpName: LPCSTR,
	    lpEnumFunc: ENUMRESLANGPROCA,
		lParam: LONG_PTR,
	       dwFlags: DWORD,
		LangId: LANGID

EnumResourceLanguagesExW proto WINAPI \
	       hModule: HMODULE,
		lpType: LPCWSTR,
		lpName: LPCWSTR,
	    lpEnumFunc: ENUMRESLANGPROCW,
		lParam: LONG_PTR,
	       dwFlags: DWORD,
		LangId: LANGID

ifdef _UNICODE
EnumResourceLanguagesEx equ <EnumResourceLanguagesExW>
else
EnumResourceLanguagesEx equ <EnumResourceLanguagesExA>
endif

EnumResourceNamesExA proto WINAPI \
	       hModule: HMODULE,
		lpType: LPCSTR,
	    lpEnumFunc: ENUMRESNAMEPROCA,
		lParam: LONG_PTR,
	       dwFlags: DWORD,
		LangId: LANGID

EnumResourceNamesExW proto WINAPI \
	       hModule: HMODULE,
		lpType: LPCWSTR,
	    lpEnumFunc: ENUMRESNAMEPROCW,
		lParam: LONG_PTR,
	       dwFlags: DWORD,
		LangId: LANGID

ifdef _UNICODE
EnumResourceNamesEx	equ <EnumResourceNamesExW>
else
EnumResourceNamesEx	equ <EnumResourceNamesExA>
endif

EnumResourceTypesExA proto WINAPI \
	       hModule: HMODULE,
	    lpEnumFunc: ENUMRESTYPEPROCA,
		lParam: LONG_PTR,
	       dwFlags: DWORD,
		LangId: LANGID

EnumResourceTypesExW proto WINAPI \
	       hModule: HMODULE,
	    lpEnumFunc: ENUMRESTYPEPROCW,
		lParam: LONG_PTR,
	       dwFlags: DWORD,
		LangId: LANGID

ifdef _UNICODE
EnumResourceTypesEx	equ <EnumResourceTypesExW>
else
EnumResourceTypesEx	equ <EnumResourceTypesExA>
endif

endif ;; (_WIN32_WINNT GE _WIN32_WINNT_VISTA)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; NOT defined(_CONTRACT_GEN) OR (_APISET_LIBLOADER_VER GE 0x0100)

endif ;; _APISETLIBLOADER_
.pragma list(pop)
