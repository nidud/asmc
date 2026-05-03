ifndef __ATLALLOC_H__
define __ATLALLOC_H__
endif

include atldef.inc
include windows.inc
include ole2.inc

.pragma pack(push,_ATL_PACKING)

ifndef _ATL_STACK_MARGIN
if defined(_M_IX86)
define _ATL_STACK_MARGIN 0x2000
elseif defined(_M_AMD64) or defined(_M_IA64)
define _ATL_STACK_MARGIN 0x4000
elseif defined(_M_ARM)
define _ATL_STACK_MARGIN 0x2000
else
.err <Unsupported target architecture.>
endif
endif

.pragma pack(pop)

ifndef _ATL_SAFE_ALLOCA_DEF_THRESHOLD
define _ATL_SAFE_ALLOCA_DEF_THRESHOLD 1024
endif
