; _INIT_POINTERS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include internal.inc
include awint.inc

_initp_eh_hooks         proto __cdecl :ptr
_initp_heap_handler     proto __cdecl :ptr
_initp_misc_invarg      proto __cdecl :ptr
_initp_misc_purevirt    proto __cdecl :ptr
_initp_misc_winsig      proto __cdecl :ptr
if not defined(_CRT_APP) or defined (_KERNELX)
_initp_misc_rand_s      proto __cdecl :ptr
endif

    .code

_init_pointers proc frame uses rsi

  local enull:ptr_t

    mov rsi,EncodePointer(NULL)

    _initp_heap_handler(rsi)
    _initp_misc_invarg(rsi)
    _initp_misc_purevirt(rsi)
    _initp_misc_winsig(rsi)
    _initp_eh_hooks(rsi)
if not defined(_CRT_APP) or defined(_KERNELX)
    _initp_misc_rand_s(rsi)
endif
if (defined (_M_IX86) or defined (_M_X64)) and not defined(_CORESYS) and not defined (_CRT_APP)
    __crtLoadWinApiPointers()
endif
ifdef _M_ARM
    _init_memcpy_functions()
endif
    ret
_init_pointers endp

    end
