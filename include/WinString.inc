ifndef __WINSTRING_H_
__WINSTRING_H_ equ <>

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif

include apiset.inc
include apisetcconv.inc
include hstring.inc
include rpc.inc

ifndef _APISET_WINRT_STRING_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0100
_APISET_WINRT_STRING_VER equ 0x0100
endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

WindowsCreateString proto WINAPI \
          sourceString: PCNZWCH,
                length: UINT32,
                string: ptr HSTRING

WindowsCreateStringReference proto WINAPI \
          sourceString: PCWSTR,
                length: UINT32,
         hstringHeader: ptr HSTRING_HEADER,
                string: ptr HSTRING

WindowsDeleteString proto WINAPI \
                string: HSTRING

WindowsDuplicateString proto WINAPI \
                string: HSTRING,
             newString: ptr HSTRING

WindowsGetStringLen proto WINAPI \
                string: HSTRING

WindowsGetStringRawBuffer proto WINAPI \
                string: HSTRING,
                length: ptr UINT32

WindowsIsStringEmpty proto WINAPI \
                string: HSTRING

WindowsStringHasEmbeddedNull proto WINAPI \
                string: HSTRING,
          hasEmbedNull: ptr BOOL

WindowsCompareStringOrdinal proto WINAPI \
               string1: HSTRING,
               string2: HSTRING,
                result: ptr INT32

WindowsSubstring proto WINAPI \
                string: HSTRING,
            startIndex: UINT32,
             newString: ptr HSTRING

WindowsSubstringWithSpecifiedLength proto WINAPI \
                string: HSTRING,
            startIndex: UINT32,
                length: UINT32,
             newString: ptr HSTRING

WindowsConcatString proto WINAPI \
               string1: HSTRING,
               string2: HSTRING,
             newString: ptr HSTRING

WindowsReplaceString proto WINAPI \
                string: HSTRING,
        stringReplaced: HSTRING,
     stringReplaceWith: HSTRING,
             newString: ptr HSTRING

WindowsTrimStringStart proto WINAPI \
                string: HSTRING,
            trimString: HSTRING,
             newString: ptr HSTRING

WindowsTrimStringEnd proto WINAPI \
                string: HSTRING,
            trimString: HSTRING,
             newString: ptr HSTRING

WindowsPreallocateStringBuffer proto WINAPI \
                length: UINT32,
            charBuffer: ptr WCHAR,
          bufferHandle: ptr HSTRING_BUFFER

WindowsPromoteStringBuffer proto WINAPI \
          bufferHandle: HSTRING_BUFFER,
               string: ptr HSTRING

WindowsDeleteStringBuffer proto WINAPI \
          bufferHandle: HSTRING_BUFFER

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


CALLBACK(PINSPECT_HSTRING_CALLBACK, :ptr, :UINT_PTR, :UINT32, :ptr BYTE)

WindowsInspectString proto WINAPI \
         targetHString: UINT_PTR,
               machine: USHORT,
              callback: PINSPECT_HSTRING_CALLBACK,
               context: ptr void,
                length: ptr UINT32,
   targetStringAddress: ptr UINT_PTR

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

HSTRING_UserSize proto WINAPI \
                pFlags: ptr DWORD,
          StartingSize: DWORD,
                 ppidl: ptr HSTRING

HSTRING_UserMarshal proto WINAPI \
                pFlags: ptr DWORD,
               pBuffer: ptr UCHAR,
                 ppidl: ptr HSTRING

HSTRING_UserUnmarshal proto WINAPI \
                pFlags: ptr DWORD,
               pBuffer: ptr UCHAR,
                 ppidl: ptr HSTRING

HSTRING_UserFree proto WINAPI \
                pFlags: ptr DWORD,
                 ppidl: ptr HSTRING

ifdef _WIN64

HSTRING_UserSize64 proto WINAPI \
                pFlags: ptr DWORD,
          StartingSize: DWORD,
                 ppidl: ptr HSTRING

HSTRING_UserMarshal64 proto WINAPI \
                pFlags: ptr DWORD,
               pBuffer: ptr UCHAR,
                 ppidl: ptr HSTRING

HSTRING_UserUnmarshal64 proto WINAPI \
                pFlags: ptr DWORD,
               pBuffer: ptr UCHAR,
                 ppidl: ptr HSTRING

HSTRING_UserFree64 proto WINAPI \
                pFlags: ptr DWORD,
                 ppidl: ptr HSTRING

endif

endif

endif
