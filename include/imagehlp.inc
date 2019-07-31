ifndef _IMAGEHLP_
_IMAGEHLP_ equ <>
.pragma list(push, 0)

ifdef _WIN64
ifndef _IMAGEHLP64
_IMAGEHLP64 equ <>
endif
endif

.pragma pack(push, 8)

ifndef WINTRUST_H
include wintrust.inc
endif

ifdef _IMAGEHLP_SOURCE_
IMAGEAPI		equ <__stdcall>
DBHLP_DEPRECIATED	equ 1
else
IMAGEAPI		equ <DECLSPEC_IMPORT __stdcall>
if (_MSC_VER GE 1300) AND NOT defined(MIDL_PASS)
DBHLP_DEPRECIATED	equ <__declspec(deprecated)>
else
DBHLP_DEPRECIATED	equ 1
endif
endif

DBHLPAPI		equ IMAGEAPI

IMAGE_SEPARATION	equ (64*1024)

LOADED_IMAGE		STRUC
ModuleName		PSTR ?
hFile			HANDLE ?
MappedAddress		PUCHAR ?
ifdef _IMAGEHLP64
FileHeader		PIMAGE_NT_HEADERS64 ?
else
FileHeader		PIMAGE_NT_HEADERS32 ?
endif
LastRvaSection		PIMAGE_SECTION_HEADER ?
NumberOfSections	ULONG ?
Sections		PIMAGE_SECTION_HEADER ?
Characteristics		ULONG ?
fSystemImage		BOOLEAN ?
fDOSImage		BOOLEAN ?
fReadOnly		BOOLEAN ?
Version			UCHAR ?
Links			LIST_ENTRY <>
SizeOfImage		ULONG ?
LOADED_IMAGE		ENDS
PLOADED_IMAGE		typedef ptr LOADED_IMAGE

MAX_SYM_NAME		equ 2000

;BOOL
BindImage proto WINAPI \
	     ImageName: PCSTR,
	       DllPath: PCSTR,
	    SymbolPath: PCSTR

IMAGEHLP_STATUS_REASON	typedef SDWORD
BindOutOfMemory		equ 0
BindRvaToVaFailed	equ 1
BindNoRoomInImage	equ 2
BindImportModuleFailed	equ 3
BindImportProcedureFailed equ 4
BindImportModule	equ 5
BindImportProcedure	equ 6
BindForwarder		equ 7
BindForwarderNOT	equ 8
BindImageModified	equ 9
BindExpandFileHeaders	equ 10
BindImageComplete	equ 11
BindMismatchedSymbols	equ 12
BindSymbolsNotUpdated	equ 13
BindImportProcedure32	equ 14
BindImportProcedure64	equ 15
BindForwarder32		equ 16
BindForwarder64		equ 17
BindForwarderNOT32	equ 18
BindForwarderNOT64	equ 19

CALLBACK(PIMAGEHLP_STATUS_ROUTINE, :IMAGEHLP_STATUS_REASON, :PCSTR, :PCSTR, :ULONG_PTR, :ULONG_PTR)
CALLBACK(PIMAGEHLP_STATUS_ROUTINE32, :IMAGEHLP_STATUS_REASON, :PCSTR, :PCSTR, :ULONG, :ULONG_PTR)
CALLBACK(PIMAGEHLP_STATUS_ROUTINE64, :IMAGEHLP_STATUS_REASON, :PCSTR, :PCSTR, :ULONG64, :ULONG_PTR)

;BOOL
BindImageEx proto WINAPI \
		 Flags: DWORD,
	     ImageName: PCSTR,
	       DllPath: PCSTR,
	    SymbolPath: PCSTR,
	 StatusRoutine: PIMAGEHLP_STATUS_ROUTINE


BIND_NO_BOUND_IMPORTS	equ 0x00000001
BIND_NO_UPDATE		equ 0x00000002
BIND_ALL_IMAGES		equ 0x00000004
BIND_CACHE_IMPORT_DLLS	equ 0x00000008
BIND_REPORT_64BIT_VA	equ 0x00000010

;BOOL
ReBaseImage proto WINAPI \
      CurrentImageName: PCSTR,
	    SymbolPath: PCSTR,
	       fReBase: BOOL,
      fRebaseSysfileOk: BOOL,
	    fGoingDown: BOOL,
	CheckImageSize: ULONG,
	  OldImageSize: ptr ULONG,
	  OldImageBase: ptr ULONG_PTR,
	  NewImageSize: ptr ULONG,
	  NewImageBase: ptr ULONG_PTR,
	     TimeStamp: ULONG

;BOOL
ReBaseImage64 proto WINAPI \
      CurrentImageName: PCSTR,
	    SymbolPath: PCSTR,
	       fReBase: BOOL,
      fRebaseSysfileOk: BOOL,
	    fGoingDown: BOOL,
	CheckImageSize: ULONG,
	  OldImageSize: ptr ULONG,
	  OldImageBase: ptr ULONG64,
	  NewImageSize: ptr ULONG,
	  NewImageBase: ptr ULONG64,
	     TimeStamp: ULONG

CHECKSUM_SUCCESS	equ 0
CHECKSUM_OPEN_FAILURE	equ 1
CHECKSUM_MAP_FAILURE	equ 2
CHECKSUM_MAPVIEW_FAILURE equ 3
CHECKSUM_UNICODE_FAILURE equ 4

SPLITSYM_REMOVE_PRIVATE equ 0x00000001
SPLITSYM_EXTRACT_ALL	equ 0x00000002
SPLITSYM_SYMBOLPATH_IS_SRC equ 0x00000004

;PIMAGE_NT_HEADERS
;IMAGEAPI
CheckSumMappedFile proto WINAPI \
	   BaseAddress: PVOID,
	    FileLength: DWORD,
	     HeaderSum: PDWORD,
	      CheckSum: PDWORD

;DWORD
MapFileAndCheckSumA proto WINAPI \
	      Filename: PCSTR,
	     HeaderSum: PDWORD,
	      CheckSum: PDWORD


;DWORD
MapFileAndCheckSumW proto WINAPI \
	      Filename: PCWSTR,
	     HeaderSum: PDWORD,
	      CheckSum: PDWORD


ifdef _UNICODE
MapFileAndCheckSum	equ <MapFileAndCheckSumW>
else
MapFileAndCheckSum	equ <MapFileAndCheckSumA>
endif

;BOOL
GetImageConfigInformation proto WINAPI \
	   LoadedImage: PLOADED_IMAGE,
ImageConfigInformation: PIMAGE_LOAD_CONFIG_DIRECTORY


;DWORD
GetImageUnusedHeaderBytes proto WINAPI \
	   LoadedImage: PLOADED_IMAGE,
 SizeUnusedHeaderBytes: PDWORD


;BOOL
SetImageConfigInformation proto WINAPI \
	   LoadedImage: PLOADED_IMAGE,
ImageConfigInformation: PIMAGE_LOAD_CONFIG_DIRECTORY


CERT_PE_IMAGE_DIGEST_DEBUG_INFO equ 0x01
CERT_PE_IMAGE_DIGEST_RESOURCES equ 0x02
CERT_PE_IMAGE_DIGEST_ALL_IMPORT_INFO equ 0x04
CERT_PE_IMAGE_DIGEST_NON_PE_INFO equ 0x08

CERT_SECTION_TYPE_ANY	equ 0xFF

DIGEST_HANDLE		typedef PVOID

CALLBACK(DIGEST_FUNCTION, :DIGEST_HANDLE, :PBYTE, :DWORD)

;BOOL
ImageGetDigestStream proto WINAPI \
	    FileHandle: HANDLE,
	   DigestLevel: DWORD,
	DigestFunction: DIGEST_FUNCTION,
	  DigestHandle: DIGEST_HANDLE


;BOOL
ImageAddCertificate proto WINAPI \
	    FileHandle: HANDLE,
	   Certificate: LPWIN_CERTIFICATE,
		 Index: PDWORD


;BOOL
ImageRemoveCertificate proto WINAPI \
	    FileHandle: HANDLE,
		 Index: DWORD


;BOOL
ImageEnumerateCertificates proto WINAPI \
	    FileHandle: HANDLE,
	    TypeFilter: WORD,
      CertificateCount: PDWORD,
	       Indices: PDWORD,
	    IndexCount: DWORD


;BOOL
ImageGetCertificateData proto WINAPI \
	    FileHandle: HANDLE,
      CertificateIndex: DWORD,
	   Certificate: LPWIN_CERTIFICATE,
	RequiredLength: PDWORD


;BOOL
ImageGetCertificateHeader proto WINAPI \
	    FileHandle: HANDLE,
      CertificateIndex: DWORD,
     Certificateheader: LPWIN_CERTIFICATE


;PLOADED_IMAGE
;IMAGEAPI
ImageLoad proto WINAPI \
	       DllName: PCSTR,
	       DllPath: PCSTR

;BOOL
ImageUnload proto WINAPI \
	   LoadedImage: PLOADED_IMAGE

;BOOL
MapAndLoad proto WINAPI \
	     ImageName: PCSTR,
	       DllPath: PCSTR,
	   LoadedImage: PLOADED_IMAGE,
		DotDll: BOOL,
	      ReadOnly: BOOL

;BOOL
UnMapAndLoad proto WINAPI \
	   LoadedImage: PLOADED_IMAGE

;BOOL
TouchFileTimes proto WINAPI \
	    FileHandle: HANDLE,
	   pSystemTime: PSYSTEMTIME

;BOOL
SplitSymbols proto WINAPI \
	     ImageName: PSTR,
	   SymbolsPath: PCSTR,
	SymbolFilePath: PSTR,
		 Flags: ULONG

;BOOL
UpdateDebugInfoFile proto WINAPI \
	 ImageFileName: PCSTR,
	    SymbolPath: PCSTR,
	 DebugFilePath: PSTR,
	     NtHeaders: PIMAGE_NT_HEADERS32

;BOOL
UpdateDebugInfoFileEx proto WINAPI \
	 ImageFileName: PCSTR,
	    SymbolPath: PCSTR,
	 DebugFilePath: PSTR,
	     NtHeaders: PIMAGE_NT_HEADERS32,
	   OldCheckSum: DWORD


ERROR_IMAGE_NOT_STRIPPED equ 0x8800
ERROR_NO_DBG_POINTER	equ 0x8801
ERROR_NO_PDB_POINTER	equ 0x8802

CALLBACK(PFIND_DEBUG_FILE_CALLBACK, :HANDLE, :PCSTR, :PVOID)

;HANDLE
SymFindDebugInfoFile proto WINAPI \
	      hProcess: HANDLE,
	      FileName: PCSTR,
	 DebugFilePath: PSTR,
	      Callback: PFIND_DEBUG_FILE_CALLBACK,
	    CallerData: PVOID

CALLBACK(PFIND_DEBUG_FILE_CALLBACKW, :HANDLE, :PCWSTR, :PVOID)

;HANDLE
SymFindDebugInfoFileW proto WINAPI \
	      hProcess: HANDLE,
	      FileName: PCWSTR,
	 DebugFilePath: PWSTR,
	      Callback: PFIND_DEBUG_FILE_CALLBACKW,
	    CallerData: PVOID


;HANDLE
FindDebugInfoFile proto WINAPI \
	      FileName: PCSTR,
	    SymbolPath: PCSTR,
	 DebugFilePath: PSTR

;HANDLE
FindDebugInfoFileEx proto WINAPI \
	      FileName: PCSTR,
	    SymbolPath: PCSTR,
	 DebugFilePath: PSTR,
	      Callback: PFIND_DEBUG_FILE_CALLBACK,
	    CallerData: PVOID


;HANDLE
FindDebugInfoFileExW proto WINAPI \
	      FileName: PCWSTR,
	    SymbolPath: PCWSTR,
	 DebugFilePath: PSTR,
	      Callback: PFIND_DEBUG_FILE_CALLBACKW,
	    CallerData: PVOID


CALLBACK(PFINDFILEINPATHCALLBACK, :PCSTR, :PVOID)

;BOOL
SymFindFileInPath proto WINAPI \
	      hprocess: HANDLE,
	    SearchPath: PCSTR,
	      FileName: PCSTR,
		    id: PVOID,
		   two: DWORD,
		 three: DWORD,
		 flags: DWORD,
	     FoundFile: PSTR,
	      callback: PFINDFILEINPATHCALLBACK,
	       context: PVOID


CALLBACK(PFINDFILEINPATHCALLBACKW, :PCWSTR, :PVOID)

;BOOL
SymFindFileInPathW proto WINAPI \
	      hprocess: HANDLE,
	    SearchPath: PCWSTR,
	      FileName: PCWSTR,
		    id: PVOID,
		   two: DWORD,
		 three: DWORD,
		 flags: DWORD,
	     FoundFile: PWSTR,
	      callback: PFINDFILEINPATHCALLBACKW,
	       context: PVOID


CALLBACK(PFIND_EXE_FILE_CALLBACK, :HANDLE, :PCSTR, :PVOID)

;HANDLE
SymFindExecutableImage proto WINAPI \
	      hProcess: HANDLE,
	      FileName: PCSTR,
	 ImageFilePath: PSTR,
	      Callback: PFIND_EXE_FILE_CALLBACK,
	    CallerData: PVOID


CALLBACK(PFIND_EXE_FILE_CALLBACKW, :HANDLE, :PCWSTR, :PVOID)

;HANDLE
SymFindExecutableImageW proto WINAPI \
	      hProcess: HANDLE,
	      FileName: PCWSTR,
	 ImageFilePath: PWSTR,
	      Callback: PFIND_EXE_FILE_CALLBACKW,
	    CallerData: PVOID


;HANDLE
FindExecutableImage proto WINAPI \
	      FileName: PCSTR,
	    SymbolPath: PCSTR,
	 ImageFilePath: PSTR

;HANDLE
FindExecutableImageEx proto WINAPI \
	      FileName: PCSTR,
	    SymbolPath: PCSTR,
	 ImageFilePath: PSTR,
	      Callback: PFIND_EXE_FILE_CALLBACK,
	    CallerData: PVOID


;HANDLE
FindExecutableImageExW proto WINAPI \
	      FileName: PCWSTR,
	    SymbolPath: PCWSTR,
	 ImageFilePath: PWSTR,
	      Callback: PFIND_EXE_FILE_CALLBACKW,
	    CallerData: PVOID


;PIMAGE_NT_HEADERS
;IMAGEAPI
ImageNtHeader proto WINAPI \
		  Base: PVOID

;PVOID
ImageDirectoryEntryToDataEx proto WINAPI \
		  Base: PVOID,
	 MappedAsImage: BOOLEAN,
	DirectoryEntry: USHORT,
		  Size: PULONG,
	   FoundHeader: ptr PIMAGE_SECTION_HEADER


;PVOID
ImageDirectoryEntryToData proto WINAPI \
		  Base: PVOID,
	 MappedAsImage: BOOLEAN,
	DirectoryEntry: USHORT,
		  Size: PULONG


;PIMAGE_SECTION_HEADER
;IMAGEAPI
ImageRvaToSection proto WINAPI \
	     NtHeaders: PIMAGE_NT_HEADERS,
		  Base: PVOID,
		   Rva: ULONG

;PVOID
ImageRvaToVa proto WINAPI \
	     NtHeaders: PIMAGE_NT_HEADERS,
		  Base: PVOID,
		   Rva: ULONG,
	LastRvaSection: PIMAGE_SECTION_HEADER

ifndef _WIN64

IMAGE_DEBUG_INFORMATION	 STRUC
List			LIST_ENTRY <>
ReservedSize		dd ?
ReservedMappedBase	PVOID ?
ReservedMachine		USHORT ?
ReservedCharacteristics USHORT ?
ReservedCheckSum	dd ?
ImageBase		dd ?
SizeOfImage		dd ?
ReservedNumberOfSections dd ?
ReservedSections	PIMAGE_SECTION_HEADER ?
ReservedExportedNamesSize dd ?
ReservedExportedNames	PSTR ?
ReservedNumberOfFunctionTableEntries dd ?
ReservedFunctionTableEntries PIMAGE_FUNCTION_ENTRY ?
ReservedLowestFunctionStartingAddress dd ?
ReservedHighestFunctionEndingAddress dd ?
ReservedNumberOfFpoTableEntries dd ?
ReservedFpoTableEntries PFPO_DATA ?
SizeOfCoffSymbols	dd ?
CoffSymbols		PIMAGE_COFF_SYMBOLS_HEADER ?
ReservedSizeOfCodeViewSymbols dd ?
ReservedCodeViewSymbols PVOID ?
ImageFilePath		PSTR ?
ImageFileName		PSTR ?
ReservedDebugFilePath	PSTR ?
ReservedTimeDateStamp	dd ?
ReservedRomImage	BOOL ?
ReservedDebugDirectory	PIMAGE_DEBUG_DIRECTORY ?
ReservedNumberOfDebugDirectories dd ?
ReservedOriginalFunctionTableBaseAddress dd ?
Reserved		dd  2  dup(?)
IMAGE_DEBUG_INFORMATION ENDS
PIMAGE_DEBUG_INFORMATION typedef ptr IMAGE_DEBUG_INFORMATION

