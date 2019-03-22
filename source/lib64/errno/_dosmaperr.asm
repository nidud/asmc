; _DOSMAPERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

_get_errno_from_oserr proto oserrno:ulong_t

    .code

_dosmaperr proc frame oserrno:ulong_t

  local error:int_t

    mov error,_get_errno_from_oserr(ecx)

    _errno()
    mov ecx,error
    mov [rax],ecx

    __doserrno()
    mov edx,oserrno
    mov [rax],edx

    mov rax,-1
    ret

_dosmaperr endp

    end
