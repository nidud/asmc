ifndef _FIBERS_H_
define _FIBERS_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc

if (_WIN32_WINNT ge 0x0600)
ifndef FLS_OUT_OF_INDEXES
define FLS_OUT_OF_INDEXES (0xFFFFFFFF)
endif
FlsAlloc proto WINAPI :PFLS_CALLBACK_FUNCTION
FlsGetValue proto WINAPI :DWORD
FlsSetValue proto WINAPI :DWORD, :PVOID
FlsFree proto WINAPI :DWORD
endif

if (_WIN32_WINNT ge 0x0600)
IsThreadAFiber proto WINAPI
endif

endif
