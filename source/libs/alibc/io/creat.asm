; CREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include fcntl.inc
include linux/kernel.inc

externdef _fmode:uint_t

.code

creat proc uses rbx path:string_t, mode:int_t

    .if ( !rdi )

        _set_errno(EINVAL)
        .return -1
    .endif

    mov ebx,FH_OPEN
    ;
    ; figure out binary/text mode
    ;
    .if ( _fmode != O_BINARY ) ; check default mode
        or bl,FH_TEXT
    .endif

    .ifsd ( sys_creat(rdi, esi) < 0 )

        neg eax
        _set_errno(eax)
        .return -1
    .endif
    lea rcx,_osfile
    mov [rax+rcx],bl
    ret

creat endp

    end
