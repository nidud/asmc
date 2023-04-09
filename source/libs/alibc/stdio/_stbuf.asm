; _STBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include malloc.inc
include crtl.inc

externdef _stdbuf:qword

    .code

    assume rbx:ptr _iobuf

_stbuf proc uses rbx r12 r13 fp:ptr _iobuf

    mov rbx,rdi

    .if ( isatty([rbx]._file) )

        xor eax,eax
        xor r12,r12

        .if ( rbx != stdout )

            .return .if ( rbx != stderr )
            inc r12
        .endif

        mov ecx,[rbx]._flag
        and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
        .return .ifnz

        or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
        mov [rbx]._flag,ecx

        shl r12,3
        lea r10,_stdbuf
        add r12,r10
        mov rax,[r12]
        mov edi,_INTIOBUF

        .if ( rax == NULL )

            mov [r12],malloc(rdi)
            mov edi,_INTIOBUF

            .if ( rax == NULL )

                lea rax,[rbx]._charbuf
                mov edi,4
            .endif
        .endif

        mov [rbx]._ptr,rax
        mov [rbx]._base,rax
        mov [rbx]._bufsiz,edi
        mov eax,1
    .endif
    ret

_stbuf endp

    end
