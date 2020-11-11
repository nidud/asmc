ifndef __ATLCOMMEM_H__
__ATLCOMMEM_H__ equ <>

ifndef __ATLMEM_H__
.err <ATLComMem.h requires atlmem.h to be included first>
endif

include atlcomcli.inc

.pragma pack(push,_ATL_PACKING)

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

.class CComHeap : public IAtlMemMgr

	.ENDS
endif

AtlAllocTaskWideStringW proto :LPCWSTR { int 3 }
AtlAllocTaskWideStringA proto :LPCSTR  { int 3 }
AtlAllocTaskAnsiStringW proto :LPCWSTR { int 3 }
AtlAllocTaskAnsiStringA proto :LPCSTR  { int 3 }

ifdef _UNICODE
AtlAllocTaskWideString equ <AtlAllocTaskWideStringW>
AtlAllocTaskAnsiString equ <AtlAllocTaskAnsiStringW>
;AtlAllocTaskString(x) AtlAllocTaskWideString(x)
else
AtlAllocTaskWideString equ <AtlAllocTaskWideStringA>
AtlAllocTaskAnsiString equ <AtlAllocTaskAnsiStringA>
;AtlAllocTaskString(x) AtlAllocTaskAnsiString(x)
endif

AtlAllocTaskOleString equ <AtlAllocTaskWideString>

.pragma pack(pop)

endif