;PIMAGE_DEBUG_INFORMATION
;IMAGEAPI
MapDebugInformation proto WINAPI \
	    FileHandle: HANDLE,
	      FileName: PCSTR,
	    SymbolPath: PCSTR,
	     ImageBase: ULONG

;BOOL
UnmapDebugInformation proto WINAPI \
	     DebugInfo: PIMAGE_DEBUG_INFORMATION

endif

;BOOL
SearchTreeForFile proto WINAPI \
	      RootPath: PCSTR,
	 InputPathName: PCSTR,
      OutputPathBuffer: PSTR

;BOOL
SearchTreeForFileW proto WINAPI \
	      RootPath: PCWSTR,
	 InputPathName: PCWSTR,
      OutputPathBuffer: PWSTR

CALLBACK(PENUMDIRTREE_CALLBACK, :PCSTR, :PVOID)

;BOOL
EnumDirTree proto WINAPI \
	      hProcess: HANDLE,
	      RootPath: PCSTR,
	 InputPathName: PCSTR,
      OutputPathBuffer: PSTR,
		    cb: PENUMDIRTREE_CALLBACK,
		  data: PVOID


CALLBACK(PENUMDIRTREE_CALLBACKW, :PCWSTR, :PVOID)

;BOOL
EnumDirTreeW proto WINAPI \
	      hProcess: HANDLE,
	      RootPath: PCWSTR,
	 InputPathName: PCWSTR,
      OutputPathBuffer: PWSTR,
		    cb: PENUMDIRTREE_CALLBACKW,
		  data: PVOID
;BOOL
MakeSureDirectoryPathExists proto WINAPI \
	       DirPath: PCSTR



UNDNAME_COMPLETE	equ (0x0000)
UNDNAME_NO_LEADING_UNDERSCORES equ (0x0001)
UNDNAME_NO_MS_KEYWORDS	equ (0x0002)
UNDNAME_NO_FUNCTION_RETURNS equ (0x0004)
UNDNAME_NO_ALLOCATION_MODEL equ (0x0008)
UNDNAME_NO_ALLOCATION_LANGUAGE equ (0x0010)
UNDNAME_NO_MS_THISTYPE	equ (0x0020)
UNDNAME_NO_CV_THISTYPE	equ (0x0040)
UNDNAME_NO_THISTYPE	equ (0x0060)
UNDNAME_NO_ACCESS_SPECIFIERS equ (0x0080)
UNDNAME_NO_THROW_SIGNATURES equ (0x0100)
UNDNAME_NO_MEMBER_TYPE	equ (0x0200)
UNDNAME_NO_RETURN_UDT_MODEL equ (0x0400)
UNDNAME_32_BIT_DECODE	equ (0x0800)
UNDNAME_NAME_ONLY	equ (0x1000)
UNDNAME_NO_ARGUMENTS	equ (0x2000)
UNDNAME_NO_SPECIAL_SYMS equ (0x4000)

;DWORD
UnDecorateSymbolName proto WINAPI \
		  name: PCSTR,
	  outputString: PSTR,
       maxStringLength: DWORD,
		 flags: DWORD

;DWORD
UnDecorateSymbolNameW proto WINAPI \
		  name: PCWSTR,
	  outputString: PWSTR,
       maxStringLength: DWORD,
		 flags: DWORD

DBHHEADER_DEBUGDIRS	equ 0x1
DBHHEADER_CVMISC	equ 0x2
DBHHEADER_PDBGUID	equ 0x3
MODLOAD_DATA		STRUC
ssize			dd ?
ssig			dd ?
data			PVOID ?
size			dd ?
flags			dd ?
MODLOAD_DATA		ENDS
PMODLOAD_DATA		typedef ptr MODLOAD_DATA

MODLOAD_CVMISC		STRUC
oCV			dd ?
cCV			size_t ?
oMisc			dd ?
cMisc			size_t ?
dtImage			dd ?
cImage			dd ?
MODLOAD_CVMISC		ENDS
PMODLOAD_CVMISC		typedef ptr MODLOAD_CVMISC

MODLOAD_PDBGUID_PDBAGE	STRUC
PdbGuid			GUID <>
PdbAge			dd ?
MODLOAD_PDBGUID_PDBAGE	ENDS
PMODLOAD_PDBGUID_PDBAGE typedef ptr MODLOAD_PDBGUID_PDBAGE


ADDRESS_MODE		typedef SDWORD
AddrMode1616		equ 0
AddrMode1632		equ 1
AddrModeReal		equ 2
AddrModeFlat		equ 3

ADDRESS64		STRUC
_Offset			dd ?
_Segment		dw ?
_Mode			ADDRESS_MODE ?
ADDRESS64		ENDS
LPADDRESS64		typedef ptr ADDRESS64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
ADDRESS			equ ADDRESS64
LPADDRESS		equ LPADDRESS64
else
ADDRESS			STRUC
_Offset			dd ?
_Segment		dw ?
_Mode			ADDRESS_MODE ?
ADDRESS			ENDS
LPADDRESS		typedef ptr ADDRESS
endif

KDHELP64		STRUC
Thread			dd ?
ThCallbackStack		dd ?
ThCallbackBStore	dd ?
NextCallback		dd ?
FramePointer		dd ?
KiCallUserMode		dd ?
KeUserCallbackDispatcher dd ?
SystemRangeStart	dd ?
KiUserExceptionDispatcher dd ?
StackBase		dd ?
StackLimit		dd ?
Reserved		dd 5 dup(?)
KDHELP64		ENDS
PKDHELP64		typedef ptr KDHELP64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
KDHELP			equ KDHELP64
PKDHELP			equ PKDHELP64
else
KDHELP			STRUC
Thread			dd ?
ThCallbackStack		dd ?
NextCallback		dd ?
FramePointer		dd ?
KiCallUserMode		dd ?
KeUserCallbackDispatcher dd ?
SystemRangeStart	dd ?
ThCallbackBStore	dd ?
KiUserExceptionDispatcher dd ?
StackBase		dd ?
StackLimit		dd ?
Reserved		dd 5 dup(?)
KDHELP			ENDS
PKDHELP			typedef ptr KDHELP
endif

STACKFRAME64		STRUC
AddrPC			ADDRESS64 <>
AddrReturn		ADDRESS64 <>
AddrFrame		ADDRESS64 <>
AddrStack		ADDRESS64 <>
AddrBStore		ADDRESS64 <>
FuncTableEntry		PVOID ?
Params			dd 4 dup(?)
_Far			BOOL ?
Virtual			BOOL ?
Reserved		dd 3 dup(?)
KdHelp			KDHELP64 <>
STACKFRAME64		ENDS
LPSTACKFRAME64		typedef ptr STACKFRAME64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
STACKFRAME		equ STACKFRAME64
LPSTACKFRAME		equ LPSTACKFRAME64
else
STACKFRAME		STRUC
AddrPC			ADDRESS <>
AddrReturn		ADDRESS <>
AddrFrame		ADDRESS <>
AddrStack		ADDRESS <>
FuncTableEntry		PVOID ?
Params			dd 4 dup(?)
_Far			BOOL ?
Virtual			BOOL ?
Reserved		dd 3 dup(?)
KdHelp			KDHELP <>
AddrBStore		ADDRESS <>
STACKFRAME		ENDS
LPSTACKFRAME		typedef ptr STACKFRAME
endif


CALLBACK(PREAD_PROCESS_MEMORY_ROUTINE64, :HANDLE, :DWORD64)
CALLBACK(PFUNCTION_TABLE_ACCESS_ROUTINE64, :HANDLE, :DWORD64)
CALLBACK(PGET_MODULE_BASE_ROUTINE64, :HANDLE, :DWORD64)
CALLBACK(PTRANSLATE_ADDRESS_ROUTINE64, :HANDLE, :HANDLE, :LPADDRESS64)

;BOOL
StackWalk64 proto WINAPI \
	   MachineType: DWORD,
	      hProcess: HANDLE,
	       hThread: HANDLE,
	    StackFrame: LPSTACKFRAME64,
	 ContextRecord: PVOID,
     ReadMemoryRoutine: PREAD_PROCESS_MEMORY_ROUTINE64,
FunctionTableAccessRoutine: PFUNCTION_TABLE_ACCESS_ROUTINE64,
  GetModuleBaseRoutine: PGET_MODULE_BASE_ROUTINE64,
      TranslateAddress: PTRANSLATE_ADDRESS_ROUTINE64


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)

PREAD_PROCESS_MEMORY_ROUTINE equ PREAD_PROCESS_MEMORY_ROUTINE64
PFUNCTION_TABLE_ACCESS_ROUTINE equ PFUNCTION_TABLE_ACCESS_ROUTINE64
PGET_MODULE_BASE_ROUTINE equ PGET_MODULE_BASE_ROUTINE64
PTRANSLATE_ADDRESS_ROUTINE equ PTRANSLATE_ADDRESS_ROUTINE64

StackWalk		equ <StackWalk64>

else

CALLBACK(PREAD_PROCESS_MEMORY_ROUTINE, :HANDLE, :DWORD)
CALLBACK(PFUNCTION_TABLE_ACCESS_ROUTINE, :HANDLE, :DWORD)
CALLBACK(PGET_MODULE_BASE_ROUTINE, :HANDLE, :DWORD)
CALLBACK(PTRANSLATE_ADDRESS_ROUTINE, :HANDLE, :HANDLE, :LPADDRESS)

;BOOL
StackWalk proto WINAPI \
	   MachineType: DWORD,
	      hProcess: HANDLE,
	       hThread: HANDLE,
	    StackFrame: LPSTACKFRAME,
	 ContextRecord: PVOID,
     ReadMemoryRoutine: PREAD_PROCESS_MEMORY_ROUTINE,
FunctionTableAccessRoutine: PFUNCTION_TABLE_ACCESS_ROUTINE,
  GetModuleBaseRoutine: PGET_MODULE_BASE_ROUTINE,
      TranslateAddress: PTRANSLATE_ADDRESS_ROUTINE


endif


API_VERSION_NUMBER	equ 11

API_VERSION		STRUC
MajorVersion		USHORT ?
MinorVersion		USHORT ?
Revision		USHORT ?
Reserved		USHORT ?
API_VERSION		ENDS
LPAPI_VERSION		typedef ptr API_VERSION

;LPAPI_VERSION
ImagehlpApiVersion proto WINAPI

;LPAPI_VERSION
ImagehlpApiVersionEx proto WINAPI \
	    AppVersion: LPAPI_VERSION

;DWORD
GetTimestampForLoadedLibrary proto WINAPI \
		Module: HMODULE


CALLBACK(PSYM_ENUMMODULES_CALLBACK64, :PCSTR, :DWORD64, :PVOID)
CALLBACK(PSYM_ENUMMODULES_CALLBACKW64, :PCWSTR, :DWORD64, :PVOID)
CALLBACK(PENUMLOADED_MODULES_CALLBACK64, :PCSTR, :DWORD64, :ULONG, :PVOID)
CALLBACK(PENUMLOADED_MODULES_CALLBACKW64, :PCWSTR, :DWORD64, :ULONG, :PVOID)
CALLBACK(PSYM_ENUMSYMBOLS_CALLBACK64, :PCSTR, :DWORD64, :ULONG, :PVOID)
CALLBACK(PSYM_ENUMSYMBOLS_CALLBACK64W, :PCWSTR, :DWORD64, :ULONG, :PVOID)
CALLBACK(PSYMBOL_REGISTERED_CALLBACK64, :HANDLE, :ULONG, :ULONG64, :ULONG64)
CALLBACK(PSYMBOL_FUNCENTRY_CALLBACK64, :HANDLE, :ULONG64, :ULONG64)

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)

PSYM_ENUMMODULES_CALLBACK equ <PSYM_ENUMMODULES_CALLBACK64>
PSYM_ENUMSYMBOLS_CALLBACK equ <PSYM_ENUMSYMBOLS_CALLBACK64>
PSYM_ENUMSYMBOLS_CALLBACKW equ <PSYM_ENUMSYMBOLS_CALLBACK64W>
PENUMLOADED_MODULES_CALLBACK equ <PENUMLOADED_MODULES_CALLBACK64>
PSYMBOL_REGISTERED_CALLBACK equ <PSYMBOL_REGISTERED_CALLBACK64>
PSYMBOL_FUNCENTRY_CALLBACK equ <PSYMBOL_FUNCENTRY_CALLBACK64>

else

CALLBACK(PSYMBOL_FUNCENTRY_CALLBACK, :HANDLE, :DWORD, :PVOID)
CALLBACK(PSYM_ENUMMODULES_CALLBACK, :PCSTR, :ULONG, :PVOID)
CALLBACK(PSYM_ENUMSYMBOLS_CALLBACK, :PCSTR, :ULONG, :ULONG, :PVOID)
CALLBACK(PSYM_ENUMSYMBOLS_CALLBACKW, :PCWSTR, :ULONG, :ULONG, :PVOID)
CALLBACK(PENUMLOADED_MODULES_CALLBACK, :PCSTR, :ULONG, :ULONG, :PVOID)
CALLBACK(PSYMBOL_REGISTERED_CALLBACK, :HANDLE, :ULONG, :PVOID, :PVOID)

endif

ifdef _NO_CVCONST_H

SymTagEnum		typedef SDWORD
SymTagNull		equ 0
SymTagExe		equ 1
SymTagCompiland		equ 2
SymTagCompilandDetails	equ 3
SymTagCompilandEnv	equ 4
SymTagFunction		equ 5
SymTagBlock		equ 6
SymTagData		equ 7
SymTagAnnotation	equ 8
SymTagLabel		equ 9
SymTagPublicSymbol	equ 10
SymTagUDT		equ 11
SymTagEnum		equ 12
SymTagFunctionType	equ 13
SymTagPointerType	equ 14
SymTagArrayType		equ 15
SymTagBaseType		equ 16
SymTagTypedef		equ 17
SymTagBaseClass		equ 18
SymTagFriend		equ 19
SymTagFunctionArgType	equ 20
SymTagFuncDebugStart	equ 21
SymTagFuncDebugEnd	equ 22
SymTagUsingNamespace	equ 23
SymTagVTableShape	equ 24
SymTagVTable		equ 25
SymTagCustom		equ 26
SymTagThunk		equ 27
SymTagCustomType	equ 28
SymTagManagedType	equ 29
SymTagDimension		equ 30
SymTagMax		equ 31

endif


SYMFLAG_VALUEPRESENT	equ 0x00000001
SYMFLAG_REGISTER	equ 0x00000008
SYMFLAG_REGREL		equ 0x00000010
SYMFLAG_FRAMEREL	equ 0x00000020
SYMFLAG_PARAMETER	equ 0x00000040
SYMFLAG_LOCAL		equ 0x00000080
SYMFLAG_CONSTANT	equ 0x00000100
SYMFLAG_EXPORT		equ 0x00000200
SYMFLAG_FORWARDER	equ 0x00000400
SYMFLAG_FUNCTION	equ 0x00000800
SYMFLAG_VIRTUAL		equ 0x00001000
SYMFLAG_THUNK		equ 0x00002000
SYMFLAG_TLSREL		equ 0x00004000
SYMFLAG_SLOT		equ 0x00008000
SYMFLAG_ILREL		equ 0x00010000
SYMFLAG_METADATA	equ 0x00020000
SYMFLAG_CLR_TOKEN	equ 0x00040000


SYMFLAG_RESET		equ 0x80000000

SYM_TYPE		typedef SDWORD
SymNone			equ 0
SymCoff			equ 1
SymCv			equ 2
SymPdb			equ 3
SymExport		equ 4
SymDeferred		equ 5
SymSym			equ 6
SymDia			equ 7
SymVirtual		equ 8
NumSymTypes		equ 9

IMAGEHLP_SYMBOL64	STRUC
SizeOfStruct		dd ?
Address			dd ?
Size			dd ?
Flags			dd ?
MaxNameLength		dd ?
Name			CHAR 1 dup(?)
IMAGEHLP_SYMBOL64	ENDS
PIMAGEHLP_SYMBOL64	typedef ptr IMAGEHLP_SYMBOL64

IMAGEHLP_SYMBOL64_PACKAGE STRUC
sym			IMAGEHLP_SYMBOL64 <>
name			CHAR MAX_SYM_NAME + 1 dup(?)
IMAGEHLP_SYMBOL64_PACKAGE ENDS
PIMAGEHLP_SYMBOL64_PACKAGE typedef ptr IMAGEHLP_SYMBOL64_PACKAGE

IMAGEHLP_SYMBOLW64	STRUC
SizeOfStruct		dd ?
Address			dd ?
Size			dd ?
Flags			dd ?
MaxNameLength		dd ?
Name			WCHAR 1 dup(?)
IMAGEHLP_SYMBOLW64	ENDS
PIMAGEHLP_SYMBOLW64	typedef ptr IMAGEHLP_SYMBOLW64

