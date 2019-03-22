ifndef _INC_SYSERR
_INC_SYSERR equ <>

include crtdefs.inc
include internal.inc

ifndef _CRTBLD
.err <ERROR: Use of C runtime library internal header file.>
endif

_SYS_MSGMAX equ 38

_sys_err_msg proto __cdecl :int_t
_get_sys_err_msg equ <_sys_err_msg>

endif
