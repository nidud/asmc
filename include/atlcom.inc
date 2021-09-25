ifndef __ATLCOM_H__
define __ATLCOM_H__

ifndef __ATLBASE_H__
.err <atlcom.h requires atlbase.h to be included first>
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
include atlstdthunk.inc
endif

externdef IID_ITargetFrame:IID

include limits.inc

.pragma pack(push, _ATL_PACKING)

ifdef _ATL_DEBUG_QI
ifndef _ATL_DEBUG
define _ATL_DEBUG
endif
endif

ifdef _ATL_DEBUG_QI
_ATLDUMPIID macro iid, name, hr
	exitm<AtlDumpIID(iid, name, hr)>
	endm
else
_ATLDUMPIID macro iid, name, hr
	exitm<hr>
	endm
endif

ifndef OBJECT_ENTRY_PRAGMA
define OBJECT_ENTRY_PRAGMA
endif

ifdef _M_IA64
elseif defined( _M_IX86 ) or defined ( _M_AMD64 ) or defined ( _M_ARM ) or defined (_M_ARM64)
CComStdCallThunkHelper proto {
    mov rax, rcx
    mov rcx, 8[rcx]
    jmp qword ptr 16[rax]
    }
else
.err <X86, AMD64, IA64 and ARM>
endif

ifndef _ATL_MAX_VARTYPES
define _ATL_MAX_VARTYPES 8
endif

ifndef _ATL_NO_CONNECTION_POINTS
ifndef _DEFAULT_VECTORLENGTH
define _DEFAULT_VECTORLENGTH 4
endif
endif

.pragma pack(pop)

endif
