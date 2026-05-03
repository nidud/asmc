ifndef __WINSTRING_H_
define __WINSTRING_H_
ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif
ifndef _API_SET_H_
include apiset.inc
include apisetcconv.inc
endif
ifndef __hstring_h__
include hstring.inc
endif
ifndef __RPC_H__
include rpc.inc
endif
ifndef _APISET_WINRT_STRING_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0100
define _APISET_WINRT_STRING_VER 0x0100
endif
endif
endif

.pragma comment(lib, combase, "api-ms-win-core-winrt-l1-1-0")

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
WindowsCreateString proto WINAPI :PCNZWCH, :UINT32, :ptr
WindowsCreateStringReference proto WINAPI :PCWSTR, :UINT32, :ptr, :ptr
WindowsDeleteString proto WINAPI :HSTRING
WindowsDuplicateString proto WINAPI :HSTRING, :ptr
WindowsGetStringLen proto WINAPI :HSTRING
WindowsGetStringRawBuffer proto WINAPI :HSTRING, :ptr
WindowsIsStringEmpty proto WINAPI :HSTRING
WindowsStringHasEmbeddedNull proto WINAPI :HSTRING, :ptr
WindowsCompareStringOrdinal proto WINAPI :HSTRING, :HSTRING, :ptr
WindowsSubstring proto WINAPI :HSTRING, :UINT32, :ptr
WindowsSubstringWithSpecifiedLength proto WINAPI :HSTRING, :UINT32, :UINT32, :ptr
WindowsConcatString proto WINAPI :HSTRING, :HSTRING, :ptr
WindowsReplaceString proto WINAPI :HSTRING, :HSTRING, :HSTRING, :ptr
WindowsTrimStringStart proto WINAPI :HSTRING, :HSTRING, :ptr
WindowsTrimStringEnd proto WINAPI :HSTRING, :HSTRING, :ptr
WindowsPreallocateStringBuffer proto WINAPI :UINT32, :ptr, :ptr
WindowsPromoteStringBuffer proto WINAPI :HSTRING_BUFFER, :ptr
WindowsDeleteStringBuffer proto WINAPI :HSTRING_BUFFER
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(PINSPECT_HSTRING_CALLBACK, :ptr, :UINT_PTR, :UINT32, :ptr)

WindowsInspectString proto WINAPI :UINT_PTR, :USHORT, :PINSPECT_HSTRING_CALLBACK, :ptr, :ptr, :ptr
endif

endif