IMAGEHLP_SYMBOLW64_PACKAGE STRUC
sym			IMAGEHLP_SYMBOLW64 <>
name			WCHAR MAX_SYM_NAME + 1 dup(?)
IMAGEHLP_SYMBOLW64_PACKAGE ENDS
PIMAGEHLP_SYMBOLW64_PACKAGE typedef ptr IMAGEHLP_SYMBOLW64_PACKAGE

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)

IMAGEHLP_SYMBOL		equ IMAGEHLP_SYMBOL64
PIMAGEHLP_SYMBOL	equ PIMAGEHLP_SYMBOL64
IMAGEHLP_SYMBOL_PACKAGE equ IMAGEHLP_SYMBOL64_PACKAGE
PIMAGEHLP_SYMBOL_PACKAGE equ PIMAGEHLP_SYMBOL64_PACKAGE
IMAGEHLP_SYMBOLW	equ IMAGEHLP_SYMBOLW64
PIMAGEHLP_SYMBOLW	equ PIMAGEHLP_SYMBOLW64
IMAGEHLP_SYMBOLW_PACKAGE equ IMAGEHLP_SYMBOLW64_PACKAGE
PIMAGEHLP_SYMBOLW_PACKAGE equ PIMAGEHLP_SYMBOLW64_PACKAGE

else

IMAGEHLP_SYMBOL		STRUC
SizeOfStruct		dd ?
Address			dd ?
Size			dd ?
Flags			dd ?
MaxNameLength		dd ?
Name			CHAR 1 dup(?)
IMAGEHLP_SYMBOL		ENDS
PIMAGEHLP_SYMBOL	typedef ptr IMAGEHLP_SYMBOL

IMAGEHLP_SYMBOL_PACKAGE	 STRUC
sym			IMAGEHLP_SYMBOL <>
name			CHAR MAX_SYM_NAME + 1 dup(?)
IMAGEHLP_SYMBOL_PACKAGE ENDS
PIMAGEHLP_SYMBOL_PACKAGE typedef ptr IMAGEHLP_SYMBOL_PACKAGE

IMAGEHLP_SYMBOLW	STRUC
SizeOfStruct		dd ?
Address			dd ?
Size			dd ?
Flags			dd ?
MaxNameLength		dd ?
Name			WCHAR 1 dup(?)
IMAGEHLP_SYMBOLW	ENDS
PIMAGEHLP_SYMBOLW	typedef ptr IMAGEHLP_SYMBOLW

IMAGEHLP_SYMBOLW_PACKAGE STRUC
sym			IMAGEHLP_SYMBOLW <>
name			WCHAR MAX_SYM_NAME + 1 dup(?)
IMAGEHLP_SYMBOLW_PACKAGE ENDS
PIMAGEHLP_SYMBOLW_PACKAGE typedef ptr IMAGEHLP_SYMBOLW_PACKAGE

endif


IMAGEHLP_MODULE64	STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
ImageSize		dd ?
TimeDateStamp		dd ?
CheckSum		dd ?
NumSyms			dd ?
SymType			SYM_TYPE ?
ModuleName		CHAR 32 dup(?)
ImageName		CHAR 256 dup(?)
LoadedImageName		CHAR 256 dup(?)
LoadedPdbName		CHAR 256 dup(?)
CVSig			dd ?
CVData			CHAR MAX_PATH * 3 dup(?)
PdbSig			dd ?
PdbSig70		GUID <>
PdbAge			dd ?
PdbUnmatched		BOOL ?
DbgUnmatched		BOOL ?
LineNumbers		BOOL ?
GlobalSymbols		BOOL ?
TypeInfo		BOOL ?
SourceIndexed		BOOL ?
Publics			BOOL ?
IMAGEHLP_MODULE64	ENDS
PIMAGEHLP_MODULE64	typedef ptr IMAGEHLP_MODULE64

IMAGEHLP_MODULEW64	STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
ImageSize		dd ?
TimeDateStamp		dd ?
CheckSum		dd ?
NumSyms			dd ?
SymType			SYM_TYPE ?
ModuleName		WCHAR 32 dup(?)
ImageName		WCHAR 256 dup(?)
LoadedImageName		WCHAR 256 dup(?)
LoadedPdbName		WCHAR 256 dup(?)
CVSig			dd ?
CVData			WCHAR MAX_PATH * 3 dup(?)
PdbSig			dd ?
PdbSig70		GUID <>
PdbAge			dd ?
PdbUnmatched		BOOL ?
DbgUnmatched		BOOL ?
LineNumbers		BOOL ?
GlobalSymbols		BOOL ?
TypeInfo		BOOL ?
SourceIndexed		BOOL ?
Publics			BOOL ?
IMAGEHLP_MODULEW64	ENDS
PIMAGEHLP_MODULEW64	typedef ptr IMAGEHLP_MODULEW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
IMAGEHLP_MODULE		equ IMAGEHLP_MODULE64
PIMAGEHLP_MODULE	equ PIMAGEHLP_MODULE64
IMAGEHLP_MODULEW	equ IMAGEHLP_MODULEW64
PIMAGEHLP_MODULEW	equ PIMAGEHLP_MODULEW64
else
IMAGEHLP_MODULE		STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
ImageSize		dd ?
TimeDateStamp		dd ?
CheckSum		dd ?
NumSyms			dd ?
SymType			SYM_TYPE ?
ModuleName		CHAR 32 dup(?)
ImageName		CHAR 256 dup(?)
LoadedImageName		CHAR 256 dup(?)
IMAGEHLP_MODULE		ENDS
PIMAGEHLP_MODULE	typedef ptr IMAGEHLP_MODULE

IMAGEHLP_MODULEW	STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
ImageSize		dd ?
TimeDateStamp		dd ?
CheckSum		dd ?
NumSyms			dd ?
SymType			SYM_TYPE ?
ModuleName		WCHAR 32 dup(?)
ImageName		WCHAR 256 dup(?)
LoadedImageName		WCHAR 256 dup(?)
IMAGEHLP_MODULEW	ENDS
PIMAGEHLP_MODULEW	typedef ptr IMAGEHLP_MODULEW
endif


IMAGEHLP_LINE64		STRUC
SizeOfStruct		dd ?
Key			PVOID ?
LineNumber		dd ?
FileName		PCHAR ?
Address			dd ?
IMAGEHLP_LINE64		ENDS
PIMAGEHLP_LINE64	typedef ptr IMAGEHLP_LINE64

IMAGEHLP_LINEW64	STRUC
SizeOfStruct		dd ?
Key			PVOID ?
LineNumber		dd ?
FileName		PWSTR ?
Address			dd ?
IMAGEHLP_LINEW64	ENDS
PIMAGEHLP_LINEW64	typedef ptr IMAGEHLP_LINEW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
IMAGEHLP_LINE		equ IMAGEHLP_LINE64
PIMAGEHLP_LINE		equ PIMAGEHLP_LINE64
else
IMAGEHLP_LINE		STRUC
SizeOfStruct		dd ?
Key			PVOID ?
LineNumber		dd ?
FileName		PCHAR ?
Address			dd ?
IMAGEHLP_LINE		ENDS
PIMAGEHLP_LINE		typedef ptr IMAGEHLP_LINE

IMAGEHLP_LINEW		STRUC
SizeOfStruct		dd ?
Key			PVOID ?
LineNumber		dd ?
FileName		PCHAR ?
Address			dd ?
IMAGEHLP_LINEW		ENDS
PIMAGEHLP_LINEW		typedef ptr IMAGEHLP_LINEW
endif


SOURCEFILE		STRUC
ModBase			dd ?
FileName		PCHAR ?
SOURCEFILE		ENDS
PSOURCEFILE		typedef ptr SOURCEFILE

SOURCEFILEW		STRUC
ModBase			dd ?
FileName		PWSTR ?
SOURCEFILEW		ENDS
PSOURCEFILEW		typedef ptr SOURCEFILEW


CBA_DEFERRED_SYMBOL_LOAD_START equ 0x00000001
CBA_DEFERRED_SYMBOL_LOAD_COMPLETE equ 0x00000002
CBA_DEFERRED_SYMBOL_LOAD_FAILURE equ 0x00000003
CBA_SYMBOLS_UNLOADED	equ 0x00000004
CBA_DUPLICATE_SYMBOL	equ 0x00000005
CBA_READ_MEMORY		equ 0x00000006
CBA_DEFERRED_SYMBOL_LOAD_CANCEL equ 0x00000007
CBA_SET_OPTIONS		equ 0x00000008
CBA_EVENT		equ 0x00000010
CBA_DEFERRED_SYMBOL_LOAD_PARTIAL equ 0x00000020
CBA_DEBUG_INFO		equ 0x10000000
CBA_SRCSRV_INFO		equ 0x20000000
CBA_SRCSRV_EVENT	equ 0x40000000

IMAGEHLP_CBA_READ_MEMORY STRUC
_addr			dd ?
buf			PVOID ?
bytes			dd ?
bytesread		LPDWORD ?
IMAGEHLP_CBA_READ_MEMORY ENDS
PIMAGEHLP_CBA_READ_MEMORY typedef ptr IMAGEHLP_CBA_READ_MEMORY

sevInfo			equ 0
sevProblem		equ 1
sevAttn			equ 2
sevFatal		equ 3
sevMax			equ 4

EVENT_SRCSPEW_START	equ 100
EVENT_SRCSPEW		equ 100
EVENT_SRCSPEW_END	equ 199

IMAGEHLP_CBA_EVENT	STRUC
severity		dd ?
code			dd ?
desc			PCHAR ?
object			PVOID ?
IMAGEHLP_CBA_EVENT	ENDS
PIMAGEHLP_CBA_EVENT	typedef ptr IMAGEHLP_CBA_EVENT

IMAGEHLP_CBA_EVENTW	STRUC
severity		dd ?
code			dd ?
desc			PCWSTR ?
object			PVOID ?
IMAGEHLP_CBA_EVENTW	ENDS
PIMAGEHLP_CBA_EVENTW	typedef ptr IMAGEHLP_CBA_EVENTW

IMAGEHLP_DEFERRED_SYMBOL_LOAD64	 STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
CheckSum		dd ?
TimeDateStamp		dd ?
FileName		CHAR MAX_PATH dup(?)
Reparse			BOOLEAN ?
hFile			HANDLE ?
Flags			dd ?
IMAGEHLP_DEFERRED_SYMBOL_LOAD64 ENDS
PIMAGEHLP_DEFERRED_SYMBOL_LOAD64 typedef ptr IMAGEHLP_DEFERRED_SYMBOL_LOAD64

IMAGEHLP_DEFERRED_SYMBOL_LOADW64 STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
CheckSum		dd ?
TimeDateStamp		dd ?
FileName		WCHAR MAX_PATH + 1 dup(?)
Reparse			BOOLEAN ?
hFile			HANDLE ?
Flags			dd ?
IMAGEHLP_DEFERRED_SYMBOL_LOADW64 ENDS
PIMAGEHLP_DEFERRED_SYMBOL_LOADW64 typedef ptr IMAGEHLP_DEFERRED_SYMBOL_LOADW64

DSLFLAG_MISMATCHED_PDB	equ 0x1
DSLFLAG_MISMATCHED_DBG	equ 0x2

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
IMAGEHLP_DEFERRED_SYMBOL_LOAD equ IMAGEHLP_DEFERRED_SYMBOL_LOAD64
PIMAGEHLP_DEFERRED_SYMBOL_LOAD equ PIMAGEHLP_DEFERRED_SYMBOL_LOAD64
else
IMAGEHLP_DEFERRED_SYMBOL_LOAD STRUC
SizeOfStruct		dd ?
BaseOfImage		dd ?
CheckSum		dd ?
TimeDateStamp		dd ?
FileName		CHAR MAX_PATH dup(?)
Reparse			BOOLEAN ?
hFile			HANDLE ?
IMAGEHLP_DEFERRED_SYMBOL_LOAD ENDS
PIMAGEHLP_DEFERRED_SYMBOL_LOAD typedef ptr IMAGEHLP_DEFERRED_SYMBOL_LOAD
endif

IMAGEHLP_DUPLICATE_SYMBOL64 STRUC
SizeOfStruct		dd ?
NumberOfDups		dd ?
Symbol			PIMAGEHLP_SYMBOL64 ?
SelectedSymbol		dd ?
IMAGEHLP_DUPLICATE_SYMBOL64 ENDS
PIMAGEHLP_DUPLICATE_SYMBOL64 typedef ptr IMAGEHLP_DUPLICATE_SYMBOL64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
IMAGEHLP_DUPLICATE_SYMBOL equ IMAGEHLP_DUPLICATE_SYMBOL64
PIMAGEHLP_DUPLICATE_SYMBOL equ PIMAGEHLP_DUPLICATE_SYMBOL64
else
IMAGEHLP_DUPLICATE_SYMBOL STRUC
SizeOfStruct		dd ?
NumberOfDups		dd ?
Symbol			PIMAGEHLP_SYMBOL ?
SelectedSymbol		dd ?
IMAGEHLP_DUPLICATE_SYMBOL ENDS
PIMAGEHLP_DUPLICATE_SYMBOL typedef ptr IMAGEHLP_DUPLICATE_SYMBOL
endif

;IMAGEAPI

;BOOL
SymSetParentWindow proto WINAPI \
		  hwnd: HWND

;PCHAR
SymSetHomeDirectory proto WINAPI \
	      hProcess: HANDLE,
		   dir: PSTR

;PWSTR
SymSetHomeDirectoryW proto WINAPI \
	      hProcess: HANDLE,
		   dir: PCWSTR

;PCHAR
SymGetHomeDirectory proto WINAPI \
		  type: DWORD,
		   dir: PSTR,
		  size: size_t

;PWSTR
SymGetHomeDirectoryW proto WINAPI \
		  type: DWORD,
		   dir: PWSTR,
		  size: size_t

hdBase			equ 0
hdSym			equ 1
hdSrc			equ 2
hdMax			equ 3

OMAP			STRUC
rva			ULONG ?
rvaTo			ULONG ?
OMAP			ENDS
POMAP			typedef ptr OMAP

;BOOL
SymGetOmaps proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: DWORD64,
		OmapTo: ptr POMAP,
	       cOmapTo: PDWORD64,
	      OmapFrom: ptr POMAP,
	     cOmapFrom: PDWORD64


SYMOPT_CASE_INSENSITIVE equ 0x00000001
SYMOPT_UNDNAME		equ 0x00000002
SYMOPT_DEFERRED_LOADS	equ 0x00000004
SYMOPT_NO_CPP		equ 0x00000008
SYMOPT_LOAD_LINES	equ 0x00000010
SYMOPT_OMAP_FIND_NEAREST equ 0x00000020
SYMOPT_LOAD_ANYTHING	equ 0x00000040
SYMOPT_IGNORE_CVREC	equ 0x00000080
SYMOPT_NO_UNQUALIFIED_LOADS equ 0x00000100
SYMOPT_FAIL_CRITICAL_ERRORS equ 0x00000200
SYMOPT_EXACT_SYMBOLS	equ 0x00000400
SYMOPT_ALLOW_ABSOLUTE_SYMBOLS equ 0x00000800
SYMOPT_IGNORE_NT_SYMPATH equ 0x00001000
SYMOPT_INCLUDE_32BIT_MODULES equ 0x00002000
SYMOPT_PUBLICS_ONLY	equ 0x00004000
SYMOPT_NO_PUBLICS	equ 0x00008000
SYMOPT_AUTO_PUBLICS	equ 0x00010000
SYMOPT_NO_IMAGE_SEARCH	equ 0x00020000
SYMOPT_SECURE		equ 0x00040000
SYMOPT_NO_PROMPTS	equ 0x00080000
SYMOPT_OVERWRITE	equ 0x00100000
SYMOPT_IGNORE_IMAGEDIR	equ 0x00200000
SYMOPT_FLAT_DIRECTORY	equ 0x00400000
SYMOPT_FAVOR_COMPRESSED equ 0x00800000
SYMOPT_ALLOW_ZERO_ADDRESS equ 0x01000000
SYMOPT_DISABLE_SYMSRV_AUTODETECT equ 0x02000000

SYMOPT_DEBUG		equ 0x80000000

;DWORD
SymSetOptions proto WINAPI \
	    SymOptions: DWORD


;DWORD
SymGetOptions proto WINAPI

;BOOL
SymCleanup proto WINAPI \
	      hProcess: HANDLE


;BOOL
SymMatchString proto WINAPI \
		string: PCSTR,
	    expression: PCSTR,
		 fCase: BOOL

;BOOL
SymMatchStringA proto WINAPI \
		string: PCSTR,
	    expression: PCSTR,
		 fCase: BOOL

