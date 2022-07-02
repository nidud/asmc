; _STBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include malloc.inc
include crtl.inc

externdef _stdbuf:string_t

    .code

    assume rbx:ptr _iobuf

_stbuf proc uses rsi rbx fp:LPFILE

ifndef _WIN64
    mov ecx,fp
endif
    mov rbx,rcx

    .if ( _isatty( [rbx]._file) )

        xor eax,eax
        xor esi,esi

        lea rcx,stdout
        lea rdx,stderr

        .if ( rbx != rcx )

            .if ( rbx != rdx )
                .return
            .endif
            inc esi
        .endif

        mov ecx,[rbx]._flag
        and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
        .ifnz
            .return
        .endif

        or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
        mov [rbx]._flag,ecx

        imul esi,esi,size_t
        lea rcx,_stdbuf
        add rsi,rcx

        mov rax,[rsi]
        .if ( rax == NULL )

            mov [rsi],malloc( rcx )
        .endif

        mov ecx,_INTIOBUF
        .if ( rax == NULL )

            lea rax,[rbx]._charbuf
            mov ecx,4
        .endif
        mov [rbx]._ptr,rax
        mov [rbx]._base,rax
        mov [rbx]._bufsiz,ecx
        mov rax,1
    .endif
    ret

_stbuf endp

    end
