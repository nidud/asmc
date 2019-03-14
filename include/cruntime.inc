ifndef _CRTBLD
;;
;; This is an internal C runtime header file. It is used when building
;; the C runtimes only. It is not to be used as a public header file.
;;
.err <ERROR: Use of C runtime library internal header file.>
endif
ifndef __LIBC_INC
 include libc.inc
endif
if defined (_SYSCRT) AND defined (_WIN64)
_USE_OLD_STDCPP equ 1
endif

if defined (_M_X64) OR defined (_M_ARM)
_UNALIGNED equ <__unaligned>
elseifdef _M_IX86
_UNALIGNED equ <>
else
.err <Unknown target architecture.>
endif