;BOOL
SymMatchStringW proto WINAPI \
		string: PCWSTR,
	    expression: PCWSTR,
		 fCase: BOOL


CALLBACK(PSYM_ENUMSOURCEFILES_CALLBACK, :PSOURCEFILE, :PVOID)

PSYM_ENUMSOURCFILES_CALLBACK equ PSYM_ENUMSOURCEFILES_CALLBACK

;BOOL
SymEnumSourceFiles proto WINAPI \
	      hProcess: HANDLE,
	       ModBase: ULONG64,
		  Mask: PCSTR,
	    cbSrcFiles: PSYM_ENUMSOURCEFILES_CALLBACK,
	   UserContext: PVOID


CALLBACK(PSYM_ENUMSOURCEFILES_CALLBACKW, :PSOURCEFILEW, :PVOID)

;BOOL
SymEnumSourceFilesW proto WINAPI \
	      hProcess: HANDLE,
	       ModBase: ULONG64,
		  Mask: PCWSTR,
	    cbSrcFiles: PSYM_ENUMSOURCEFILES_CALLBACKW,
	   UserContext: PVOID


;BOOL
SymEnumerateModules64 proto WINAPI \
	      hProcess: HANDLE,
   EnumModulesCallback: PSYM_ENUMMODULES_CALLBACK64,
	   UserContext: PVOID


;BOOL
SymEnumerateModulesW64 proto WINAPI \
	      hProcess: HANDLE,
   EnumModulesCallback: PSYM_ENUMMODULES_CALLBACKW64,
	   UserContext: PVOID


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymEnumerateModules	equ <SymEnumerateModules64>
else
;BOOL
SymEnumerateModules proto WINAPI \
	      hProcess: HANDLE,
   EnumModulesCallback: PSYM_ENUMMODULES_CALLBACK,
	   UserContext: PVOID

endif

;BOOL
EnumerateLoadedModulesEx proto WINAPI \
	      hProcess: HANDLE,
EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACK64,
	   UserContext: PVOID


;BOOL
EnumerateLoadedModulesExW proto WINAPI \
	      hProcess: HANDLE,
EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACKW64,
	   UserContext: PVOID


;BOOL
EnumerateLoadedModules64 proto WINAPI \
	      hProcess: HANDLE,
EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACK64,
	   UserContext: PVOID


;BOOL
EnumerateLoadedModulesW64 proto WINAPI \
	      hProcess: HANDLE,
EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACKW64,
	   UserContext: PVOID


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
EnumerateLoadedModules	equ <EnumerateLoadedModules64>
else
;BOOL
EnumerateLoadedModules proto WINAPI \
	      hProcess: HANDLE,
EnumLoadedModulesCallback: PENUMLOADED_MODULES_CALLBACK,
	   UserContext: PVOID

endif

;PVOID
SymFunctionTableAccess64 proto WINAPI \
	      hProcess: HANDLE,
	      AddrBase: DWORD64


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymFunctionTableAccess	equ <SymFunctionTableAccess64>
else
;PVOID
SymFunctionTableAccess proto WINAPI \
	      hProcess: HANDLE,
	      AddrBase: DWORD
endif

;BOOL
SymGetUnwindInfo proto WINAPI \
	      hProcess: HANDLE,
	       Address: DWORD64,
		Buffer: PVOID,
		  Size: PULONG

;BOOL
SymGetModuleInfo64 proto WINAPI \
	      hProcess: HANDLE,
		qwAddr: DWORD64,
	    ModuleInfo: PIMAGEHLP_MODULE64

;BOOL
SymGetModuleInfoW64 proto WINAPI \
	      hProcess: HANDLE,
		qwAddr: DWORD64,
	    ModuleInfo: PIMAGEHLP_MODULEW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetModuleInfo	equ <SymGetModuleInfo64>
SymGetModuleInfoW	equ <SymGetModuleInfoW64>
else
;BOOL
SymGetModuleInfo proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD,
	    ModuleInfo: PIMAGEHLP_MODULE

;BOOL
SymGetModuleInfoW proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD,
	    ModuleInfo: PIMAGEHLP_MODULEW

endif

;DWORD64
SymGetModuleBase64 proto WINAPI \
	      hProcess: HANDLE,
		qwAddr: DWORD64


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetModuleBase	equ <SymGetModuleBase64>
else
;DWORD
SymGetModuleBase proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD

endif

SRCCODEINFO		STRUC
SizeOfStruct		dd ?
Key			PVOID ?
ModBase			dd ?
Obj			CHAR MAX_PATH + 1 dup(?)
FileName		CHAR MAX_PATH + 1 dup(?)
LineNumber		dd ?
Address			dd ?
SRCCODEINFO		ENDS
PSRCCODEINFO		typedef ptr SRCCODEINFO

SRCCODEINFOW		STRUC
SizeOfStruct		dd ?
Key			PVOID ?
ModBase			dd ?
Obj			WCHAR MAX_PATH + 1 dup(?)
FileName		WCHAR MAX_PATH + 1 dup(?)
LineNumber		dd ?
Address			dd ?
SRCCODEINFOW		ENDS
PSRCCODEINFOW		typedef ptr SRCCODEINFOW

CALLBACK(PSYM_ENUMLINES_CALLBACK, :PSRCCODEINFO, :PVOID)

;BOOL
SymEnumLines proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
		   Obj: PCSTR,
		  File: PCSTR,
     EnumLinesCallback: PSYM_ENUMLINES_CALLBACK,
	   UserContext: PVOID


CALLBACK(PSYM_ENUMLINES_CALLBACKW, :PSRCCODEINFOW, :PVOID)

;BOOL
SymEnumLinesW proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
		   Obj: PCWSTR,
		  File: PCWSTR,
     EnumLinesCallback: PSYM_ENUMLINES_CALLBACKW,
	   UserContext: PVOID

;BOOL
SymGetLineFromAddr64 proto WINAPI \
	      hProcess: HANDLE,
		qwAddr: DWORD64,
       pdwDisplacement: PDWORD,
		Line64: PIMAGEHLP_LINE64

;BOOL
SymGetLineFromAddrW64 proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD64,
       pdwDisplacement: PDWORD,
		  Line: PIMAGEHLP_LINEW64

;BOOL
SymEnumSourceLines proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
		   Obj: PCSTR,
		  File: PCSTR,
		  Line: DWORD,
		 Flags: DWORD,
     EnumLinesCallback: PSYM_ENUMLINES_CALLBACK,
	   UserContext: PVOID

;BOOL
SymEnumSourceLinesW proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
		   Obj: PCWSTR,
		  File: PCWSTR,
		  Line: DWORD,
		 Flags: DWORD,
     EnumLinesCallback: PSYM_ENUMLINES_CALLBACKW,
	   UserContext: PVOID


ESLFLAG_FULLPATH	equ 0x1
ESLFLAG_NEAREST		equ 0x2
ESLFLAG_PREV		equ 0x4
ESLFLAG_NEXT		equ 0x8

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetLineFromAddr	equ <SymGetLineFromAddr64>
SymGetLineFromAddrW	equ <SymGetLineFromAddrW64>
else
;BOOL
SymGetLineFromAddr proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD,
       pdwDisplacement: PDWORD,
		  Line: PIMAGEHLP_LINE

;BOOL
SymGetLineFromAddrW proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD,
       pdwDisplacement: PDWORD,
		  Line: PIMAGEHLP_LINEW

endif

;BOOL
SymGetLineFromName64 proto WINAPI \
	      hProcess: HANDLE,
	    ModuleName: PCSTR,
	      FileName: PCSTR,
	  dwLineNumber: DWORD,
	plDisplacement: PLONG,
		  Line: PIMAGEHLP_LINE64

;BOOL
SymGetLineFromNameW64 proto WINAPI \
	      hProcess: HANDLE,
	    ModuleName: PCWSTR,
	      FileName: PCWSTR,
	  dwLineNumber: DWORD,
	plDisplacement: PLONG,
		  Line: PIMAGEHLP_LINEW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetLineFromName	equ <SymGetLineFromName64>
else
;BOOL
SymGetLineFromName proto WINAPI \
	      hProcess: HANDLE,
	    ModuleName: PCSTR,
	      FileName: PCSTR,
	  dwLineNumber: DWORD,
	plDisplacement: PLONG,
		  Line: PIMAGEHLP_LINE

endif

;BOOL
SymGetLineNext64 proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINE64

;BOOL
SymGetLineNextW64 proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINEW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetLineNext		equ <SymGetLineNext64>
else
;BOOL
SymGetLineNext proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINE

;BOOL
SymGetLineNextW proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINEW
endif

;BOOL
SymGetLinePrev64 proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINE64

;BOOL
SymGetLinePrevW64 proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINEW64


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetLinePrev		equ <SymGetLinePrev64>
else
;BOOL
SymGetLinePrev proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINE

;BOOL
SymGetLinePrevW proto WINAPI \
	      hProcess: HANDLE,
		  Line: PIMAGEHLP_LINEW
endif

;ULONG
SymGetFileLineOffsets64 proto WINAPI \
	      hProcess: HANDLE,
	    ModuleName: PCSTR,
	      FileName: PCSTR,
		Buffer: PDWORD64,
	   BufferLines: ULONG

;BOOL
SymMatchFileName proto WINAPI \
	      FileName: PCSTR,
		 Match: PCSTR,
	  FileNameStop: ptr PSTR,
	     MatchStop: ptr PSTR

;BOOL
SymMatchFileNameW proto WINAPI \
	      FileName: PCWSTR,
		 Match: PCWSTR,
	  FileNameStop: ptr PWSTR,
	     MatchStop: ptr PWSTR

;BOOL
SymGetSourceFile proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
		Params: PCSTR,
	      FileSpec: PCSTR,
	      FilePath: PSTR,
		  Size: DWORD

;BOOL
SymGetSourceFileW proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
		Params: PCWSTR,
	      FileSpec: PCWSTR,
	      FilePath: PWSTR,
		  Size: DWORD

;BOOL
SymGetSourceFileToken proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
	      FileSpec: PCSTR,
		 Token: ptr PVOID,
		  Size: ptr DWORD

;BOOL
SymGetSourceFileTokenW proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
	      FileSpec: PCWSTR,
		 Token: ptr PVOID,
		  Size: ptr DWORD

;BOOL
SymGetSourceFileFromToken proto WINAPI \
	      hProcess: HANDLE,
		 Token: PVOID,
		Params: PCSTR,
	      FilePath: PSTR,
		  Size: DWORD

;BOOL
SymGetSourceFileFromTokenW proto WINAPI \
	      hProcess: HANDLE,
		 Token: PVOID,
		Params: PCWSTR,
	      FilePath: PWSTR,
		  Size: DWORD

;BOOL
SymGetSourceVarFromToken proto WINAPI \
	      hProcess: HANDLE,
		 Token: PVOID,
		Params: PCSTR,
	       VarName: PCSTR,
		 Value: PSTR,
		  Size: DWORD

;BOOL
SymGetSourceVarFromTokenW proto WINAPI \
	      hProcess: HANDLE,
		 Token: PVOID,
		Params: PCWSTR,
	       VarName: PCWSTR,
		 Value: PWSTR,
		  Size: DWORD

CALLBACK(PENUMSOURCEFILETOKENSCALLBACK, :PVOID, :size_t)

;BOOL
SymEnumSourceFileTokens proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
	      Callback: PENUMSOURCEFILETOKENSCALLBACK


;BOOL
SymInitialize proto WINAPI \
	      hProcess: HANDLE,
	UserSearchPath: PCSTR,
	fInvadeProcess: BOOL

;BOOL
SymInitializeW proto WINAPI \
	      hProcess: HANDLE,
	UserSearchPath: PCWSTR,
	fInvadeProcess: BOOL

;BOOL
SymGetSearchPath proto WINAPI \
	      hProcess: HANDLE,
	    SearchPath: PSTR,
      SearchPathLength: DWORD

;BOOL
SymGetSearchPathW proto WINAPI \
	      hProcess: HANDLE,
	    SearchPath: PWSTR,
      SearchPathLength: DWORD

;BOOL
SymSetSearchPath proto WINAPI \
	      hProcess: HANDLE,
	    SearchPath: PCSTR

;BOOL
SymSetSearchPathW proto WINAPI \
	      hProcess: HANDLE,
	    SearchPath: PCWSTR


SLMFLAG_VIRTUAL		equ 0x1
SLMFLAG_ALT_INDEX	equ 0x2
SLMFLAG_NO_SYMBOLS	equ 0x4

;DWORD64
SymLoadModuleEx proto WINAPI \
	      hProcess: HANDLE,
		 hFile: HANDLE,
	     ImageName: PCSTR,
	    ModuleName: PCSTR,
	     BaseOfDll: DWORD64,
	       DllSize: DWORD,
		  Data: PMODLOAD_DATA,
		 Flags: DWORD

;DWORD64
SymLoadModuleExW proto WINAPI \
	      hProcess: HANDLE,
		 hFile: HANDLE,
	     ImageName: PCWSTR,
	    ModuleName: PCWSTR,
	     BaseOfDll: DWORD64,
	       DllSize: DWORD,
		  Data: PMODLOAD_DATA,
		 Flags: DWORD

;BOOL
SymUnloadModule64 proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: DWORD64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymUnloadModule		equ <SymUnloadModule64>
else
;BOOL
SymUnloadModule proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: DWORD
endif

;BOOL
SymUnDName64 proto WINAPI \
		   sym: PIMAGEHLP_SYMBOL64,
	     UnDecName: PSTR,
       UnDecNameLength: DWORD

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymUnDName		equ <SymUnDName64>
else
;BOOL
SymUnDName proto WINAPI \
		   sym: PIMAGEHLP_SYMBOL,
	     UnDecName: PSTR,
       UnDecNameLength: DWORD

endif

;BOOL
SymRegisterCallback64 proto WINAPI \
	      hProcess: HANDLE,
      CallbackFunction: PSYMBOL_REGISTERED_CALLBACK64,
	   UserContext: ULONG64

;BOOL
SymRegisterCallbackW64 proto WINAPI \
	      hProcess: HANDLE,
      CallbackFunction: PSYMBOL_REGISTERED_CALLBACK64,
	   UserContext: ULONG64

;BOOL
SymRegisterFunctionEntryCallback64 proto WINAPI \
	      hProcess: HANDLE,
      CallbackFunction: PSYMBOL_FUNCENTRY_CALLBACK64,
	   UserContext: ULONG64


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymRegisterCallback	equ <SymRegisterCallback64>
SymRegisterFunctionEntryCallback equ <SymRegisterFunctionEntryCallback64>
else
;BOOL
SymRegisterCallback proto WINAPI \
	      hProcess: HANDLE,
      CallbackFunction: PSYMBOL_REGISTERED_CALLBACK,
	   UserContext: PVOID

;BOOL
SymRegisterFunctionEntryCallback proto WINAPI \
	      hProcess: HANDLE,
      CallbackFunction: PSYMBOL_FUNCENTRY_CALLBACK,
	   UserContext: PVOID
endif


IMAGEHLP_SYMBOL_SRC	STRUC
sizeofstruct		dd ?
type			dd ?
file			CHAR MAX_PATH dup(?)
IMAGEHLP_SYMBOL_SRC	ENDS
PIMAGEHLP_SYMBOL_SRC	typedef ptr IMAGEHLP_SYMBOL_SRC

MODULE_TYPE_INFO	STRUC
dataLength		USHORT ?
leaf			USHORT ?
data			db 1 dup(?)
MODULE_TYPE_INFO	ENDS
PMODULE_TYPE_INFO	typedef ptr MODULE_TYPE_INFO

SYMBOL_INFO		STRUC
SizeOfStruct		ULONG ?
TypeIndex		ULONG ?
Reserved		ULONG64 2 dup(?)
Index			ULONG ?
Size			ULONG ?
ModBase			ULONG64 ?
Flags			ULONG ?
Value			ULONG64 ?
Address			ULONG64 ?
Register		ULONG ?
Scope			ULONG ?
Tag			ULONG ?
NameLen			ULONG ?
MaxNameLen		ULONG ?
Name			CHAR 1 dup(?)
SYMBOL_INFO		ENDS
PSYMBOL_INFO		typedef ptr SYMBOL_INFO

SYMBOL_INFO_PACKAGE	STRUC
_si			SYMBOL_INFO <>
name			CHAR MAX_SYM_NAME + 1 dup(?)
SYMBOL_INFO_PACKAGE	ENDS
PSYMBOL_INFO_PACKAGE	typedef ptr SYMBOL_INFO_PACKAGE

SYMBOL_INFOW		STRUC
SizeOfStruct		ULONG ?
TypeIndex		ULONG ?
Reserved		ULONG64 2 dup(?)
Index			ULONG ?
Size			ULONG ?
ModBase			ULONG64 ?
Flags			ULONG ?
Value			ULONG64 ?
Address			ULONG64 ?
Register		ULONG ?
Scope			ULONG ?
Tag			ULONG ?
NameLen			ULONG ?
MaxNameLen		ULONG ?
Name			WCHAR 1 dup(?)
SYMBOL_INFOW		ENDS
PSYMBOL_INFOW		typedef ptr SYMBOL_INFOW

