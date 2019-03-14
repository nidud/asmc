ifndef _INC_RTERR
_INC_RTERR equ <>

ifndef _CRTBLD
.err <ERROR: Use of C runtime library internal header file.>
endif

_RT_STACK               equ 0
_RT_NULLPTR             equ 1
_RT_FLOAT               equ 2
_RT_INTDIV              equ 3

_RT_EXECMEM             equ 5
_RT_EXECFORM            equ 6
_RT_EXECENV             equ 7

_RT_SPACEARG            equ 8
_RT_SPACEENV            equ 9
_RT_ABORT               equ 10

_RT_NPTR                equ 12
_RT_FPTR                equ 13
_RT_BREAK               equ 14
_RT_INT                 equ 15
_RT_THREAD              equ 16
_RT_LOCK                equ 17
_RT_HEAP                equ 18
_RT_OPENCON             equ 19
_RT_QWIN                equ 20
_RT_NOMAIN              equ 21
_RT_NONCONT             equ 22
_RT_INVALDISP           equ 23
_RT_ONEXIT              equ 24
_RT_PUREVIRT            equ 25
_RT_STDIOINIT           equ 26
_RT_LOWIOINIT           equ 27
_RT_HEAPINIT            equ 28
_RT_BADCLRVERSION       equ 29
_RT_CRT_NOTINIT         equ 30
_RT_CRT_INIT_CONFLICT   equ 31
_RT_LOCALE              equ 32
_RT_CRT_INIT_MANAGED_CONFLICT equ 33
_RT_ONEXIT_VAR          equ 34
_RT_COOKIE_INIT         equ 35

_RT_DOMAIN              equ 120
_RT_SING                equ 121
_RT_TLOSS               equ 122

_RT_CRNL                equ 252
_RT_BANNER              equ 255

endif
