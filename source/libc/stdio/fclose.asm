; FCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc

    .code

fclose proc uses rbx fp:LPFILE

   .new retval:size_t

    ldr rcx,fp
    mov eax,[rcx]._iobuf._flag
    and eax,_IOREAD or _IOWRT or _IORW
    .ifz
        dec rax
       .return
    .endif

    mov rbx,rcx
    mov retval,fflush( rcx )
    _freebuf( rbx )

    xor eax,eax
    mov [rbx]._iobuf._flag,eax
    mov ecx,[rbx]._iobuf._file
    dec eax
    mov [rbx]._iobuf._file,eax

    .if ( _close( ecx ) == 0 )

        mov rax,retval
    .endif
    ret

fclose endp

    end