SYMBOL_INFO_PACKAGEW	STRUC
_si			SYMBOL_INFOW <>
name			WCHAR MAX_SYM_NAME + 1 dup(?)
SYMBOL_INFO_PACKAGEW	ENDS
PSYMBOL_INFO_PACKAGEW	typedef ptr SYMBOL_INFO_PACKAGEW

IMAGEHLP_STACK_FRAME	STRUC
InstructionOffset	ULONG64 ?
ReturnOffset		ULONG64 ?
FrameOffset		ULONG64 ?
StackOffset		ULONG64 ?
BackingStoreOffset	ULONG64 ?
FuncTableEntry		ULONG64 ?
Params			ULONG64 4 dup(?)
Reserved		ULONG64 5 dup(?)
Virtual			BOOL ?
Reserved2		ULONG ?
IMAGEHLP_STACK_FRAME	ENDS
PIMAGEHLP_STACK_FRAME	typedef ptr IMAGEHLP_STACK_FRAME


IMAGEHLP_CONTEXT	typedef ;VOID
PIMAGEHLP_CONTEXT	typedef ptr IMAGEHLP_CONTEXT

;BOOL
SymSetContext proto WINAPI \
	      hProcess: HANDLE,
	    StackFrame: PIMAGEHLP_STACK_FRAME,
	       Context: PIMAGEHLP_CONTEXT

;BOOL
SymSetScopeFromAddr proto WINAPI \
	      hProcess: HANDLE,
	       Address: ULONG64

;BOOL
SymSetScopeFromIndex proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD

CALLBACK(PSYM_ENUMPROCESSES_CALLBACK, :HANDLE, :PVOID)

;BOOL
SymEnumProcesses proto WINAPI \
 EnumProcessesCallback: PSYM_ENUMPROCESSES_CALLBACK,
	   UserContext: PVOID

;BOOL
SymFromAddr proto WINAPI \
	      hProcess: HANDLE,
	       Address: DWORD64,
	  Displacement: PDWORD64,
		Symbol: PSYMBOL_INFO

;BOOL
SymFromAddrW proto WINAPI \
	      hProcess: HANDLE,
	       Address: DWORD64,
	  Displacement: PDWORD64,
		Symbol: PSYMBOL_INFOW

;BOOL
SymFromToken proto WINAPI \
	      hProcess: HANDLE,
		  Base: DWORD64,
		 Token: DWORD,
		Symbol: PSYMBOL_INFO

;BOOL
SymFromTokenW proto WINAPI \
	      hProcess: HANDLE,
		  Base: DWORD64,
		 Token: DWORD,
		Symbol: PSYMBOL_INFOW

;BOOL
SymNext proto WINAPI \
	      hProcess: HANDLE,
		   _si: PSYMBOL_INFO

;BOOL
SymNextW proto WINAPI \
	      hProcess: HANDLE,
		   siw: PSYMBOL_INFOW

;BOOL
SymPrev proto WINAPI \
	      hProcess: HANDLE,
		   _si: PSYMBOL_INFO

;BOOL
SymPrevW proto WINAPI \
	      hProcess: HANDLE,
		   siw: PSYMBOL_INFOW

;BOOL
SymFromName proto WINAPI \
	      hProcess: HANDLE,
		  Name: PCSTR,
		Symbol: PSYMBOL_INFO

;BOOL
SymFromNameW proto WINAPI \
	      hProcess: HANDLE,
		  Name: PCWSTR,
		Symbol: PSYMBOL_INFOW


CALLBACK(PSYM_ENUMERATESYMBOLS_CALLBACK, :PSYMBOL_INFO, :ULONG, :PVOID)

;BOOL
SymEnumSymbols proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Mask: PCSTR,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK,
	   UserContext: PVOID


CALLBACK(PSYM_ENUMERATESYMBOLS_CALLBACKW, :PSYMBOL_INFOW, :ULONG, :PVOID)

;BOOL
SymEnumSymbolsW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Mask: PCWSTR,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACKW,
	   UserContext: PVOID

;BOOL
SymEnumSymbolsForAddr proto WINAPI \
	      hProcess: HANDLE,
	       Address: DWORD64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK,
	   UserContext: PVOID

;BOOL
SymEnumSymbolsForAddrW proto WINAPI \
	      hProcess: HANDLE,
	       Address: DWORD64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACKW,
	   UserContext: PVOID


SYMSEARCH_MASKOBJS	equ 0x01
SYMSEARCH_RECURSE	equ 0X02
SYMSEARCH_GLOBALSONLY	equ 0X04
SYMSEARCH_ALLITEMS	equ 0X08

;BOOL
SymSearch proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD,
		SymTag: DWORD,
		  Mask: PCSTR,
	       Address: DWORD64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK,
	   UserContext: PVOID,
	       Options: DWORD

;BOOL
SymSearchW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD,
		SymTag: DWORD,
		  Mask: PCWSTR,
	       Address: DWORD64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACKW,
	   UserContext: PVOID,
	       Options: DWORD

;BOOL
SymGetScope proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD,
		Symbol: PSYMBOL_INFO

;BOOL
SymGetScopeW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD,
		Symbol: PSYMBOL_INFOW

;BOOL
SymFromIndex proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD,
		Symbol: PSYMBOL_INFO

;BOOL
SymFromIndexW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		 Index: DWORD,
		Symbol: PSYMBOL_INFOW

IMAGEHLP_SYMBOL_TYPE_INFO typedef SDWORD
PIMAGEHLP_SYMBOL_TYPE_INFO typedef ptr IMAGEHLP_SYMBOL_TYPE_INFO

TI_GET_SYMTAG		equ 0
TI_GET_SYMNAME		equ 1
TI_GET_LENGTH		equ 2
TI_GET_TYPE		equ 3
TI_GET_TYPEID		equ 4
TI_GET_BASETYPE		equ 5
TI_GET_ARRAYINDEXTYPEID equ 6
TI_FINDCHILDREN		equ 7
TI_GET_DATAKIND		equ 8
TI_GET_ADDRESSOFFSET	equ 9
TI_GET_OFFSET		equ 10
TI_GET_VALUE		equ 11
TI_GET_COUNT		equ 12
TI_GET_CHILDRENCOUNT	equ 13
TI_GET_BITPOSITION	equ 14
TI_GET_VIRTUALBASECLASS equ 15
TI_GET_VIRTUALTABLESHAPEID equ 16
TI_GET_VIRTUALBASEPOINTEROFFSET equ 17
TI_GET_CLASSPARENTID	equ 18
TI_GET_NESTED		equ 19
TI_GET_SYMINDEX		equ 20
TI_GET_LEXICALPARENT	equ 21
TI_GET_ADDRESS		equ 22
TI_GET_THISADJUST	equ 23
TI_GET_UDTKIND		equ 24
TI_IS_EQUIV_TO		equ 25
TI_GET_CALLING_CONVENTION equ 26
TI_IS_CLOSE_EQUIV_TO	equ 27
TI_GTIEX_REQS_VALID	equ 28
TI_GET_VIRTUALBASEOFFSET equ 29
TI_GET_VIRTUALBASEDISPINDEX equ 30
TI_GET_IS_REFERENCE	equ 31
TI_GET_INDIRECTVIRTUALBASECLASS equ 32
IMAGEHLP_SYMBOL_TYPE_INFO_MAX equ 33

TI_FINDCHILDREN_PARAMS	STRUC
Count			ULONG ?
Start			ULONG ?
ChildId			ULONG 1 dup(?)
TI_FINDCHILDREN_PARAMS	ENDS

;BOOL
SymGetTypeInfo proto WINAPI \
	      hProcess: HANDLE,
	       ModBase: DWORD64,
		TypeId: ULONG,
	       GetType: IMAGEHLP_SYMBOL_TYPE_INFO,
		 pInfo: PVOID

IMAGEHLP_GET_TYPE_INFO_UNCACHED equ 0x00000001
IMAGEHLP_GET_TYPE_INFO_CHILDREN equ 0x00000002

IMAGEHLP_GET_TYPE_INFO_PARAMS STRUC
SizeOfStruct		ULONG ?
Flags			ULONG ?
NumIds			ULONG ?
TypeIds			PULONG ?
TagFilter		ULONG64 ?
NumReqs			ULONG ?
ReqKinds		PIMAGEHLP_SYMBOL_TYPE_INFO ?
ReqOffsets		PULONG_PTR ?
ReqSizes		PULONG ?
ReqStride		ULONG_PTR ?
BufferSize		ULONG_PTR ?
Buffer			PVOID ?
EntriesMatched		ULONG ?
EntriesFilled		ULONG ?
TagsFound		ULONG64 ?
AllReqsValid		ULONG64 ?
NumReqsValid		ULONG ?
ReqsValid		PULONG64 ?
IMAGEHLP_GET_TYPE_INFO_PARAMS ENDS
PIMAGEHLP_GET_TYPE_INFO_PARAMS typedef ptr IMAGEHLP_GET_TYPE_INFO_PARAMS

;BOOL
SymGetTypeInfoEx proto WINAPI \
	      hProcess: HANDLE,
	       ModBase: DWORD64,
		Params: PIMAGEHLP_GET_TYPE_INFO_PARAMS


;BOOL
SymEnumTypes proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK,
	   UserContext: PVOID

;BOOL
SymEnumTypesW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACKW,
	   UserContext: PVOID

;BOOL
SymEnumTypesByName proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  mask: PCSTR,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK,
	   UserContext: PVOID

;BOOL
SymEnumTypesByNameW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  mask: PCWSTR,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACKW,
	   UserContext: PVOID

;BOOL
SymGetTypeFromName proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Name: PCSTR,
		Symbol: PSYMBOL_INFO

;BOOL
SymGetTypeFromNameW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Name: PCWSTR,
		Symbol: PSYMBOL_INFOW

;BOOL
SymAddSymbol proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Name: PCSTR,
	       Address: DWORD64,
		  Size: DWORD,
		 Flags: DWORD

;BOOL
SymAddSymbolW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Name: PCWSTR,
	       Address: DWORD64,
		  Size: DWORD,
		 Flags: DWORD

;BOOL
SymDeleteSymbol proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Name: PCSTR,
	       Address: DWORD64,
		 Flags: DWORD

;BOOL
SymDeleteSymbolW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
		  Name: PCWSTR,
	       Address: DWORD64,
		 Flags: DWORD

;BOOL
SymRefreshModuleList proto WINAPI \
	      hProcess: HANDLE

;BOOL
SymAddSourceStream proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
	    StreamFile: PCSTR,
		Buffer: PBYTE,
		  Size: size_t

CALLBACK(SYMADDSOURCESTREAM, :HANDLE, :ULONG64, :PCSTR, :PBYTE, :size_t)

;BOOL
SymAddSourceStreamA proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
	    StreamFile: PCSTR,
		Buffer: PBYTE,
		  Size: size_t

CALLBACK(SYMADDSOURCESTREAMA, :HANDLE, :ULONG64, :PCSTR, :PBYTE, :size_t)

;BOOL
SymAddSourceStreamW proto WINAPI \
	      hProcess: HANDLE,
		  Base: ULONG64,
	      FileSpec: PCWSTR,
		Buffer: PBYTE,
		  Size: size_t

;BOOL
SymSrvIsStoreW proto WINAPI \
	      hProcess: HANDLE,
		  path: PCWSTR

;BOOL
SymSrvIsStore proto WINAPI \
	      hProcess: HANDLE,
		  path: PCSTR

;PCSTR
SymSrvDeltaName proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCSTR,
		  Type: PCSTR,
		 File1: PCSTR,
		 File2: PCSTR

;PCWSTR
SymSrvDeltaNameW proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCWSTR,
		  Type: PCWSTR,
		 File1: PCWSTR,
		 File2: PCWSTR

;PCSTR
SymSrvGetSupplement proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCSTR,
		  Node: PCSTR,
		  File: PCSTR

;PCWSTR
SymSrvGetSupplementW proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCWSTR,
		  Node: PCWSTR,
		  File: PCWSTR

;BOOL
SymSrvGetFileIndexes proto WINAPI \
		  File: PCSTR,
		    Id: ptr GUID,
		  Val1: PDWORD,
		  Val2: PDWORD,
		 Flags: DWORD

;BOOL
SymSrvGetFileIndexesW proto WINAPI \
		  File: PCWSTR,
		    Id: ptr GUID,
		  Val1: PDWORD,
		  Val2: PDWORD,
		 Flags: DWORD

;BOOL
SymSrvGetFileIndexStringW proto WINAPI \
	      hProcess: HANDLE,
	       SrvPath: PCWSTR,
		  File: PCWSTR,
		 Index: PWSTR,
		  Size: size_t,
		 Flags: DWORD

;BOOL
SymSrvGetFileIndexString proto WINAPI \
	      hProcess: HANDLE,
	       SrvPath: PCSTR,
		  File: PCSTR,
		 Index: PSTR,
		  Size: size_t,
		 Flags: DWORD

SYMSRV_INDEX_INFO	STRUC
sizeofstruct		dd ?
file			CHAR MAX_PATH +1 dup(?)
stripped		BOOL ?
timestamp		dd ?
size			dd ?
dbgfile			CHAR MAX_PATH +1 dup(?)
pdbfile			CHAR MAX_PATH + 1 dup(?)
guid			GUID <>
sig			dd ?
age			dd ?
SYMSRV_INDEX_INFO	ENDS
PSYMSRV_INDEX_INFO	typedef ptr SYMSRV_INDEX_INFO

SYMSRV_INDEX_INFOW	STRUC
sizeofstruct		dd ?
file			WCHAR MAX_PATH +1 dup(?)
stripped		BOOL ?
timestamp		dd ?
size			dd ?
dbgfile			WCHAR MAX_PATH +1 dup(?)
pdbfile			WCHAR MAX_PATH + 1 dup(?)
guid			GUID <>
sig			dd ?
age			dd ?
SYMSRV_INDEX_INFOW	ENDS
PSYMSRV_INDEX_INFOW	typedef ptr SYMSRV_INDEX_INFOW

;BOOL
SymSrvGetFileIndexInfo proto WINAPI \
		  File: PCSTR,
		  Info: PSYMSRV_INDEX_INFO,
		 Flags: DWORD

;BOOL
SymSrvGetFileIndexInfoW proto WINAPI \
		  File: PCWSTR,
		  Info: PSYMSRV_INDEX_INFOW,
		 Flags: DWORD

;PCSTR
SymSrvStoreSupplement proto WINAPI \
	      hProcess: HANDLE,
	       SrvPath: PCSTR,
		  Node: PCSTR,
		  File: PCSTR,
		 Flags: DWORD

;PCWSTR
SymSrvStoreSupplementW proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCWSTR,
		  Node: PCWSTR,
		  File: PCWSTR,
		 Flags: DWORD

;PCSTR
SymSrvStoreFile proto WINAPI \
	      hProcess: HANDLE,
	       SrvPath: PCSTR,
		  File: PCSTR,
		 Flags: DWORD

;PCWSTR
SymSrvStoreFileW proto WINAPI \
	      hProcess: HANDLE,
	       SrvPath: PCWSTR,
		  File: PCWSTR,
		 Flags: DWORD


sfImage			equ 0
sfDbg			equ 1
sfPdb			equ 2
sfMpd			equ 3
sfMax			equ 4

;BOOL
SymGetSymbolFile proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCSTR,
	     ImageFile: PCSTR,
		  Type: DWORD,
	    SymbolFile: PSTR,
	   cSymbolFile: size_t,
	       DbgFile: PSTR,
	      cDbgFile: size_t

;BOOL
SymGetSymbolFileW proto WINAPI \
	      hProcess: HANDLE,
	       SymPath: PCWSTR,
	     ImageFile: PCWSTR,
		  Type: DWORD,
	    SymbolFile: PWSTR,
	   cSymbolFile: size_t,
	       DbgFile: PWSTR,
	      cDbgFile: size_t

CALLBACK(PDBGHELP_CREATE_USER_DUMP_CALLBACK, :DWORD, :PVOID, :LPDWORD, :PVOID)

;BOOL
DbgHelpCreateUserDump proto WINAPI \
	      FileName: LPCSTR,
	      Callback: PDBGHELP_CREATE_USER_DUMP_CALLBACK,
	      UserData: PVOID

;BOOL
DbgHelpCreateUserDumpW proto WINAPI \
	      FileName: LPCWSTR,
	      Callback: PDBGHELP_CREATE_USER_DUMP_CALLBACK,
	      UserData: PVOID

