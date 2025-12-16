; STBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include io.inc
include malloc.inc

externdef _stdbuf:string_t

    .code

    assume rbx:LPFILE

_stbuf proc uses rbx fp:LPFILE

   .new p:string_t

    ldr rbx,fp

    xor eax,eax
    lea rdx,_stdbuf
    .if ( [rbx]._file != 1 )
        .if ( [rbx]._file != 2 )
            .return
        .endif
        add rdx,string_t
    .endif
    mov ecx,[rbx]._flag
    and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
    .ifz
        or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
        mov [rbx]._flag,ecx
        mov rax,[rdx]
        mov ecx,_INTIOBUF
        .if ( rax == NULL )
            lea rax,[rbx]._charbuf
            mov ecx,4
        .endif
        mov [rbx]._ptr,rax
        mov [rbx]._base,rax
        mov [rbx]._bufsiz,ecx
        mov eax,1
    .endif
    ret

_stbuf endp

    end
