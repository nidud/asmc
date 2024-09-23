.pragma list(push, 0)
ifndef _ADSHLP_
define _ADSHLP_

ADsGetObject proto WINAPI :LPCWSTR, :REFIID, :ptr ptr
ADsBuildEnumerator proto WINAPI :ptr IADsContainer, :ptr IEnumVARIANT
ADsFreeEnumerator proto WINAPI :ptr IEnumVARIANT
ADsEnumerateNext proto WINAPI :ptr IEnumVARIANT, :ULONG, :ptr, :ptr
ADsBuildVarArrayStr proto WINAPI :ptr LPWSTR, :DWORD, :ptr
ADsBuildVarArrayInt proto WINAPI :LPDWORD, :DWORD, :ptr
ADsOpenObject proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD, :REFIID, :ptr
ADsGetLastError proto WINAPI :LPDWORD, :LPWSTR, :DWORD, :LPWSTR, :DWORD
ADsSetLastError proto WINAPI :DWORD, :LPCWSTR, :LPCWSTR
ADsFreeAllErrorRecords proto WINAPI
AllocADsMem proto WINAPI :DWORD
FreeADsMem proto WINAPI :ptr
ReallocADsMem proto WINAPI :ptr, :DWORD, :DWORD
AllocADsStr proto WINAPI pStr:LPCWSTR
FreeADsStr proto WINAPI pStr:LPWSTR
ReallocADsStr proto WINAPI :ptr LPWSTR, :LPWSTR
ADsEncodeBinaryData proto WINAPI :PBYTE, :DWORD, :ptr LPWSTR
ADsDecodeBinaryData proto WINAPI :LPCWSTR, :ptr PBYTE, :ptr ULONG
PropVariantToAdsType proto WINAPI :ptr, :DWORD, :ptr PADSVALUE, :PDWORD
AdsTypeToPropVariant proto WINAPI :PADSVALUE, :DWORD, :ptr
AdsFreeAdsValues proto WINAPI :PADSVALUE, :DWORD
BinarySDToSecurityDescriptor proto WINAPI :PSECURITY_DESCRIPTOR, :ptr VARIANT, :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD
SecurityDescriptorToBinarySD proto WINAPI :VARIANT, :ptr, :PDWORD, :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD

ifdef DBG
if DBG
externdef ADsMemList :LIST_ENTRY
externdef ADsMemCritSect :CRITICAL_SECTION
InitADsMem proto WINAPI
AssertADsMemLeaks proto WINAPI
DumpMemoryTracker proto WINAPI
else
InitADsMem macro
    endm
AssertADsMemLeaks macro
    endm
DumpMemoryTracker macro
    endm
endif
endif
endif
.pragma list(pop)
