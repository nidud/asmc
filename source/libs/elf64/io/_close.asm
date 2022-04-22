; _CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

    .code

_close proc handle:int_t

    lea rax,_osfile
    .if ( edi < 3 || edi >= _nfile || !( byte ptr [rax+rdi] & FH_OPEN ) )

        _set_errno(EBADF)
        xor eax,eax
    .else

        mov byte ptr [rax+rdi],0
        sys_close(edi)
        xor eax,eax
    .endif
    ret

_close endp

    end