;BOOL
SymGetSymFromAddr64 proto WINAPI \
	      hProcess: HANDLE,
		qwAddr: DWORD64,
       pdwDisplacement: PDWORD64,
		Symbol: PIMAGEHLP_SYMBOL64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetSymFromAddr	equ <SymGetSymFromAddr64>
else
;BOOL
SymGetSymFromAddr proto WINAPI \
	      hProcess: HANDLE,
		dwAddr: DWORD,
       pdwDisplacement: PDWORD,
		Symbol: PIMAGEHLP_SYMBOL

endif

;BOOL
SymGetSymFromName64 proto WINAPI \
	      hProcess: HANDLE,
		  Name: PCSTR,
		Symbol: PIMAGEHLP_SYMBOL64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetSymFromName	equ <SymGetSymFromName64>
else
;BOOL
SymGetSymFromName proto WINAPI \
	      hProcess: HANDLE,
		  Name: PCSTR,
		Symbol: PIMAGEHLP_SYMBOL

endif



CALLBACK(PSYMBOLSERVERPROC, :PCSTR, :PCSTR, :PVOID, :DWORD, :DWORD, :PSTR)
CALLBACK(PSYMBOLSERVERPROCA, :PCSTR, :PCSTR, :PVOID, :DWORD, :DWORD, :PSTR)
CALLBACK(PSYMBOLSERVERPROCW, :PCWSTR, :PCWSTR, :PVOID, :DWORD, :DWORD, :PWSTR)
CALLBACK(PSYMBOLSERVERBYINDEXPROC, :PCSTR, :PCSTR, :PCSTR, :PSTR)
CALLBACK(PSYMBOLSERVERBYINDEXPROCA, :PCSTR, :PCSTR, :PCSTR, :PSTR)
CALLBACK(PSYMBOLSERVERBYINDEXPROCW, :PCWSTR, :PCWSTR, :PCWSTR, :PWSTR)
CALLBACK(PSYMBOLSERVEROPENPROC)
CALLBACK(PSYMBOLSERVERCLOSEPROC)
CALLBACK(PSYMBOLSERVERSETOPTIONSPROC, :UINT_PTR, :ULONG64)
CALLBACK(PSYMBOLSERVERSETOPTIONSWPROC, :UINT_PTR, :ULONG64)
CALLBACK(PSYMBOLSERVERCALLBACKPROC, :UINT_PTR, :ULONG64, :ULONG64)
CALLBACK(PSYMBOLSERVERGETOPTIONSPROC)
CALLBACK(PSYMBOLSERVERPINGPROC, :PCSTR)
CALLBACK(PSYMBOLSERVERPINGPROCA, :PCSTR)
CALLBACK(PSYMBOLSERVERPINGPROCW, :PCWSTR)
CALLBACK(PSYMBOLSERVERGETVERSION, :LPAPI_VERSION)
CALLBACK(PSYMBOLSERVERDELTANAME, :PCSTR, :PVOID, :DWORD, :DWORD, :PVOID, :DWORD, :DWORD, :PSTR, :size_t)
CALLBACK(PSYMBOLSERVERDELTANAMEW, :PCWSTR, :PVOID, :DWORD, :DWORD, :PVOID, :DWORD, :DWORD, :PWSTR, :size_t)
CALLBACK(PSYMBOLSERVERGETSUPPLEMENT, :PCSTR, :PCSTR, :PCSTR, :PSTR, :size_t)
CALLBACK(PSYMBOLSERVERGETSUPPLEMENTW, :PCWSTR, :PCWSTR, :PCWSTR, :PWSTR, :size_t)
CALLBACK(PSYMBOLSERVERSTORESUPPLEMENT, :PCSTR, :PCSTR, :PCSTR, :PSTR, :size_t, :DWORD)
CALLBACK(PSYMBOLSERVERSTORESUPPLEMENTW, :PCWSTR, :PCWSTR, :PCWSTR, :PWSTR, :size_t, :DWORD)
CALLBACK(PSYMBOLSERVERGETINDEXSTRING, :PVOID, :DWORD, :DWORD, :PSTR, :size_t)
CALLBACK(PSYMBOLSERVERGETINDEXSTRINGW, :PVOID, :DWORD, :DWORD, :PWSTR, :size_t)
CALLBACK(PSYMBOLSERVERSTOREFILE, :PCSTR, :PCSTR, :PVOID, :DWORD, :DWORD, :PSTR, :size_t, :DWORD)
CALLBACK(PSYMBOLSERVERSTOREFILEW, :PCWSTR, :PCWSTR, :PVOID, :DWORD, :DWORD, :PWSTR, :size_t, :DWORD)
CALLBACK(PSYMBOLSERVERISSTORE, :PCSTR)
CALLBACK(PSYMBOLSERVERISSTOREW, :PCWSTR)
CALLBACK(PSYMBOLSERVERVERSION)
CALLBACK(PSYMBOLSERVERMESSAGEPROC, :UINT_PTR, :ULONG64, :ULONG64)

SYMSRV_VERSION		equ 2

SSRVOPT_CALLBACK	equ 0x00000001
SSRVOPT_DWORD		equ 0x00000002
SSRVOPT_DWORDPTR	equ 0x00000004
SSRVOPT_GUIDPTR		equ 0x00000008
SSRVOPT_OLDGUIDPTR	equ 0x00000010
SSRVOPT_UNATTENDED	equ 0x00000020
SSRVOPT_NOCOPY		equ 0x00000040
SSRVOPT_GETPATH		equ 0x00000040
SSRVOPT_PARENTWIN	equ 0x00000080
SSRVOPT_PARAMTYPE	equ 0x00000100
SSRVOPT_SECURE		equ 0x00000200
SSRVOPT_TRACE		equ 0x00000400
SSRVOPT_SETCONTEXT	equ 0x00000800
SSRVOPT_PROXY		equ 0x00001000
SSRVOPT_DOWNSTREAM_STORE equ 0x00002000
SSRVOPT_OVERWRITE	equ 0x00004000
SSRVOPT_RESETTOU	equ 0x00008000
SSRVOPT_CALLBACKW	equ 0x00010000
SSRVOPT_FLAT_DEFAULT_STORE equ 0x00020000
SSRVOPT_PROXYW		equ 0x00040000
SSRVOPT_MESSAGE		equ 0x00080000
SSRVOPT_SERVICE		equ 0x00100000
SSRVOPT_FAVOR_COMPRESSED equ 0x00200000
SSRVOPT_STRING		equ 0x00400000
SSRVOPT_WINHTTP		equ 0x00800000
SSRVOPT_WININET		equ 0x01000000

SSRVOPT_MAX		equ 0x0100000

SSRVOPT_RESET		equ (-1)


NUM_SSRVOPTS		equ 30

SSRVACTION_TRACE	equ 1
SSRVACTION_QUERYCANCEL	equ 2
SSRVACTION_EVENT	equ 3
SSRVACTION_EVENTW	equ 4
SSRVACTION_SIZE		equ 5

SYMSTOREOPT_COMPRESS	equ 0x01
SYMSTOREOPT_OVERWRITE	equ 0x02
SYMSTOREOPT_RETURNINDEX equ 0x04
SYMSTOREOPT_POINTER	equ 0x08
SYMSTOREOPT_ALT_INDEX	equ 0x10
SYMSTOREOPT_UNICODE	equ 0x20
SYMSTOREOPT_PASS_IF_EXISTS equ 0x40

ifdef DBGHELP_TRANSLATE_TCHAR
SymInitialize		equ <SymInitializeW>
SymAddSymbol		equ <SymAddSymbolW>
SymDeleteSymbol		equ <SymDeleteSymbolW>
SearchTreeForFile	equ <SearchTreeForFileW>
UnDecorateSymbolName	equ <UnDecorateSymbolNameW>
SymGetLineFromName64	equ <SymGetLineFromNameW64>
SymGetLineFromAddr64	equ <SymGetLineFromAddrW64>
SymGetLineNext64	equ <SymGetLineNextW64>
SymGetLinePrev64	equ <SymGetLinePrevW64>
SymFromName		equ <SymFromNameW>
SymFindExecutableImage	equ <SymFindExecutableImageW>
FindExecutableImageEx	equ <FindExecutableImageExW>
SymSearch		equ <SymSearchW>
SymEnumLines		equ <SymEnumLinesW>
SymEnumSourceLines	equ <SymEnumSourceLinesW>
SymGetTypeFromName	equ <SymGetTypeFromNameW>
SymEnumSymbolsForAddr	equ <SymEnumSymbolsForAddrW>
SymFromAddr		equ <SymFromAddrW>
SymMatchString		equ <SymMatchStringW>
SymEnumSourceFiles	equ <SymEnumSourceFilesW>
SymEnumSymbols		equ <SymEnumSymbolsW>
SymLoadModuleEx		equ <SymLoadModuleExW>
SymSetSearchPath	equ <SymSetSearchPathW>
SymGetSearchPath	equ <SymGetSearchPathW>
EnumDirTree		equ <EnumDirTreeW>
SymFromToken		equ <SymFromTokenW>
SymFromIndex		equ <SymFromIndexW>
SymGetScope		equ <SymGetScopeW>
SymNext			equ <SymNextW>
SymPrev			equ <SymPrevW>
SymEnumTypes		equ <SymEnumTypesW>
SymEnumTypesByName	equ <SymEnumTypesByNameW>
SymRegisterCallback64	equ <SymRegisterCallbackW64>
SymFindDebugInfoFile	equ <SymFindDebugInfoFileW>
FindDebugInfoFileEx	equ <FindDebugInfoFileExW>
SymFindFileInPath	equ <SymFindFileInPathW>
SymEnumerateModules64	equ <SymEnumerateModulesW64>
SymSetHomeDirectory	equ <SymSetHomeDirectoryW>
SymGetHomeDirectory	equ <SymGetHomeDirectoryW>
SymGetSourceFile	equ <SymGetSourceFileW>
SymGetSourceFileToken	equ <SymGetSourceFileTokenW>
SymGetSourceFileFromToken equ <SymGetSourceFileFromTokenW>
SymGetSourceVarFromToken equ <SymGetSourceVarFromTokenW>
SymGetSourceFileToken	equ <SymGetSourceFileTokenW>
SymGetFileLineOffsets64 equ <SymGetFileLineOffsetsW64>
SymFindFileInPath	equ <SymFindFileInPathW>
SymMatchFileName	equ <SymMatchFileNameW>
SymGetSourceFileFromToken equ <SymGetSourceFileFromTokenW>
SymGetSourceVarFromToken equ <SymGetSourceVarFromTokenW>
SymGetModuleInfo64	equ <SymGetModuleInfoW64>
SymSrvIsStore		equ <SymSrvIsStoreW>
SymSrvDeltaName		equ <SymSrvDeltaNameW>
SymSrvGetSupplement	equ <SymSrvGetSupplementW>
SymSrvStoreSupplement	equ <SymSrvStoreSupplementW>
SymSrvGetFileIndexes	equ <SymSrvGetFileIndexes>
SymSrvGetFileIndexString equ <SymSrvGetFileIndexStringW>
SymSrvStoreFile		equ <SymSrvStoreFileW>
SymGetSymbolFile	equ <SymGetSymbolFileW>
EnumerateLoadedModules64 equ <EnumerateLoadedModulesW64>
EnumerateLoadedModulesEx equ <EnumerateLoadedModulesExW>
SymSrvGetFileIndexInfo	equ <SymSrvGetFileIndexInfoW>

IMAGEHLP_LINE64		equ IMAGEHLP_LINEW64
PIMAGEHLP_LINE64	equ PIMAGEHLP_LINEW64
SYMBOL_INFO		equ <SYMBOL_INFOW>
PSYMBOL_INFO		equ <PSYMBOL_INFOW>
SYMBOL_INFO_PACKAGE	equ <SYMBOL_INFO_PACKAGEW>
PSYMBOL_INFO_PACKAGE	equ <PSYMBOL_INFO_PACKAGEW>
FIND_EXE_FILE_CALLBACK	equ <FIND_EXE_FILE_CALLBACKW>
PFIND_EXE_FILE_CALLBACK equ <PFIND_EXE_FILE_CALLBACKW>
SYM_ENUMERATESYMBOLS_CALLBACK equ <SYM_ENUMERATESYMBOLS_CALLBACKW>
PSYM_ENUMERATESYMBOLS_CALLBACK equ <PSYM_ENUMERATESYMBOLS_CALLBACKW>
SRCCODEINFO		equ <SRCCODEINFOW>
PSRCCODEINFO		equ <PSRCCODEINFOW>
SOURCEFILE		equ <SOURCEFILEW>
PSOURCEFILE		equ <PSOURCEFILEW>
SYM_ENUMSOURECFILES_CALLBACK equ <SYM_ENUMSOURCEFILES_CALLBACKW>
PSYM_ENUMSOURCEFILES_CALLBACK equ <PSYM_ENUMSOURECFILES_CALLBACKW>
IMAGEHLP_CBA_EVENT	equ <IMAGEHLP_CBA_EVENTW>
PIMAGEHLP_CBA_EVENT	equ <PIMAGEHLP_CBA_EVENTW>
PENUMDIRTREE_CALLBACK	equ <PENUMDIRTREE_CALLBACKW>
IMAGEHLP_DEFERRED_SYMBOL_LOAD64 equ IMAGEHLP_DEFERRED_SYMBOL_LOADW64
PIMAGEHLP_DEFERRED_SYMBOL_LOAD64 equ PIMAGEHLP_DEFERRED_SYMBOL_LOADW64
PFIND_DEBUG_FILE_CALLBACK equ <PFIND_DEBUG_FILE_CALLBACKW>
PFINDFILEINPATHCALLBACK equ <PFINDFILEINPATHCALLBACKW>
IMAGEHLP_MODULE64	equ IMAGEHLP_MODULEW64
PIMAGEHLP_MODULE64	equ PIMAGEHLP_MODULEW64
SYMSRV_INDEX_INFO	equ <SYMSRV_INDEX_INFOW>
PSYMSRV_INDEX_INFO	equ <PSYMSRV_INDEX_INFOW>

PSYMBOLSERVERPROC	equ <PSYMBOLSERVERPROCW>
PSYMBOLSERVERPINGPROC	equ <PSYMBOLSERVERPINGPROCW>
endif

;DBHLP_DEPRECIATED
;BOOL
FindFileInPath proto WINAPI \
	      hprocess: HANDLE,
	    SearchPath: PCSTR,
	      FileName: PCSTR,
		    id: PVOID,
		   two: DWORD,
		 three: DWORD,
		 flags: DWORD,
	      FilePath: PSTR

;DBHLP_DEPRECIATED
;BOOL
FindFileInSearchPath proto WINAPI \
	      hprocess: HANDLE,
	    SearchPath: PCSTR,
	      FileName: PCSTR,
		   one: DWORD,
		   two: DWORD,
		 three: DWORD,
	      FilePath: PSTR

;DBHLP_DEPRECIATED
;BOOL
SymEnumSym proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
   EnumSymbolsCallback: PSYM_ENUMERATESYMBOLS_CALLBACK,
	   UserContext: PVOID

;DBHLP_DEPRECIATED
;BOOL
SymEnumerateSymbols64 proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
   EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACK64,
	   UserContext: PVOID

;DBHLP_DEPRECIATED
;BOOL
SymEnumerateSymbolsW64 proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG64,
   EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACK64W,
	   UserContext: PVOID

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymEnumerateSymbols	equ <SymEnumerateSymbols64>
SymEnumerateSymbolsW	equ <SymEnumerateSymbolsW64>
else
;DBHLP_DEPRECIATED
;BOOL
SymEnumerateSymbols proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG,
   EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACK,
	   UserContext: PVOID
;DBHLP_DEPRECIATED
;BOOL
SymEnumerateSymbolsW proto WINAPI \
	      hProcess: HANDLE,
	     BaseOfDll: ULONG,
   EnumSymbolsCallback: PSYM_ENUMSYMBOLS_CALLBACKW,
	   UserContext: PVOID

endif

;DWORD64
SymLoadModule64 proto WINAPI \
	      hProcess: HANDLE,
		 hFile: HANDLE,
	     ImageName: PCSTR,
	    ModuleName: PCSTR,
	     BaseOfDll: DWORD64,
	     SizeOfDll: DWORD


if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymLoadModule		equ <SymLoadModule64>
else
;DWORD
SymLoadModule proto WINAPI \
	      hProcess: HANDLE,
		 hFile: HANDLE,
	     ImageName: PCSTR,
	    ModuleName: PCSTR,
	     BaseOfDll: DWORD,
	     SizeOfDll: DWORD

endif

;BOOL
SymGetSymNext64 proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOL64

;BOOL
SymGetSymNextW64 proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOLW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetSymNext		equ <SymGetSymNext64>
SymGetSymNextW		equ <SymGetSymNextW64>
else
;BOOL
SymGetSymNext proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOL

;BOOL
SymGetSymNextW proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOLW

endif

;BOOL
SymGetSymPrev64 proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOL64

