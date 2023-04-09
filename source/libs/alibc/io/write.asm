; WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include linux/kernel.inc

.code

write proc uses rbx r12 r13 fd:int_t, buf:ptr, cnt:uint_t

    mov eax,edx                 ; cnt
    .return .if !eax            ; nothing to do

    .ifs ( edi >= _NFILE_ )      ; validate handle
                                ; out of range -- return error
        _set_errno(EBADF)
        .return -1
    .endif

    mov ebx,edi
    mov r12,rsi
    mov r13d,edx

    lea rdx,_osfile
    mov al,[rdx+rbx]
    .if ( al & FH_APPEND )      ; appending - seek to end of file; ignore error,
                                ; because maybe file doesn't allow seeking
        lseek(ebx, 0, SEEK_END)
    .endif
    .return( sys_write(ebx, r12, r13d) )

write endp

    end
