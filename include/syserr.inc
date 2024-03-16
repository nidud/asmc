ifndef _INC_SYSERR
define _INC_SYSERR

;include crtdefs.inc
;include internal.inc
include errno.inc

ifndef _CRTBLD
.err <ERROR: Use of C runtime library internal header file.>
endif

define _SYS_MSGMAX 38
define _get_sys_err_msg <_sys_err_msg>

_sys_err_msg proto __cdecl :int_t

endif