;BOOL
SymGetSymPrevW64 proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOLW64

if NOT defined(_IMAGEHLP_SOURCE_) AND defined(_IMAGEHLP64)
SymGetSymPrev		equ <SymGetSymPrev64>
SymGetSymPrevW		equ <SymGetSymPrevW64>
else
;BOOL
SymGetSymPrev proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOL

;BOOL
SymGetSymPrevW proto WINAPI \
	      hProcess: HANDLE,
		Symbol: PIMAGEHLP_SYMBOLW

endif

SYMF_OMAP_GENERATED	equ 0x00000001
SYMF_OMAP_MODIFIED	equ 0x00000002
SYMF_REGISTER		equ 0x00000008
SYMF_REGREL		equ 0x00000010
SYMF_FRAMEREL		equ 0x00000020
SYMF_PARAMETER		equ 0x00000040
SYMF_LOCAL		equ 0x00000080
SYMF_CONSTANT		equ 0x00000100
SYMF_EXPORT		equ 0x00000200
SYMF_FORWARDER		equ 0x00000400
SYMF_FUNCTION		equ 0x00000800
SYMF_VIRTUAL		equ 0x00001000
SYMF_THUNK		equ 0x00002000
SYMF_TLSREL		equ 0x00004000


IMAGEHLP_SYMBOL_INFO_VALUEPRESENT equ 1
IMAGEHLP_SYMBOL_INFO_REGISTER equ SYMF_REGISTER
IMAGEHLP_SYMBOL_INFO_REGRELATIVE equ SYMF_REGRE
IMAGEHLP_SYMBOL_INFO_FRAMERELATIVE equ SYMF_FRAMERE
IMAGEHLP_SYMBOL_INFO_PARAMETER equ SYMF_PARAMETER
IMAGEHLP_SYMBOL_INFO_LOCAL equ SYMF_LOCA
IMAGEHLP_SYMBOL_INFO_CONSTANT equ SYMF_CONSTANT
IMAGEHLP_SYMBOL_FUNCTION equ SYMF_FUNCTION
IMAGEHLP_SYMBOL_VIRTUAL equ SYMF_VIRTUA
IMAGEHLP_SYMBOL_THUNK	equ SYMF_THUNK
IMAGEHLP_SYMBOL_INFO_TLSRELATIVE equ SYMF_TLSRE

.pragma pack(pop)
.pragma pack(push, 4)

MINIDUMP_SIGNATURE	equ ('PMDM')
MINIDUMP_VERSION	equ (42899)
RVA			typedef DWORD
RVA64			typedef ULONG64

MINIDUMP_LOCATION_DESCRIPTOR STRUC
DataSize		ULONG32 ?
Rva			RVA ?
MINIDUMP_LOCATION_DESCRIPTOR ENDS

MINIDUMP_LOCATION_DESCRIPTOR64	STRUC
DataSize		ULONG64 ?
Rva			RVA64 ?
MINIDUMP_LOCATION_DESCRIPTOR64 ENDS

MINIDUMP_MEMORY_DESCRIPTOR STRUC
StartOfMemoryRange	ULONG64 ?
Memory			MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_MEMORY_DESCRIPTOR ENDS
PMINIDUMP_MEMORY_DESCRIPTOR typedef ptr MINIDUMP_MEMORY_DESCRIPTOR

MINIDUMP_MEMORY_DESCRIPTOR64 STRUC
StartOfMemoryRange	ULONG64 ?
DataSize		ULONG64 ?
MINIDUMP_MEMORY_DESCRIPTOR64 ENDS
PMINIDUMP_MEMORY_DESCRIPTOR64 typedef ptr MINIDUMP_MEMORY_DESCRIPTOR64

MINIDUMP_HEADER		STRUC
Signature		ULONG32 ?
Version			ULONG32 ?
NumberOfStreams		ULONG32 ?
StreamDirectoryRva	RVA ?
CheckSum		ULONG32 ?
UNION
 Reserved		ULONG32 ?
 TimeDateStamp		ULONG32 ?
ENDS
Flags			ULONG64 ?
MINIDUMP_HEADER		ENDS
PMINIDUMP_HEADER	typedef ptr MINIDUMP_HEADER

MINIDUMP_DIRECTORY	STRUC
StreamType		ULONG32 ?
Location		MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_DIRECTORY	ENDS
PMINIDUMP_DIRECTORY	typedef ptr MINIDUMP_DIRECTORY

MINIDUMP_STRING		STRUC
Length			ULONG32 ?
Buffer			WCHAR 0 dup(?)
MINIDUMP_STRING		ENDS
PMINIDUMP_STRING	typedef ptr MINIDUMP_STRING

MINIDUMP_STREAM_TYPE	typedef SDWORD
UnusedStream		equ 0
ReservedStream0		equ 1
ReservedStream1		equ 2
ThreadListStream	equ 3
ModuleListStream	equ 4
MemoryListStream	equ 5
ExceptionStream		equ 6
SystemInfoStream	equ 7
ThreadExListStream	equ 8
Memory64ListStream	equ 9
CommentStreamA		equ 10
CommentStreamW		equ 11
HandleDataStream	equ 12
FunctionTableStream	equ 13
UnloadedModuleListStream equ 14
MiscInfoStream		equ 15
MemoryInfoListStream	equ 16
ThreadInfoListStream	equ 17
HandleOperationListStream equ 18
TokenStream		equ 19
ceStreamNull		equ 0x8000
ceStreamSystemInfo	equ 0x8001
ceStreamException	equ 0x8002
ceStreamModuleList	equ 0x8003
ceStreamProcessList	equ 0x8004
ceStreamThreadList	equ 0x8005
ceStreamThreadContextList equ 0x8006
ceStreamThreadCallStackList equ 0x8007
ceStreamMemoryVirtualList equ 0x8008
ceStreamMemoryPhysicalList equ 0x8009
ceStreamBucketParameters equ 0x800A
ceStreamProcessModuleMap equ 0x800B
ceStreamDiagnosisList	equ 0x800C
LastReservedStream	equ 0xffff

CPU_INFORMATION		UNION
STRUC X86CpuInfo
 VendorId		ULONG32 3 dup(?)
 VersionInformation	ULONG32 ?
 FeatureInformation	ULONG32 ?
 AMDExtendedCpuFeatures ULONG32 ?
ENDS
STRUC OtherCpuInfo
 ProcessorFeatures	ULONG64	 2  dup(?)
ENDS
CPU_INFORMATION		ENDS
PCPU_INFORMATION	typedef ptr CPU_INFORMATION

MINIDUMP_SYSTEM_INFO	STRUC
ProcessorArchitecture	USHORT ?
ProcessorLevel		USHORT ?
ProcessorRevision	USHORT ?
UNION
 Reserved0		USHORT ?
 STRUC
  NumberOfProcessors	UCHAR ?
  ProductType		UCHAR ?
 ENDS
ENDS
MajorVersion		ULONG32 ?
MinorVersion		ULONG32 ?
BuildNumber		ULONG32 ?
PlatformId		ULONG32 ?
CSDVersionRva		RVA ?
UNION
 Reserved1		ULONG32 ?
 STRUC
  SuiteMask		USHORT ?
  Reserved2		USHORT ?
 ENDS
ENDS
Cpu			CPU_INFORMATION <>
MINIDUMP_SYSTEM_INFO	ENDS
PMINIDUMP_SYSTEM_INFO	typedef ptr MINIDUMP_SYSTEM_INFO

