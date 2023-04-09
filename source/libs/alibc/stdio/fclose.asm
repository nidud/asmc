; FCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

fclose proc uses rbx r12 fp:ptr FILE

    mov eax,[rdi]._iobuf._flag
    and eax,_IOREAD or _IOWRT or _IORW
    .ifz
        dec rax
        .return
    .endif

    mov rbx,rdi
    mov r12,fflush(rdi)
    _freebuf(rbx)

    xor eax,eax
    mov [rbx]._iobuf._flag,eax
    mov edi,[rbx]._iobuf._file
    dec eax
    mov [rbx]._iobuf._file,eax

    .if !close(edi)

        mov rax,r12
    .endif
    ret

fclose endp

    END
