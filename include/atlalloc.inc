ifndef __ATLALLOC_H__
__ATLALLOC_H__ equ <>
endif

include atldef.inc
include windows.inc
include ole2.inc

.pragma pack(push, _ATL_PACKING)

ifndef _ATL_W64
if not defined(__midl) and (defined(_X86_) or defined(_M_IX86))
_ATL_W64 equ <__w64>
else
_ATL_W64 equ <>
endif
endif

.pragma pack(pop)

.pragma pack(push,8)

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

endif

ifndef _ATL_STACK_MARGIN
if defined(_M_IX86)
_ATL_STACK_MARGIN	equ 0x2000
elseif defined(_M_AMD64) or defined(_M_IA64)
_ATL_STACK_MARGIN	equ 0x4000
elseif defined(_M_ARM)
_ATL_STACK_MARGIN	equ 0x2000
else
.err <Unsupported target architecture.>
endif
endif

.pragma pack(pop)

USES_ATL_SAFE_ALLOCA_EX macro x
exitm<.err>
endm

ifndef USES_ATL_SAFE_ALLOCA

endif

ifdef _ATL_SAFE_ALLOCA_ALWAYS_ALLOCATE_THRESHOLD_SIZE
else
endif

ifndef _ATL_SAFE_ALLOCA_DEF_THRESHOLD
_ATL_SAFE_ALLOCA_DEF_THRESHOLD	equ 1024
endif