C_ASSERT (sizeof ( ((PPROCESS_INFORMATION).dwThreadId ) == 4);

MINIDUMP_THREAD		STRUC
ThreadId		ULONG32 ?
SuspendCount		ULONG32 ?
PriorityClass		ULONG32 ?
Priority		ULONG32 ?
Teb			ULONG64 ?
Stack			MINIDUMP_MEMORY_DESCRIPTOR <>
ThreadContext		MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_THREAD		ENDS
PMINIDUMP_THREAD	typedef ptr MINIDUMP_THREAD

MINIDUMP_THREAD_LIST	STRUC
NumberOfThreads		ULONG32 ?
Threads			MINIDUMP_THREAD 0 dup(?)
MINIDUMP_THREAD_LIST	ENDS
PMINIDUMP_THREAD_LIST	typedef ptr MINIDUMP_THREAD_LIST

MINIDUMP_THREAD_EX	STRUC
ThreadId		ULONG32 ?
SuspendCount		ULONG32 ?
PriorityClass		ULONG32 ?
Priority		ULONG32 ?
Teb			ULONG64 ?
Stack			MINIDUMP_MEMORY_DESCRIPTOR <>
ThreadContext		MINIDUMP_LOCATION_DESCRIPTOR <>
BackingStore		MINIDUMP_MEMORY_DESCRIPTOR <>
MINIDUMP_THREAD_EX	ENDS
PMINIDUMP_THREAD_EX	typedef ptr MINIDUMP_THREAD_EX

MINIDUMP_THREAD_EX_LIST	 STRUC
NumberOfThreads		ULONG32 ?
Threads			MINIDUMP_THREAD_EX 0 dup(?)
MINIDUMP_THREAD_EX_LIST ENDS
PMINIDUMP_THREAD_EX_LIST typedef ptr MINIDUMP_THREAD_EX_LIST

MINIDUMP_EXCEPTION	STRUC
ExceptionCode		ULONG32 ?
ExceptionFlags		ULONG32 ?
ExceptionRecord		ULONG64 ?
ExceptionAddress	ULONG64 ?
NumberParameters	ULONG32 ?
__unusedAlignment	ULONG32 ?
ExceptionInformation	ULONG64	 EXCEPTION_MAXIMUM_PARAMETERS  dup(?)
MINIDUMP_EXCEPTION	ENDS
PMINIDUMP_EXCEPTION	typedef ptr MINIDUMP_EXCEPTION

MINIDUMP_EXCEPTION_STREAM STRUC
ThreadId		ULONG32 ?
__alignment		ULONG32 ?
ExceptionRecord		MINIDUMP_EXCEPTION <>
ThreadContext		MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_EXCEPTION_STREAM ENDS
PMINIDUMP_EXCEPTION_STREAM typedef ptr MINIDUMP_EXCEPTION_STREAM

MINIDUMP_MODULE		STRUC
BaseOfImage		ULONG64 ?
SizeOfImage		ULONG32 ?
CheckSum		ULONG32 ?
TimeDateStamp		ULONG32 ?
ModuleNameRva		RVA ?
VersionInfo		VS_FIXEDFILEINFO <>
CvRecord		MINIDUMP_LOCATION_DESCRIPTOR <>
MiscRecord		MINIDUMP_LOCATION_DESCRIPTOR <>
Reserved0		ULONG64 ?
Reserved1		ULONG64 ?
MINIDUMP_MODULE		ENDS
PMINIDUMP_MODULE	typedef ptr MINIDUMP_MODULE

MINIDUMP_MODULE_LIST	STRUC
NumberOfModules		ULONG32 ?
Modules			MINIDUMP_MODULE	 0  dup(?)
MINIDUMP_MODULE_LIST	ENDS
PMINIDUMP_MODULE_LIST	typedef ptr MINIDUMP_MODULE_LIST

MINIDUMP_MEMORY_LIST	STRUC
NumberOfMemoryRanges	ULONG32 ?
MemoryRanges		MINIDUMP_MEMORY_DESCRIPTOR 0 dup(?)
MINIDUMP_MEMORY_LIST	ENDS
PMINIDUMP_MEMORY_LIST	typedef ptr MINIDUMP_MEMORY_LIST

MINIDUMP_MEMORY64_LIST	STRUC
NumberOfMemoryRanges	ULONG64 ?
BaseRva			RVA64 ?
MemoryRanges		MINIDUMP_MEMORY_DESCRIPTOR64 0 dup(?)
MINIDUMP_MEMORY64_LIST	ENDS
PMINIDUMP_MEMORY64_LIST typedef ptr MINIDUMP_MEMORY64_LIST

MINIDUMP_EXCEPTION_INFORMATION	STRUC
ThreadId		dd ?
ExceptionPointers	PEXCEPTION_POINTERS ?
ClientPointers		BOOL ?
MINIDUMP_EXCEPTION_INFORMATION ENDS
PMINIDUMP_EXCEPTION_INFORMATION typedef ptr MINIDUMP_EXCEPTION_INFORMATION

MINIDUMP_EXCEPTION_INFORMATION64 STRUC
ThreadId		dd ?
ExceptionRecord		ULONG64 ?
ContextRecord		ULONG64 ?
ClientPointers		BOOL ?
MINIDUMP_EXCEPTION_INFORMATION64 ENDS
PMINIDUMP_EXCEPTION_INFORMATION64 typedef ptr MINIDUMP_EXCEPTION_INFORMATION64

MINIDUMP_HANDLE_OBJECT_INFORMATION_TYPE typedef SDWORD
MiniHandleObjectInformationNone equ 0
MiniThreadInformation1	equ 1
MiniMutantInformation1	equ 2
MiniMutantInformation2	equ 3
MiniProcessInformation1 equ 4
MiniProcessInformation2 equ 5
MiniHandleObjectInformationTypeMax equ 6

MINIDUMP_HANDLE_OBJECT_INFORMATION STRUC
NextInfoRva		RVA ?
InfoType		ULONG32 ?
SizeOfInfo		ULONG32 ?
MINIDUMP_HANDLE_OBJECT_INFORMATION ENDS

MINIDUMP_HANDLE_DESCRIPTOR STRUC
Handle			ULONG64 ?
TypeNameRva		RVA ?
ObjectNameRva		RVA ?
Attributes		ULONG32 ?
GrantedAccess		ULONG32 ?
HandleCount		ULONG32 ?
PointerCount		ULONG32 ?
MINIDUMP_HANDLE_DESCRIPTOR ENDS
PMINIDUMP_HANDLE_DESCRIPTOR typedef ptr MINIDUMP_HANDLE_DESCRIPTOR

MINIDUMP_HANDLE_DESCRIPTOR_2 STRUC
Handle			ULONG64 ?
TypeNameRva		RVA ?
ObjectNameRva		RVA ?
Attributes		ULONG32 ?
GrantedAccess		ULONG32 ?
HandleCount		ULONG32 ?
PointerCount		ULONG32 ?
ObjectInfoRva		RVA ?
Reserved0		ULONG32 ?
MINIDUMP_HANDLE_DESCRIPTOR_2 ENDS
PMINIDUMP_HANDLE_DESCRIPTOR_2 typedef ptr MINIDUMP_HANDLE_DESCRIPTOR_2

MINIDUMP_HANDLE_DESCRIPTOR_N typedef MINIDUMP_HANDLE_DESCRIPTOR_2
PMINIDUMP_HANDLE_DESCRIPTOR_N typedef ptr MINIDUMP_HANDLE_DESCRIPTOR_N

MINIDUMP_HANDLE_DATA_STREAM STRUC
SizeOfHeader		ULONG32 ?
SizeOfDescriptor	ULONG32 ?
NumberOfDescriptors	ULONG32 ?
Reserved		ULONG32 ?
MINIDUMP_HANDLE_DATA_STREAM ENDS
PMINIDUMP_HANDLE_DATA_STREAM typedef ptr MINIDUMP_HANDLE_DATA_STREAM

MINIDUMP_HANDLE_OPERATION_LIST STRUC
SizeOfHeader		ULONG32 ?
SizeOfEntry		ULONG32 ?
NumberOfEntries		ULONG32 ?
Reserved		ULONG32 ?
MINIDUMP_HANDLE_OPERATION_LIST ENDS
PMINIDUMP_HANDLE_OPERATION_LIST typedef ptr MINIDUMP_HANDLE_OPERATION_LIST

MINIDUMP_FUNCTION_TABLE_DESCRIPTOR STRUC
MinimumAddress		ULONG64 ?
MaximumAddress		ULONG64 ?
BaseAddress		ULONG64 ?
EntryCount		ULONG32 ?
SizeOfAlignPad		ULONG32 ?
MINIDUMP_FUNCTION_TABLE_DESCRIPTOR ENDS
PMINIDUMP_FUNCTION_TABLE_DESCRIPTOR typedef ptr MINIDUMP_FUNCTION_TABLE_DESCRIPTOR

MINIDUMP_FUNCTION_TABLE_STREAM STRUC
SizeOfHeader		ULONG32 ?
SizeOfDescriptor	ULONG32 ?
SizeOfNativeDescriptor	ULONG32 ?
SizeOfFunctionEntry	ULONG32 ?
NumberOfDescriptors	ULONG32 ?
SizeOfAlignPad		ULONG32 ?
MINIDUMP_FUNCTION_TABLE_STREAM ENDS
PMINIDUMP_FUNCTION_TABLE_STREAM typedef ptr MINIDUMP_FUNCTION_TABLE_STREAM

MINIDUMP_UNLOADED_MODULE STRUC
BaseOfImage		ULONG64 ?
SizeOfImage		ULONG32 ?
CheckSum		ULONG32 ?
TimeDateStamp		ULONG32 ?
ModuleNameRva		RVA ?
MINIDUMP_UNLOADED_MODULE ENDS
PMINIDUMP_UNLOADED_MODULE typedef ptr MINIDUMP_UNLOADED_MODULE

MINIDUMP_UNLOADED_MODULE_LIST STRUC
SizeOfHeader		ULONG32 ?
SizeOfEntry		ULONG32 ?
NumberOfEntries		ULONG32 ?
MINIDUMP_UNLOADED_MODULE_LIST ENDS
PMINIDUMP_UNLOADED_MODULE_LIST typedef ptr MINIDUMP_UNLOADED_MODULE_LIST

MINIDUMP_MISC1_PROCESS_ID equ 0x00000001
MINIDUMP_MISC1_PROCESS_TIMES equ 0x00000002
MINIDUMP_MISC1_PROCESSOR_POWER_INFO equ 0x00000004
MINIDUMP_MISC3_PROCESS_INTEGRITY equ 0x00000010
MINIDUMP_MISC3_PROCESS_EXECUTE_FLAGS equ 0x00000020
MINIDUMP_MISC3_TIMEZONE equ 0x00000040
MINIDUMP_MISC3_PROTECTED_PROCESS equ 0x00000080

MINIDUMP_MISC_INFO	STRUC
SizeOfInfo		ULONG32 ?
Flags1			ULONG32 ?
ProcessId		ULONG32 ?
ProcessCreateTime	ULONG32 ?
ProcessUserTime		ULONG32 ?
ProcessKernelTime	ULONG32 ?
MINIDUMP_MISC_INFO	ENDS
PMINIDUMP_MISC_INFO	typedef ptr MINIDUMP_MISC_INFO

MINIDUMP_MISC_INFO_2	STRUC
SizeOfInfo		ULONG32 ?
Flags1			ULONG32 ?
ProcessId		ULONG32 ?
ProcessCreateTime	ULONG32 ?
ProcessUserTime		ULONG32 ?
ProcessKernelTime	ULONG32 ?
ProcessorMaxMhz		ULONG32 ?
ProcessorCurrentMhz	ULONG32 ?
ProcessorMhzLimit	ULONG32 ?
ProcessorMaxIdleState	ULONG32 ?
ProcessorCurrentIdleState ULONG32 ?
MINIDUMP_MISC_INFO_2	ENDS
PMINIDUMP_MISC_INFO_2	typedef ptr MINIDUMP_MISC_INFO_2

MINIDUMP_MISC_INFO_3	STRUC
SizeOfInfo		ULONG32 ?
Flags1			ULONG32 ?
ProcessId		ULONG32 ?
ProcessCreateTime	ULONG32 ?
ProcessUserTime		ULONG32 ?
ProcessKernelTime	ULONG32 ?
ProcessorMaxMhz		ULONG32 ?
ProcessorCurrentMhz	ULONG32 ?
ProcessorMhzLimit	ULONG32 ?
ProcessorMaxIdleState	ULONG32 ?
ProcessorCurrentIdleState ULONG32 ?
ProcessIntegrityLevel	ULONG32 ?
ProcessExecuteFlags	ULONG32 ?
ProtectedProcess	ULONG32 ?
TimeZoneId		ULONG32 ?
TimeZone		TIME_ZONE_INFORMATION <>
MINIDUMP_MISC_INFO_3	ENDS
PMINIDUMP_MISC_INFO_3	typedef ptr MINIDUMP_MISC_INFO_3

MINIDUMP_MISC_INFO_N	typedef MINIDUMP_MISC_INFO_3
PMINIDUMP_MISC_INFO_N	typedef ptr MINIDUMP_MISC_INFO_N

MINIDUMP_MEMORY_INFO	STRUC
BaseAddress		ULONG64 ?
AllocationBase		ULONG64 ?
AllocationProtect	ULONG32 ?
__alignment1		ULONG32 ?
RegionSize		ULONG64 ?
State			ULONG32 ?
Protect			ULONG32 ?
Type			ULONG32 ?
__alignment2		ULONG32 ?
MINIDUMP_MEMORY_INFO	ENDS
PMINIDUMP_MEMORY_INFO	typedef ptr MINIDUMP_MEMORY_INFO

MINIDUMP_MEMORY_INFO_LIST STRUC
SizeOfHeader		ULONG ?
SizeOfEntry		ULONG ?
NumberOfEntries		ULONG64 ?
MINIDUMP_MEMORY_INFO_LIST ENDS
PMINIDUMP_MEMORY_INFO_LIST typedef ptr MINIDUMP_MEMORY_INFO_LIST

MINIDUMP_THREAD_INFO_ERROR_THREAD equ 0x00000001
MINIDUMP_THREAD_INFO_WRITING_THREAD equ 0x00000002
MINIDUMP_THREAD_INFO_EXITED_THREAD equ 0x00000004
MINIDUMP_THREAD_INFO_INVALID_INFO equ 0x00000008
MINIDUMP_THREAD_INFO_INVALID_CONTEXT equ 0x00000010
MINIDUMP_THREAD_INFO_INVALID_TEB equ 0x00000020

MINIDUMP_THREAD_INFO	STRUC
ThreadId		ULONG32 ?
DumpFlags		ULONG32 ?
DumpError		ULONG32 ?
ExitStatus		ULONG32 ?
CreateTime		ULONG64 ?
ExitTime		ULONG64 ?
KernelTime		ULONG64 ?
UserTime		ULONG64 ?
StartAddress		ULONG64 ?
Affinity		ULONG64 ?
MINIDUMP_THREAD_INFO	ENDS
PMINIDUMP_THREAD_INFO	typedef ptr MINIDUMP_THREAD_INFO

MINIDUMP_THREAD_INFO_LIST STRUC
SizeOfHeader		ULONG ?
SizeOfEntry		ULONG ?
NumberOfEntries		ULONG ?
MINIDUMP_THREAD_INFO_LIST ENDS
PMINIDUMP_THREAD_INFO_LIST typedef ptr MINIDUMP_THREAD_INFO_LIST

MINIDUMP_TOKEN_INFO_HEADER STRUC
TokenSize		ULONG ?
TokenId			ULONG ?
TokenHandle		ULONG64 ?
MINIDUMP_TOKEN_INFO_HEADER ENDS
PMINIDUMP_TOKEN_INFO_HEADER typedef ptr MINIDUMP_TOKEN_INFO_HEADER

MINIDUMP_TOKEN_INFO_LIST STRUC
TokenListSize		ULONG ?
TokenListEntries	ULONG ?
ListHeaderSize		ULONG ?
ElementHeaderSize	ULONG ?
MINIDUMP_TOKEN_INFO_LIST ENDS
PMINIDUMP_TOKEN_INFO_LIST typedef ptr MINIDUMP_TOKEN_INFO_LIST

MINIDUMP_USER_RECORD	STRUC
Type			ULONG32 ?
Memory			MINIDUMP_LOCATION_DESCRIPTOR <>
MINIDUMP_USER_RECORD	ENDS
PMINIDUMP_USER_RECORD	typedef ptr MINIDUMP_USER_RECORD

MINIDUMP_USER_STREAM	STRUC
Type			ULONG32 ?
BufferSize		ULONG ?
Buffer			PVOID ?

MINIDUMP_USER_STREAM	ENDS
PMINIDUMP_USER_STREAM	typedef ptr MINIDUMP_USER_STREAM

MINIDUMP_USER_STREAM_INFORMATION STRUC
UserStreamCount		ULONG ?
UserStreamArray		PMINIDUMP_USER_STREAM ?
MINIDUMP_USER_STREAM_INFORMATION ENDS
PMINIDUMP_USER_STREAM_INFORMATION typedef ptr MINIDUMP_USER_STREAM_INFORMATION

MINIDUMP_CALLBACK_TYPE	typedef SDWORD
ModuleCallback		equ 0
ThreadCallback		equ 1
ThreadExCallback	equ 2
IncludeThreadCallback	equ 3
IncludeModuleCallback	equ 4
MemoryCallback		equ 5
CancelCallback		equ 6
WriteKernelMinidumpCallback equ 7
KernelMinidumpStatusCallback equ 8
RemoveMemoryCallback	equ 9
IncludeVmRegionCallback equ 10
IoStartCallback		equ 11
IoWriteAllCallback	equ 12
IoFinishCallback	equ 13
ReadMemoryFailureCallback equ 14
SecondaryFlagsCallback	equ 15

MINIDUMP_THREAD_CALLBACK STRUC
ThreadId		ULONG ?
ThreadHandle		HANDLE ?
Context			CONTEXT <>
SizeOfContext		ULONG ?
StackBase		ULONG64 ?
StackEnd		ULONG64 ?
MINIDUMP_THREAD_CALLBACK ENDS
PMINIDUMP_THREAD_CALLBACK typedef ptr MINIDUMP_THREAD_CALLBACK

MINIDUMP_THREAD_EX_CALLBACK STRUC
ThreadId		ULONG ?
ThreadHandle		HANDLE ?
Context			CONTEXT <>
SizeOfContext		ULONG ?
StackBase		ULONG64 ?
StackEnd		ULONG64 ?
BackingStoreBase	ULONG64 ?
BackingStoreEnd		ULONG64 ?
MINIDUMP_THREAD_EX_CALLBACK ENDS
PMINIDUMP_THREAD_EX_CALLBACK typedef ptr MINIDUMP_THREAD_EX_CALLBACK

MINIDUMP_INCLUDE_THREAD_CALLBACK STRUC
ThreadId		ULONG ?
MINIDUMP_INCLUDE_THREAD_CALLBACK ENDS
PMINIDUMP_INCLUDE_THREAD_CALLBACK typedef ptr MINIDUMP_INCLUDE_THREAD_CALLBACK

THREAD_WRITE_FLAGS	typedef SDWORD
ThreadWriteThread	equ 0x0001
ThreadWriteStack	equ 0x0002
ThreadWriteContext	equ 0x0004
ThreadWriteBackingStore equ 0x0008
ThreadWriteInstructionWindow equ 0x0010
ThreadWriteThreadData	equ 0x0020
ThreadWriteThreadInfo	equ 0x0040

MINIDUMP_MODULE_CALLBACK STRUC
FullPath		PWCHAR ?
BaseOfImage		ULONG64 ?
SizeOfImage		ULONG ?
CheckSum		ULONG ?
TimeDateStamp		ULONG ?
VersionInfo		VS_FIXEDFILEINFO <>
CvRecord		PVOID ?
SizeOfCvRecord		ULONG ?
MiscRecord		PVOID ?
SizeOfMiscRecord	ULONG ?
MINIDUMP_MODULE_CALLBACK ENDS
PMINIDUMP_MODULE_CALLBACK typedef ptr MINIDUMP_MODULE_CALLBACK

MINIDUMP_INCLUDE_MODULE_CALLBACK STRUC
BaseOfImage		ULONG64 ?
MINIDUMP_INCLUDE_MODULE_CALLBACK ENDS
PMINIDUMP_INCLUDE_MODULE_CALLBACK typedef ptr MINIDUMP_INCLUDE_MODULE_CALLBACK

MODULE_WRITE_FLAGS	typedef SDWORD
ModuleWriteModule	equ 0x0001
ModuleWriteDataSeg	equ 0x0002
ModuleWriteMiscRecord	equ 0x0004
ModuleWriteCvRecord	equ 0x0008
ModuleReferencedByMemory equ 0x0010
ModuleWriteTlsData	equ 0x0020
ModuleWriteCodeSegs	equ 0x0040

MINIDUMP_IO_CALLBACK	STRUC
Handle			HANDLE ?
_Offset			ULONG64 ?
Buffer			PVOID ?
BufferBytes		ULONG ?
MINIDUMP_IO_CALLBACK	ENDS
PMINIDUMP_IO_CALLBACK	typedef ptr MINIDUMP_IO_CALLBACK

MINIDUMP_READ_MEMORY_FAILURE_CALLBACK STRUC
_Offset			ULONG64 ?
Bytes			ULONG ?
FailureStatus		HRESULT ?
MINIDUMP_READ_MEMORY_FAILURE_CALLBACK ENDS


MINIDUMP_CALLBACK_INPUT	 STRUC
ProcessId		ULONG ?
ProcessHandle		HANDLE ?
CallbackType		ULONG ?
UNION
 Status			HRESULT ?
 Thread			MINIDUMP_THREAD_CALLBACK <>
 ThreadEx		MINIDUMP_THREAD_EX_CALLBACK <>
 Module			MINIDUMP_MODULE_CALLBACK <>
 IncludeThread		MINIDUMP_INCLUDE_THREAD_CALLBACK <>
 IncludeModule		MINIDUMP_INCLUDE_MODULE_CALLBACK <>
 Io			MINIDUMP_IO_CALLBACK <>
 ReadMemoryFailure	MINIDUMP_READ_MEMORY_FAILURE_CALLBACK <>
 SecondaryFlags		ULONG ?
ENDS
MINIDUMP_CALLBACK_INPUT ENDS
PMINIDUMP_CALLBACK_INPUT typedef ptr MINIDUMP_CALLBACK_INPUT

MINIDUMP_CALLBACK_OUTPUT STRUC
UNION
 ModuleWriteFlags	ULONG ?
 ThreadWriteFlags	ULONG ?
 SecondaryFlags		ULONG ?
 STRUC
  MemoryBase		ULONG64 ?
  MemorySize		ULONG ?
 ENDS
 STRUC
  CheckCancel		BOOL ?
  Cancel		BOOL ?
 ENDS
 Handle			HANDLE ?
 STRUC
  VmRegion		MINIDUMP_MEMORY_INFO <>
  Continue		BOOL ?
 ENDS
 Status			HRESULT ?
ENDS
MINIDUMP_CALLBACK_OUTPUT ENDS
PMINIDUMP_CALLBACK_OUTPUT typedef ptr MINIDUMP_CALLBACK_OUTPUT



MINIDUMP_TYPE		typedef SDWORD
MiniDumpNormal		equ 0x00000000
MiniDumpWithDataSegs	equ 0x00000001
MiniDumpWithFullMemory	equ 0x00000002
MiniDumpWithHandleData	equ 0x00000004
MiniDumpFilterMemory	equ 0x00000008
MiniDumpScanMemory	equ 0x00000010
MiniDumpWithUnloadedModules equ 0x00000020
MiniDumpWithIndirectlyReferencedMemory equ 0x00000040
MiniDumpFilterModulePaths equ 0x00000080
MiniDumpWithProcessThreadData equ 0x00000100
MiniDumpWithPrivateReadWriteMemory equ 0x00000200
MiniDumpWithoutOptionalData equ 0x00000400
MiniDumpWithFullMemoryInfo equ 0x00000800
MiniDumpWithThreadInfo	equ 0x00001000
MiniDumpWithCodeSegs	equ 0x00002000
MiniDumpWithoutAuxiliaryState equ 0x00004000
MiniDumpWithFullAuxiliaryState equ 0x00008000
MiniDumpWithPrivateWriteCopyMemory equ 0x00010000
MiniDumpIgnoreInaccessibleMemory equ 0x00020000
MiniDumpWithTokenInformation equ 0x00040000
MiniDumpValidTypeFlags	equ 0x0007ffff

MINIDUMP_SECONDARY_FLAGS typedef SDWORD
MiniSecondaryWithoutPowerInfo equ 0x00000001
MiniSecondaryValidFlags equ 0x00000001

CALLBACK(MINIDUMP_CALLBACK_ROUTINE, :PVOID, :PMINIDUMP_CALLBACK_INPUT, :PMINIDUMP_CALLBACK_OUTPUT)
MINIDUMP_CALLBACK_INFORMATION STRUC
CallbackRoutine		MINIDUMP_CALLBACK_ROUTINE ?
CallbackParam		PVOID ?
MINIDUMP_CALLBACK_INFORMATION ENDS
PMINIDUMP_CALLBACK_INFORMATION typedef ptr MINIDUMP_CALLBACK_INFORMATION

RVA_TO_ADDR macro Mapping,Rva
	exitm<((((Mapping)) + (Rva)))>
	endm

;BOOL
MiniDumpWriteDump proto WINAPI \
	      hProcess: HANDLE,
	     ProcessId: DWORD,
		 hFile: HANDLE,
	      DumpType: MINIDUMP_TYPE,
	ExceptionParam: PMINIDUMP_EXCEPTION_INFORMATION,
       UserStreamParam: PMINIDUMP_USER_STREAM_INFORMATION,
	 CallbackParam: PMINIDUMP_CALLBACK_INFORMATION

;BOOL
MiniDumpReadDumpStream proto WINAPI \
	    BaseOfDump: PVOID,
	  StreamNumber: ULONG,
		   Dir: ptr PMINIDUMP_DIRECTORY,
	 StreamPointer: ptr PVOID,
	    StreamSize: ptr ULONG

.pragma pack(pop)
.pragma list(pop)
endif
